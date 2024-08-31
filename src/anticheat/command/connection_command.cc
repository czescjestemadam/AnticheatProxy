#include "connection_command.hh"

#include "anticheat_proxy.hh"
#include "globals.hh"
#include "util/text/io/i_text_io.hh"
#include "util/text/io/minimessage/minimessage_io.hh"

acp::ConnectionCommand::ConnectionCommand()
	: ICommand(nullptr)
{
}

void acp::ConnectionCommand::execute(ICommandSource* source, const std::vector<std::string>& args)
{
	if (args.empty())
	{
		source->sendMessage(text::ITextIO::minimessage().parse("<red>Usage: " + getUsage()));
		return;
	}

	const std::weak_ptr<Connection> connectionPtr = AnticheatProxy::get()->getNetworkManager().getByUsername(args.front());
	if (const std::shared_ptr<Connection> connection = connectionPtr.lock())
	{
		source->sendMessage(text::ITextIO::minimessage().parse(
			std::format("<{}><bold>Connection info for {}",
						globals::THEME_COLOR,
						connection->getGameProfile().username,
						connection->getGameProfile().uuid.toString()
			)
		));
		if (source->hasPermission(Permission::CMD_IP))
		{
			source->sendMessage(text::ITextIO::minimessage().parse(
				std::format("<{}>IP: {}", globals::THEME_COLOR, connection->getSide(NetworkSide::CLIENT).getAddrStr())
			));
		}
		source->sendMessage(text::ITextIO::minimessage().parse(
			std::format("<{}>Packet count: c2s={} s2c={}",
						globals::THEME_COLOR,
						connection->getPacketCount(NetworkSide::DEST),
						connection->getPacketCount(NetworkSide::CLIENT)
			)
		));
		source->sendMessage(text::ITextIO::minimessage().parse(
			std::format("<{}>Network state: {}", globals::THEME_COLOR, EnumNames<NetworkState>::get(connection->getState()))
		));
		source->sendMessage(text::ITextIO::minimessage().parse(
			std::format("<{}>Client version: {} (pvn={})",
						globals::THEME_COLOR,
						connection->getProtocolVersion()->getName(),
						connection->getProtocolVersion()->getIdx()
			)
		));
		source->sendMessage(text::ITextIO::minimessage().parse(
			std::format("<{}>Client brand: {}", globals::THEME_COLOR, connection->getClientbrand())
		));
	}
	else
		source->sendMessage(text::ITextIO::minimessage().parse(std::format("<red>Player {} not found", args.front())));
}

std::vector<std::string> acp::ConnectionCommand::complete(ICommandSource* source, const std::vector<std::string>& args)
{
	if (args.size() == 1)
	{
		std::vector<std::string> ret;

		for (const std::shared_ptr<Connection>& connection : AnticheatProxy::get()->getNetworkManager().getConnections())
		{
			const std::string& username = connection->getGameProfile().username;
			if (!username.empty())
				ret.push_back(username);
		}

		return ret;
	}

	return {};
}

std::string acp::ConnectionCommand::getUsage() const
{
	return "connection <username>";
}

std::string acp::ConnectionCommand::getHelpMessage() const
{
	return "Shows player connection info";
}
