#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::login::s2c
{
	class SetCompression : public IPacket
	{
		int	threshold;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		int getThreshold() const;
		void setThreshold(int threshold);

		std::string toString() const override;
	};
}
