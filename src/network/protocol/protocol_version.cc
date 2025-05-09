#include "protocol_version.hh"

#include <map>

static std::map<int, acp::ProtocolVersion*> versionByIdx;

acp::ProtocolVersion::ProtocolVersion(int idx, std::string&& name) : idx(idx), name(std::move(name))
{
	versionByIdx[idx] = this;
}

int acp::ProtocolVersion::getIdx() const
{
	return idx;
}

std::string acp::ProtocolVersion::getName() const
{
	return name;
}

const acp::ProtocolMapping& acp::ProtocolVersion::getProtocolMapping() const
{
	return protocolMapping;
}

const acp::game::EntityTypeMapping& acp::ProtocolVersion::getEntityTypeMapping() const
{
	return entityTypeMapping;
}

const acp::command::ParserMapping& acp::ProtocolVersion::getCommandParserMapping() const
{
	return commandParserMapping;
}

bool acp::ProtocolVersion::operator==(const ProtocolVersion& rhs) const
{
	return idx == rhs.idx;
}

bool acp::ProtocolVersion::operator!=(const ProtocolVersion& rhs) const
{
	return !(*this == rhs);
}

bool acp::ProtocolVersion::operator<(const ProtocolVersion& rhs) const
{
	return idx < rhs.idx;
}

bool acp::ProtocolVersion::operator<=(const ProtocolVersion& rhs) const
{
	return !(rhs < *this);
}

bool acp::ProtocolVersion::operator>(const ProtocolVersion& rhs) const
{
	return rhs < *this;
}

bool acp::ProtocolVersion::operator>=(const ProtocolVersion& rhs) const
{
	return !(*this < rhs);
}

void acp::ProtocolVersion::compileMappings(SubLogger&& logger)
{
	logger.info("Compiling packet mappings");

	for (auto& [idx, version] : versionByIdx)
	{
		version->protocolMapping = ProtocolMapping(version);
		version->entityTypeMapping = game::EntityTypeMapping(version);
		version->commandParserMapping = command::ParserMapping(version);

		std::string name = version->getName();
		if (name.length() < 6)
			name += "  ";

		logger.info("Compiled {} packet, {} entity ids for {} ({})",
					version->protocolMapping.size(),
					version->entityTypeMapping.size(),
					name,
					idx
		);
	}
}

acp::ProtocolVersion* acp::ProtocolVersion::byIdx(int idx)
{
	return versionByIdx.contains(idx) ? versionByIdx.at(idx) : nullptr;
}

const acp::ProtocolVersion acp::ProtocolVersion::v1_16_3 = { 753, "1.16.3" };
const acp::ProtocolVersion acp::ProtocolVersion::v1_16_4 = { 754, "1.16.4" };
const acp::ProtocolVersion acp::ProtocolVersion::v1_17 = { 755, "1.17" };
const acp::ProtocolVersion acp::ProtocolVersion::v1_17_1 = { 756, "1.17.1" };
const acp::ProtocolVersion acp::ProtocolVersion::v1_18 = { 757, "1.18" };
const acp::ProtocolVersion acp::ProtocolVersion::v1_18_2 = { 758, "1.18.2" };
const acp::ProtocolVersion acp::ProtocolVersion::v1_19 = { 759, "1.19" };
const acp::ProtocolVersion acp::ProtocolVersion::v1_19_1 = { 760, "1.19.1" };
const acp::ProtocolVersion acp::ProtocolVersion::v1_19_3 = { 761, "1.19.3" };
const acp::ProtocolVersion acp::ProtocolVersion::v1_19_4 = { 762, "1.19.4" };
const acp::ProtocolVersion acp::ProtocolVersion::v1_20 = { 763, "1.20" };
const acp::ProtocolVersion acp::ProtocolVersion::v1_20_2 = { 764, "1.20.2" };
const acp::ProtocolVersion acp::ProtocolVersion::v1_20_3 = { 765, "1.20.3" };
const acp::ProtocolVersion acp::ProtocolVersion::v1_20_5 = { 766, "1.20.5" };
const acp::ProtocolVersion acp::ProtocolVersion::v1_21 = { 767, "1.21" };
