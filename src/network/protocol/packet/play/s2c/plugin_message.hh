#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::s2c
{
	class PluginMessage : public IPacket
	{
		Identifier channel;
		ByteBuf data;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		Identifier& getChannel();
		const Identifier& getChannel() const;
		void setChannel(const Identifier& channel);

		ByteBuf& getData();
		const ByteBuf& getData() const;
		void setData(const ByteBuf& data);

		std::string toString() const override;
	};
}
