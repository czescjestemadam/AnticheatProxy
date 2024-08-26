#include "alert_manager.hh"

#include "anticheat_proxy.hh"
#include "network/protocol/packet/play/s2c/system_chat_message.hh"
#include "util/str_utils.hh"
#include "util/text/io/i_text_io.hh"
#include "util/text/io/minimessage/minimessage_io.hh"

void acp::AlertManager::send(const Alert& alert)
{
	const AlertConfig& config = AnticheatProxy::get()->getConfigManager().getAlert();

	// check if spam

	lastSent.push_back(alert);
	if (lastSent.size() > config.antispamLogSize)
		lastSent.erase(lastSent.begin());

	const std::string format = formatString(config.format, alert);
	const std::string hoverFormat = formatString(config.hoverFormat, alert);
	const std::string clickFormat = formatString(config.clickFormat, alert);

	std::unique_ptr<text::Component> component = text::ITextIO::minimessage().parse(format);
	component->getStyle().hoverEvent = {
		text::HoverEvent::Action::SHOW_TEXT,
		text::Component::toNbt(text::ITextIO::minimessage().parse(hoverFormat))
	};
	component->getStyle().clickEvent = {
		text::ClickEvent::Action::RUN_COMMAND,
		clickFormat
	};

	send(std::move(component));
}

std::string acp::AlertManager::formatString(const std::string& str, const Alert& alert)
{
	std::string replaced = str;

	StrUtils::replace(replaced, "<player>", alert.username);
	StrUtils::replace(replaced, "<check>", alert.check);
	StrUtils::replace(replaced, "<check-info>", alert.checkInfo);
	StrUtils::replace(replaced, "<check-description>", alert.checkDescription);
	StrUtils::replace(replaced, "<count>", std::to_string(alert.count));

	return replaced;
}

void acp::AlertManager::send(std::unique_ptr<text::Component>&& component)
{
	auto packet = std::make_unique<packet::play::s2c::SystemChatMessage>();
	packet->setMessage(std::move(component));
	packet->setOverlay(false);

	send(std::move(packet));
}

void acp::AlertManager::send(std::unique_ptr<packet::IPacket>&& packet)
{
	for (const std::shared_ptr<Connection>& connection : AnticheatProxy::get()->getNetworkManager().getConnections())
	{
		if (AnticheatProxy::get()->getPermissionManager().hasPermission(connection->getGameProfile().username, Permission::ALERT))
			connection->sendPacket(NetworkSide::CLIENT, packet);
	}
}
