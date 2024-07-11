#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::login::c2s
{
	class LoginPluginResponse : public IPacket
	{
		int messageId;
		bool success;
		ByteBuf data;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		int getMessageId() const;
		void setMessageId(int message_id);

		bool isSuccess() const;
		void setSuccess(bool success);

		ByteBuf getData() const;
		void setData(const ByteBuf& data);

		std::string toString() const override;
	};
}
