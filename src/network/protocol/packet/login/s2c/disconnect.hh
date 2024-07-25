#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::login::s2c
{
	class Disconnect : public IPacket
	{
		// TODO json string -> Text
		std::string reason;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		std::string getReason() const;
		void setReason(const std::string& reason);

		std::string toString() const override;
	};
}
