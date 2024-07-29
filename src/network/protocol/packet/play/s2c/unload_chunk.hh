#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::s2c
{
	class UnloadChunk : public IPacket
	{
		int z, x;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		int getZ() const;
		void setZ(int z);

		int getX() const;
		void setX(int x);

		std::string toString() const override;
	};
}
