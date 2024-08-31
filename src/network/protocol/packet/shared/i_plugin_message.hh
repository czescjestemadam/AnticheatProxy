#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet
{
	class IPluginMessage : public IPacket
	{
	protected:
		Identifier channel;
		ByteBuf data;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		Identifier& getChannel();
		const Identifier& getChannel() const;
		void setChannel(const Identifier& channel);

		ByteBuf& getData();
		const ByteBuf& getData() const;
		void setData(const ByteBuf& data);

		std::string toString() const override;
	};
}
