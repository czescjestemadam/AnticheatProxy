#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::login::s2c
{
	class EncryptionRequest : public IPacket
	{
		std::string serverId;
		ByteBuf publicKey;
		ByteBuf verifyToken;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		bool apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		std::string getServerId() const;
		void setServerId(const std::string& server_id);

		ByteBuf getPublicKey() const;
		void setPublicKey(const ByteBuf& public_key);

		ByteBuf getVerifyToken() const;
		void setVerifyToken(const ByteBuf& verify_token);

		std::string toString() const override;
	};
}
