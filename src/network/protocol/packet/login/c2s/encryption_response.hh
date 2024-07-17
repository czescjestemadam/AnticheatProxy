#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::login::c2s
{
	class EncryptionResponse : public IPacket
	{
		ByteBuf sharedSecret;
		ByteBuf verifyToken;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		bool apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		ByteBuf getSharedSecret() const;
		void setSharedSecret(const ByteBuf& shared_secret);

		ByteBuf getVerifyToken() const;
		void setVerifyToken(const ByteBuf& verify_token);

		std::string toString() const override;
	};
}
