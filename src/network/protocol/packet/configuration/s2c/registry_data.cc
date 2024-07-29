#include "registry_data.hh"

#include "network/handler/configuration_handler.hh"
#include "network/protocol/protocol_version.hh"
#include "util/nbt/tag.hh"

void acp::packet::configuration::s2c::RegistryData::read(const ProtocolVersion* version)
{
	if (*version < ProtocolVersion::v1_20_5)
	{
		codec = buf.readNbt(*version < ProtocolVersion::v1_20_2);
	}
	else
	{
		registryId = buf.readIdentifier(); // TODO test

		const int len = buf.readVarint();
		for (int i = 0; i < len; i++)
		{
			const Identifier id = buf.readIdentifier();
			std::unique_ptr<nbt::Tag> data = nullptr;
			if (buf.readByte())
				data = buf.readNbt(*version < ProtocolVersion::v1_20_2);

			entries.emplace_back(id, std::move(data));
		}
	}
}

void acp::packet::configuration::s2c::RegistryData::write(const ProtocolVersion* version)
{
	if (*version < ProtocolVersion::v1_20_5)
	{
		buf.writeNbt(codec, *version < ProtocolVersion::v1_20_2);
	}
	else
	{
		buf.writeIdentifier(registryId);

		buf.writeVarint(static_cast<int>(entries.size()));
		for (auto& [id, data] : entries)
		{
			buf.writeIdentifier(id);
			buf.writeByte(data != nullptr);
			if (data != nullptr)
				buf.writeNbt(data, *version < ProtocolVersion::v1_20_2);
		}
	}
}

acp::HandleResult acp::packet::configuration::s2c::RegistryData::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* configHandler = dynamic_cast<ConfigurationHandler*>(handler.get()))
		return configHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::configuration::s2c::RegistryData::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x07;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x05;

	return -1;
}

acp::Identifier acp::packet::configuration::s2c::RegistryData::getRegistryId() const
{
	return registryId;
}

void acp::packet::configuration::s2c::RegistryData::setRegistryId(const Identifier& registry_id)
{
	registryId = registry_id;
}

std::vector<std::pair<acp::Identifier, std::unique_ptr<acp::nbt::Tag>>>& acp::packet::configuration::s2c::RegistryData::getEntries()
{
	return entries;
}

const std::vector<std::pair<acp::Identifier, std::unique_ptr<acp::nbt::Tag>>>& acp::packet::configuration::s2c::RegistryData::getEntries() const
{
	return entries;
}

void acp::packet::configuration::s2c::RegistryData::setEntries(std::vector<std::pair<Identifier, std::unique_ptr<nbt::Tag>>>&& entries)
{
	this->entries = std::move(entries);
}

std::string acp::packet::configuration::s2c::RegistryData::toString() const
{
	return std::format("RegistryData[codec={} / id={}, entries={}]", codec->toString(), registryId.toString(), entries.size());
}
