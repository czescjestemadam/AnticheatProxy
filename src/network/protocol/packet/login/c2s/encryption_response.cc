#include "encryption_response.hh"

#include "network/handler/login_handler.hh"

#include <format>

void acp::packet::login::c2s::EncryptionResponse::read(const ProtocolVersion* version)
{
	const int sharedSecretLen = buf.readVarint();
	sharedSecret = buf.readBuf(sharedSecretLen);

	const int verifyTokenLen = buf.readVarint();
	verifyToken = buf.readBuf(verifyTokenLen);
}

void acp::packet::login::c2s::EncryptionResponse::write(const ProtocolVersion* version)
{
}

bool acp::packet::login::c2s::EncryptionResponse::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* loginHandler = dynamic_cast<LoginHandler*>(handler.get()))
		return loginHandler->handle(this);

	return false;
}

int acp::packet::login::c2s::EncryptionResponse::getId(const ProtocolVersion* version) const
{
	return 0x01;
}

acp::ByteBuf acp::packet::login::c2s::EncryptionResponse::getSharedSecret() const
{
	return sharedSecret;
}

void acp::packet::login::c2s::EncryptionResponse::setSharedSecret(const ByteBuf& shared_secret)
{
	sharedSecret = shared_secret;
}

acp::ByteBuf acp::packet::login::c2s::EncryptionResponse::getVerifyToken() const
{
	return verifyToken;
}

void acp::packet::login::c2s::EncryptionResponse::setVerifyToken(const ByteBuf& verify_token)
{
	verifyToken = verify_token;
}

std::string acp::packet::login::c2s::EncryptionResponse::toString() const
{
	return std::format("EncryptionResponse[secret={}, verify={}]", sharedSecret.toStringShort(), verifyToken.toStringShort());
}
