#include "uuid.hh"

#include "hash.hh"

#include <format>
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
	std::string out;

	for (int i = 0; i < 16; ++i)
	{
		out += std::format("{:02x}", bytes[i]);

		if (i == 3 || i == 5 || i == 7 || i == 9)
			out += '-';
	}

	return out;
}

std::string acp::UUID::toStringShort() const
{
	std::string out;

	for (byte_t byte : bytes)
		out += std::format("{:02x}", byte);

	return out;
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

byte_t charHexValue(char c);

acp::UUID acp::UUID::parse(const std::string& str)
{
	if (str.length() != 36 && str.length() != 32)
		return {};

	UUID id;

	int idx = 0;
	for (int i = 0; i < str.length(); ++i)
	{
		const char c = str[i];
		if (c == '-')
			continue;

		if (i + 1 >= str.length())
			return {};

		const char c2 = str[++i];

		id.bytes[idx++] = charHexValue(std::tolower(c)) << 4 | charHexValue(std::tolower(c2));
	}

	return id;
}

byte_t charHexValue(char c)
{
	switch (c)
	{
		default:
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		case 'a': return 10;
		case 'b': return 11;
		case 'c': return 12;
		case 'd': return 13;
		case 'e': return 14;
		case 'f': return 15;
	}
}

acp::UUID acp::UUID::fromString(const std::string& str)
{
	UUID id;

	std::ranges::move(hash::md5(reinterpret_cast<const byte_t*>(str.data()), str.size()), id.bytes);
	id.setVersion(3);

	return id;
}
