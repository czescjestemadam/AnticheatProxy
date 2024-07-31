#pragma once
#include "network/protocol/packet/i_packet.hh"
#include "util/game_profile.hh"

namespace acp::packet::login::s2c
{
	class LoginSuccess : public IPacket
	{
		UUID uuid;
		std::string username;
		/// 1.19 - now
		std::vector<std::tuple<std::string, std::string, std::string>> properties;
		/// 1.20.5 - now
		std::optional<bool> strictErrorHandling;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		UUID getUuid() const;
		void setUuid(const UUID& uuid);

		std::string getUsername() const;
		void setUsername(const std::string& username);

		std::vector<std::tuple<std::string, std::string, std::string>>& getProperties();
		void setProperties(const std::vector<std::tuple<std::string, std::string, std::string>>& properties);

		const std::optional<bool>& getStrictErrorHandling() const;
		void setStrictErrorHandling(const std::optional<bool>& strict_error_handling);

		GameProfile toGameProfile() const;

		std::string toString() const override;
	};
}
