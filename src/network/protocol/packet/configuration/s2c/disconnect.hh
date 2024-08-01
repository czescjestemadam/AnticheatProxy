#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::configuration::s2c
{
	class Disconnect : public IPacket
	{
		std::unique_ptr<text::Component> reason;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		std::unique_ptr<text::Component>& getReason();
		const std::unique_ptr<text::Component>& getReason() const;
		void setReason(std::unique_ptr<text::Component>&& component);

		std::string toString() const override;
	};
}
