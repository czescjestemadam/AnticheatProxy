#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::login::s2c
{
	class LoginPluginRequest : public IPacket
	{
		int messageId;
		Identifier channel;
		ByteBuf data;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		bool apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		int getMessageId() const;
		void setMessageId(int message_id);

		Identifier& getChannel();
		void setChannel(const Identifier& channel);

		ByteBuf& getData();
		void setData(const ByteBuf& data);

		std::string toString() const override;
	};
}
