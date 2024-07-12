#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::login::s2c
{
	class LoginPluginRequest : public IPacket
	{
		int messageId;
		// TODO identifier
		std::string channel;
		ByteBuf data;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		int getId(const ProtocolVersion* version) const override;

		int getMessageId() const;
		void setMessageId(int message_id);

		std::string getChannel() const;
		void setChannel(const std::string& channel);

		ByteBuf getData() const;
		void setData(const ByteBuf& data);

		std::string toString() const override;
	};
}
