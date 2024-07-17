#pragma once
#include "network/protocol/packet/i_packet.hh"

#include <string>

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

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		bool apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

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
