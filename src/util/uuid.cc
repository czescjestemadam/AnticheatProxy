#include "uuid.hh"

#include <random>

constexpr byte_t VERSION_BYTE_IDX = 6;

acp::UUID::UUID() : UUID(0, 0)
{
}

acp::UUID::UUID(unsigned long high, unsigned long low) : high(high), low(low)
{
}

unsigned long acp::UUID::getHigh() const
{
	return high;
}

unsigned long acp::UUID::getLow() const
{
	return low;
}

int acp::UUID::getVersion() const
{
	return bytes[VERSION_BYTE_IDX] >> 4;
}

void acp::UUID::setVersion(int ver)
{
	bytes[VERSION_BYTE_IDX] &= 0x0f;
	bytes[VERSION_BYTE_IDX] |= ver << 4 & 0xf0;
}

std::string acp::UUID::toString() const
{
	// TODO
	return "";
}

std::string acp::UUID::toStringShort() const
{
	// TODO
	return "";
}


bool acp::UUID::operator==(const UUID& rhs) const
{
	return high == rhs.high && low == rhs.low;
}

bool acp::UUID::operator!=(const UUID& rhs) const
{
	return !(*this == rhs);
}


acp::UUID acp::UUID::random()
{
	static std::random_device randomDevice;
	static std::mt19937_64 engine(randomDevice());
	static std::uniform_int_distribution<unsigned long> distribution;

	UUID id(distribution(engine), distribution(engine));
	id.setVersion(4);

	return id;
}

acp::UUID acp::UUID::parse(const std::string& str)
{
	// TODO

	return {};
}
