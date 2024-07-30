#include "login_start.hh"

#include "network/handler/login_handler.hh"
#include "network/protocol/protocol_version.hh"

#include <format>

void acp::packet::login::c2s::LoginStart::read(const ProtocolVersion* version)
{
	username = buf.readStr();

	if (*version >= ProtocolVersion::v1_19)
	{
		if (*version <= ProtocolVersion::v1_19_1 && buf.readByte())
		{
			const long timestamp = buf.readLong();

			const int pubkeyLen = buf.readVarint();
			const ByteBuf pubkey = buf.readBuf(pubkeyLen);

			const int sigLen = buf.readVarint();
			const ByteBuf sig = buf.readBuf(sigLen);

			signatureData = { timestamp, pubkey, sig };
		}

		if (*version >= ProtocolVersion::v1_20_2)
			uuid = buf.readUuid();
		else if (buf.readByte())
			uuid = buf.readUuid();
	}
}

void acp::packet::login::c2s::LoginStart::write(const ProtocolVersion* version)
{
	buf.writeStr(username);

	if (*version >= ProtocolVersion::v1_19)
	{
		if (*version <= ProtocolVersion::v1_19_1)
		{
			buf.writeByte(signatureData.has_value());
			if (signatureData.has_value())
			{
				buf.writeLong(std::get<0>(signatureData.value()));

				const ByteBuf& pubkey = std::get<1>(signatureData.value());
				buf.writeVarint(static_cast<int>(pubkey.size()));
				buf.writeBuf(pubkey);

				const ByteBuf& sig = std::get<2>(signatureData.value());
				buf.writeVarint(static_cast<int>(sig.size()));
				buf.writeBuf(sig);
			}
		}

		if (*version >= ProtocolVersion::v1_20_2)
		{
			buf.writeUuid(uuid.value());
		}
		else
		{
			buf.writeByte(uuid.has_value());
			if (uuid.has_value())
				buf.writeUuid(uuid.value());
		}
	}
}

acp::HandleResult acp::packet::login::c2s::LoginStart::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* loginHandler = dynamic_cast<LoginHandler*>(handler.get()))
		return loginHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::login::c2s::LoginStart::getId(const ProtocolVersion* version) const
{
	return 0x00;
}

std::string acp::packet::login::c2s::LoginStart::getUsername() const
{
	return username;
}

void acp::packet::login::c2s::LoginStart::setUsername(const std::string& username)
{
	this->username = username;
}

const std::optional<acp::UUID>& acp::packet::login::c2s::LoginStart::getUuid() const
{
	return uuid;
}

void acp::packet::login::c2s::LoginStart::setUuid(const std::optional<UUID>& uuid)
{
	this->uuid = uuid;
}

std::string acp::packet::login::c2s::LoginStart::toString() const
{
	return std::format("LoginStart[name={}, sig={}, uuid={}]", username, signatureData.has_value(), uuid.value_or(UUID{}).toString());
}
