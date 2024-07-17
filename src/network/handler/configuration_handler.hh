#pragma once
#include "i_network_handler.hh"
#include "network/protocol/packet/configuration/c2s/acknowledge_finish_configuration.hh"
#include "network/protocol/packet/configuration/c2s/client_information.hh"
#include "network/protocol/packet/configuration/c2s/cookie_response.hh"
#include "network/protocol/packet/configuration/c2s/keep_alive.hh"
#include "network/protocol/packet/configuration/c2s/known_packs.hh"
#include "network/protocol/packet/configuration/c2s/plugin_message.hh"
#include "network/protocol/packet/configuration/c2s/pong.hh"
#include "network/protocol/packet/configuration/c2s/resource_pack_response.hh"
#include "network/protocol/packet/configuration/s2c/add_resource_pack.hh"
#include "network/protocol/packet/configuration/s2c/cookie_request.hh"
#include "network/protocol/packet/configuration/s2c/custom_report_details.hh"
#include "network/protocol/packet/configuration/s2c/disconnect.hh"
#include "network/protocol/packet/configuration/s2c/feature_flags.hh"
#include "network/protocol/packet/configuration/s2c/finish_configuration.hh"
#include "network/protocol/packet/configuration/s2c/keep_alive.hh"
#include "network/protocol/packet/configuration/s2c/known_packs.hh"
#include "network/protocol/packet/configuration/s2c/ping.hh"
#include "network/protocol/packet/configuration/s2c/plugin_message.hh"
#include "network/protocol/packet/configuration/s2c/registry_data.hh"
#include "network/protocol/packet/configuration/s2c/remove_resource_pack.hh"
#include "network/protocol/packet/configuration/s2c/reset_chat.hh"
#include "network/protocol/packet/configuration/s2c/server_links.hh"
#include "network/protocol/packet/configuration/s2c/store_cookie.hh"
#include "network/protocol/packet/configuration/s2c/transfer.hh"
#include "network/protocol/packet/configuration/s2c/update_tags.hh"

namespace acp
{
	class ConfigurationHandler : public INetworkHandler
	{
	public:
		using INetworkHandler::INetworkHandler;

		bool handle(packet::configuration::c2s::ClientInformation* packet);
		bool handle(packet::configuration::c2s::CookieResponse* packet);
		bool handle(packet::configuration::c2s::PluginMessage* packet);
		bool handle(packet::configuration::c2s::AcknowledgeFinishConfiguration* packet);
		bool handle(packet::configuration::c2s::KeepAlive* packet);
		bool handle(packet::configuration::c2s::Pong* packet);
		bool handle(packet::configuration::c2s::ResourcePackResponse* packet);
		bool handle(packet::configuration::c2s::KnownPacks* packet);

		bool handle(packet::configuration::s2c::CookieRequest* packet);
		bool handle(packet::configuration::s2c::PluginMessage* packet);
		bool handle(packet::configuration::s2c::Disconnect* packet);
		bool handle(packet::configuration::s2c::FinishConfiguration* packet);
		bool handle(packet::configuration::s2c::KeepAlive* packet);
		bool handle(packet::configuration::s2c::Ping* packet);
		bool handle(packet::configuration::s2c::ResetChat* packet);
		bool handle(packet::configuration::s2c::RegistryData* packet);
		bool handle(packet::configuration::s2c::RemoveResourcePack* packet);
		bool handle(packet::configuration::s2c::AddResourcePack* packet);
		bool handle(packet::configuration::s2c::StoreCookie* packet);
		bool handle(packet::configuration::s2c::Transfer* packet);
		bool handle(packet::configuration::s2c::FeatureFlags* packet);
		bool handle(packet::configuration::s2c::UpdateTags* packet);
		bool handle(packet::configuration::s2c::KnownPacks* packet);
		bool handle(packet::configuration::s2c::CustomReportDetails* packet);
		bool handle(packet::configuration::s2c::ServerLinks* packet);
	};
}
