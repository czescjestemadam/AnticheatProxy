#include "remove_entities.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::RemoveEntities::read(const ProtocolVersion* version)
{
	if (*version == ProtocolVersion::v1_17)
	{
		ids.push_back(buf.readVarint());
	}
	else
	{
		const int len = buf.readVarint();
		for (int i = 0; i < len; i++)
			ids.push_back(buf.readVarint());
	}
}

void acp::packet::play::s2c::RemoveEntities::write(const ProtocolVersion* version)
{
	if (*version == ProtocolVersion::v1_17)
	{
		buf.writeVarint(ids[0]);
	}
	else
	{
		buf.writeVarint(static_cast<int>(ids.size()));
		for (const int id : ids)
			buf.writeVarint(id);
	}
}

acp::HandleResult acp::packet::play::s2c::RemoveEntities::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::RemoveEntities::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x42;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x40;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x3E;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x3A;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x3B;
	if (*version >= ProtocolVersion::v1_19)
		return 0x38;
	if (*version >= ProtocolVersion::v1_17)
		return 0x3A;

	return 0x36;
}

std::vector<int>& acp::packet::play::s2c::RemoveEntities::getIds()
{
	return ids;
}

const std::vector<int>& acp::packet::play::s2c::RemoveEntities::getIds() const
{
	return ids;
}

void acp::packet::play::s2c::RemoveEntities::setIds(const std::vector<int>& ids)
{
	this->ids = ids;
}

std::string acp::packet::play::s2c::RemoveEntities::toString() const
{
	std::string arrStr;

	for (int i = 0; i < ids.size(); i++)
	{
		arrStr += std::to_string(ids[i]);

		if (i + 1 < ids.size())
			arrStr += ", ";
	}

	return std::format("RemoveEntities[{}]", arrStr);
}
