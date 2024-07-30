#include "login_success.hh"

#include "network/handler/login_handler.hh"
#include "network/protocol/protocol_version.hh"

#include <format>

void acp::packet::login::s2c::LoginSuccess::read(const ProtocolVersion* version)
{
	uuid = buf.readUuid();
	username = buf.readStr();

	if (*version >= ProtocolVersion::v1_19)
	{
		const int len = buf.readVarint();
		for (int i = 0; i < len; ++i)
		{
			const std::string name = buf.readStr();
			const std::string value = buf.readStr();
			std::string sig;
			if (buf.readByte())
				sig = buf.readStr();

			properties.emplace_back(name, value, sig);
		}
	}

	if (*version >= ProtocolVersion::v1_20_5)
		strictErrorHandling = buf.readByte();

	// TODO fix more
}

void acp::packet::login::s2c::LoginSuccess::write(const ProtocolVersion* version)
{
	buf.writeUuid(uuid);
	buf.writeStr(username);

	if (*version >= ProtocolVersion::v1_19)
	{
		buf.writeVarint(static_cast<int>(properties.size()));
		for (auto& [name, value, sig] : properties)
		{
			buf.writeStr(name);
			buf.writeStr(value);

			const bool sigPresent = !sig.empty();
			buf.writeByte(sigPresent);
			if (sigPresent)
				buf.writeStr(sig);
		}
	}

	if (*version >= ProtocolVersion::v1_20_5)
		buf.writeByte(strictErrorHandling.value());
}

acp::HandleResult acp::packet::login::s2c::LoginSuccess::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* loginHandler = dynamic_cast<LoginHandler*>(handler.get()))
		return loginHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::login::s2c::LoginSuccess::getId(const ProtocolVersion* version) const
{
	return 0x02;
}

acp::UUID acp::packet::login::s2c::LoginSuccess::getUuid() const
{
	return uuid;
}

void acp::packet::login::s2c::LoginSuccess::setUuid(const UUID& uuid)
{
	this->uuid = uuid;
}

std::string acp::packet::login::s2c::LoginSuccess::getUsername() const
{
	return username;
}

void acp::packet::login::s2c::LoginSuccess::setUsername(const std::string& username)
{
	this->username = username;
}

std::vector<std::tuple<std::string, std::string, std::string>>& acp::packet::login::s2c::LoginSuccess::getProperties()
{
	return properties;
}

void acp::packet::login::s2c::LoginSuccess::setProperties(const std::vector<std::tuple<std::string, std::string, std::string>>& properties)
{
	this->properties = properties;
}

const std::optional<bool>& acp::packet::login::s2c::LoginSuccess::getStrictErrorHandling() const
{
	return strictErrorHandling;
}

void acp::packet::login::s2c::LoginSuccess::setStrictErrorHandling(const std::optional<bool>& strict_error_handling)
{
	strictErrorHandling = strict_error_handling;
}

std::string acp::packet::login::s2c::LoginSuccess::toString() const
{
	return std::format("LoginSuccess[id={}, name={}, props={}, strictError={}]",
					   uuid.toString(),
					   username,
					   properties.size(),
					   strictErrorHandling.value_or(false)
	);
}
