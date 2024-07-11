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

		int getProtocolVersion() const;
		void setProtocolVersion(int protocol_version);

		const std::string& getAddress() const;
		void setAddress(const std::string& address);

		ushort getPort() const;
		void setPort(ushort port);

		int getNextState() const;
		void setNextState(int next_state);


		std::string toString() const override;
	};
}
