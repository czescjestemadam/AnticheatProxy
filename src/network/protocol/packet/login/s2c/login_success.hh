#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::login::s2c
{
	class LoginSuccess : public IPacket
	{
		UUID uuid;
		std::string username;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		bool apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		UUID getUuid() const;
		void setUuid(const UUID& uuid);

		std::string getUsername() const;
		void setUsername(const std::string& username);

		std::string toString() const override;
	};
}
