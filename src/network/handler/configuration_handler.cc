#include "configuration_handler.hh"

#include "network/connection.hh"
#include "util/nbt/tag/tag_list.hh"
#include "util/nbt/tag/tag_number.hh"
#include "util/registry/damage_type.hh"
#include "util/registry/dimension_type.hh"

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::c2s::ClientInformation* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::c2s::CookieResponse* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::c2s::PluginMessage* packet)
{
	return connection->getMessenger().onPluginMessage(NetworkSide::DEST, packet);
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::c2s::AcknowledgeFinishConfiguration* packet)
{
	connection->setState(NetworkState::PLAY);

	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::c2s::KeepAlive* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::c2s::Pong* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::c2s::ResourcePackResponse* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::c2s::KnownPacks* packet)
{
	return HandleResult::FORWARD;
}


acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::CookieRequest* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::PluginMessage* packet)
{
	return connection->getMessenger().onPluginMessage(NetworkSide::CLIENT, packet);
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::Disconnect* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::FinishConfiguration* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::KeepAlive* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::Ping* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::ResetChat* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::RegistryData* packet)
{
	if (*connection->getProtocolVersion() < ProtocolVersion::v1_20_5)
	{
		if (auto* codec = dynamic_cast<nbt::TagCompound*>(packet->getCodec().get()))
		{
			if (codec->get().contains("damage_type"))
			{
				if (auto* damage = dynamic_cast<nbt::TagCompound*>(codec->get()["damage_type"].get()))
				{
					if (auto* list = dynamic_cast<nbt::TagList*>(damage->get("value").get()))
					{
						for (std::unique_ptr<nbt::Tag>& tag : list->get())
						{
							registry::DamageTypeEntry entry;
							entry.deserialize(tag);

							connection->getDamageTypes().push_back(std::move(entry));
						}
					}
				}
			}

			if (codec->get().contains("dimension_type"))
			{
				if (auto* dimensions = dynamic_cast<nbt::TagCompound*>(codec->get()["dimension_type"].get()))
				{
					if (auto* list = dynamic_cast<nbt::TagList*>(dimensions->get("value").get()))
					{
						for (std::unique_ptr<nbt::Tag>& tag : list->get())
						{
							registry::DimensionTypeEntry entry;
							entry.deserialize(tag);

							connection->getDimensionTypes().push_back(std::move(entry));
						}
					}
				}
			}
		}
	}
	else
	{
		auto& entries = packet->getEntries();

		if (packet->getRegistryId() == Identifier("minecraft", "dimension_type"))
		{
			for (int i = 0; i < entries.size(); ++i)
			{
				auto& [id, tag] = entries[i];

				registry::DimensionType type;
				type.deserialize(tag);

				connection->getDimensionTypes().emplace_back(i, type, id.toString());
			}
		}
		if (packet->getRegistryId() == Identifier("minecraft", "damage_type"))
		{
			for (int i = 0; i < entries.size(); ++i)
			{
				auto& [id, tag] = entries[i];

				registry::DamageType type;
				type.deserialize(tag);

				connection->getDamageTypes().emplace_back(i, type, id.toString());
			}
		}
	}

	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::RemoveResourcePack* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::AddResourcePack* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::StoreCookie* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::Transfer* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::FeatureFlags* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::UpdateTags* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::KnownPacks* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::CustomReportDetails* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::ServerLinks* packet)
{
	return HandleResult::FORWARD;
}


void acp::ConfigurationHandler::sendPluginMessage(NetworkSide to, const Identifier& channel, const ByteBuf& data)
{
	if (to == NetworkSide::DEST) // server
	{
		auto packet = std::make_unique<packet::configuration::c2s::PluginMessage>();
		packet->setChannel(channel);
		packet->setData(data);

		connection->sendPacket(to, std::move(packet));
	}
	else // client
	{
		auto packet = std::make_unique<packet::configuration::s2c::PluginMessage>();
		packet->setChannel(channel);
		packet->setData(data);

		connection->sendPacket(to, std::move(packet));
	}
}

void acp::ConfigurationHandler::disconnect(const std::unique_ptr<text::Component>& reason)
{
	auto packet = std::make_unique<packet::configuration::s2c::Disconnect>();
	packet->setReason(reason->copy());

	connection->sendPacket(NetworkSide::CLIENT, std::move(packet));
}
