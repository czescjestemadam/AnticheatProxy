#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::login::c2s
{
	class LoginStart : public IPacket
	{
		std::string username;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		int getId(const ProtocolVersion* version) const override;

		std::string getUsername() const;
		void setUsername(const std::string& username);

		std::string toString() const override;
	};
}
