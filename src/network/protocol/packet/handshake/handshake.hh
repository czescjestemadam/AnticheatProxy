#pragma once
#include <string>

#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::handshake
{
	class Handshake : public IPacket
	{
		int protocolVersion;
		std::string address;
		ushort port;
		int nextState;

	public:
		using IPacket::IPacket;

		void read() override;
		void write() override;
	};
}
