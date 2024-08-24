#include "alert_manager.hh"

#include "anticheat_proxy.hh"
#include "network/protocol/packet/play/s2c/system_chat_message.hh"
#include "util/text/text_component.hh"

void send(std::unique_ptr<acp::text::Component>&& text);
void send(std::unique_ptr<acp::packet::IPacket>&& packet);


void acp::AlertManager::send(const Alert& alert)
{
	const AlertConfig& config = AnticheatProxy::get()->getConfigManager().getAlert();

	// check if spam

	lastSent.push_back(alert);
	if (lastSent.size() > config.antispamLogSize)
		lastSent.erase(lastSent.begin());

	// TODO formatting in config, TextComponentIO

	auto text = std::make_unique<text::TextComponent>("[alert] user=" + alert.username);
	text->getStyle().color = "red";

	::send(std::move(text));
}


void send(std::unique_ptr<acp::text::Component>&& text)
{
	auto packet = std::make_unique<acp::packet::play::s2c::SystemChatMessage>();
	std::unique_ptr<acp::nbt::Tag> tag = std::make_unique<acp::nbt::TagCompound>();
	text->serialize(tag);
	packet->setMessage(std::move(tag));
	packet->setOverlay(false);

	send(std::move(packet));
}

void send(std::unique_ptr<acp::packet::IPacket>&& packet)
{
	acp::AnticheatProxy* acp = acp::AnticheatProxy::get();

	for (const std::shared_ptr<acp::Connection>& connection : acp->getNetworkManager().getConnections())
	{
		if (acp->getPermissionManager().hasPermission(connection->getGameProfile().username, acp::Permission::ALERT))
			connection->sendPacket(acp::NetworkSide::CLIENT, packet);
	}
}
