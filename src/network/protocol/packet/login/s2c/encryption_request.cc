#include "encryption_request.hh"

#include <format>

void acp::packet::login::s2c::EncryptionRequest::read(const ProtocolVersion* version)
{
	serverId = buf.readStr();

	const int pubkeyLen = buf.readVarint();
	publicKey = buf.readBuf(pubkeyLen);

	const int verifyTokenLen = buf.readVarint();
	verifyToken = buf.readBuf(verifyTokenLen);
}

void acp::packet::login::s2c::EncryptionRequest::write(const ProtocolVersion* version)
{
	buf.writeStr(serverId);
	buf.writeBuf(publicKey);
	buf.writeBuf(verifyToken);
}

int acp::packet::login::s2c::EncryptionRequest::getId(const ProtocolVersion* version) const
{
	return 1;
}

std::string acp::packet::login::s2c::EncryptionRequest::getServerId() const
{
	return serverId;
}

void acp::packet::login::s2c::EncryptionRequest::setServerId(const std::string& server_id)
{
	serverId = server_id;
}

acp::ByteBuf acp::packet::login::s2c::EncryptionRequest::getPublicKey() const
{
	return publicKey;
}

void acp::packet::login::s2c::EncryptionRequest::setPublicKey(const ByteBuf& public_key)
{
	publicKey = public_key;
}

acp::ByteBuf acp::packet::login::s2c::EncryptionRequest::getVerifyToken() const
{
	return verifyToken;
}

void acp::packet::login::s2c::EncryptionRequest::setVerifyToken(const ByteBuf& verify_token)
{
	verifyToken = verify_token;
}

std::string acp::packet::login::s2c::EncryptionRequest::toString() const
{
	return std::format("EncryptionRequest[id={}, pubkey={}, verify={}]", serverId, publicKey.toStringShort(), verifyToken.toStringShort());
}
