#pragma once
#include "i_network_handler.hh"
#include "network/protocol/packet/login/c2s/cookie_response.hh"
#include "network/protocol/packet/login/c2s/encryption_response.hh"
#include "network/protocol/packet/login/c2s/login_acknowledged.hh"
#include "network/protocol/packet/login/c2s/login_plugin_response.hh"
#include "network/protocol/packet/login/c2s/login_start.hh"
#include "network/protocol/packet/login/s2c/cookie_request.hh"
#include "network/protocol/packet/login/s2c/disconnect.hh"
#include "network/protocol/packet/login/s2c/encryption_request.hh"
#include "network/protocol/packet/login/s2c/login_plugin_request.hh"
#include "network/protocol/packet/login/s2c/login_success.hh"
#include "network/protocol/packet/login/s2c/set_compression.hh"

namespace acp
{
	class LoginHandler : public INetworkHandler
	{
	public:
		using INetworkHandler::INetworkHandler;

		HandleResult handle(packet::login::c2s::CookieResponse* packet);
		HandleResult handle(packet::login::c2s::EncryptionResponse* packet);
		HandleResult handle(packet::login::c2s::LoginAcknowledged* packet);
		HandleResult handle(packet::login::c2s::LoginPluginResponse* packet);
		HandleResult handle(packet::login::c2s::LoginStart* packet);

		HandleResult handle(packet::login::s2c::CookieRequest* packet);
		HandleResult handle(packet::login::s2c::Disconnect* packet);
		HandleResult handle(packet::login::s2c::EncryptionRequest* packet);
		HandleResult handle(packet::login::s2c::LoginPluginRequest* packet);
		HandleResult handle(packet::login::s2c::LoginSuccess* packet);
		HandleResult handle(packet::login::s2c::SetCompression* packet);
	};
}
