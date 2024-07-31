#include "known_packs.hh"

#include "network/handler/configuration_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::configuration::c2s::KnownPacks::read(const ProtocolVersion* version)
{
	const int len = buf.readVarint();

	for (int i = 0; i < len; ++i)
		packs.push_back(std::to_array({ buf.readStr(), buf.readStr(), buf.readStr() }));
}

void acp::packet::configuration::c2s::KnownPacks::write(const ProtocolVersion* version)
{
	buf.writeVarint(static_cast<int>(packs.size()));
	for (std::array<std::string, 3>& pack : packs)
	{
		buf.writeStr(pack[0]);
		buf.writeStr(pack[1]);
		buf.writeStr(pack[2]);
	}
}

acp::HandleResult acp::packet::configuration::c2s::KnownPacks::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* configHandler = dynamic_cast<ConfigurationHandler*>(handler.get()))
		configHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::configuration::c2s::KnownPacks::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x07;

	return -1;
}

std::vector<std::array<std::string, 3>>& acp::packet::configuration::c2s::KnownPacks::getPacks()
{
	return packs;
}

void acp::packet::configuration::c2s::KnownPacks::setPacks(const std::vector<std::array<std::string, 3>>& packs)
{
	this->packs = packs;
}

std::string acp::packet::configuration::c2s::KnownPacks::toString() const
{
	return std::format("KnownPacks[{}]", packs.size());
}
