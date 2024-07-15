#include "byte_buf.hh"

#include "varint_exception.hh"
#include "z_lib_exception.hh"

#include <format>
#include <zlib.h>

#define BUF_UNION(type) union { byte_t bytes[sizeof(type)]; type val; }

#define BUF_READ(type)					\
	BUF_UNION(type);					\
	readBytes(bytes, sizeof(type));	\
	return val

#define BUF_WRITE(type)					\
	BUF_UNION(type);					\
	val = v;							\
	writeBytes(bytes, sizeof(type))


acp::ByteBuf::ByteBuf(byte_t* bytes, size_t size) : bytes(bytes, bytes + size)
{
}


byte_t acp::ByteBuf::readByte()
{
	const byte_t byte = bytes.front();
	bytes.erase(bytes.begin());
	return byte;
}

void acp::ByteBuf::writeByte(byte_t v)
{
	bytes.push_back(v);
}

void acp::ByteBuf::readBytes(byte_t* out, size_t len)
{
	for (int i = 0; i < len; ++i)
		out[i] = readByte();
}

void acp::ByteBuf::writeBytes(const byte_t* buf, size_t len)
{
	for (int i = 0; i < len; ++i)
		bytes.push_back(buf[i]);
}

acp::ByteBuf acp::ByteBuf::readBuf(size_t len)
{
	byte_t bytes[len];
	readBytes(bytes, len);
	return { bytes, len };
}

void acp::ByteBuf::writeBuf(const ByteBuf& buf)
{
	writeBytes(buf.data(), buf.size());
}


int acp::ByteBuf::readVarint()
{
	int val = 0;
	int pos = 0;
	byte_t cur;

	while (true)
	{
		cur = readByte();
		val |= (cur & 0x7f) << pos;

		if ((cur & 0x80) == 0)
			break;

		pos += 7;

		if (pos >= 32)
			throw VarintException();
	}

	return val;
}

void acp::ByteBuf::writeVarint(int v)
{
	while (true)
	{
		if ((v & ~0x7f) == 0)
		{
			writeByte(byte_t(v));
			return;
		}
		writeByte(byte_t((v & 0x7f) | 0x80));
		v = uint(v) >> 7;
	}
}

long acp::ByteBuf::readVarlong()
{
	long val = 0;
	int pos = 0;
	byte_t cur;

	while (true)
	{
		cur = readByte();
		val |= static_cast<long>(cur & 0x7f) << pos;

		if ((cur & 0x80) == 0)
			break;

		pos += 7;

		if (pos >= 64)
			throw VarintException();
	}

	return val;
}

void acp::ByteBuf::writeVarlong(long v)
{
	while (true)
	{
		if ((v & ~0x7f) == 0)
		{
			writeByte(byte_t(v));
			return;
		}
		writeByte(byte_t((v & 0x7f) | 0x80));
		v = ulong(v) >> 7;
	}
}


short acp::ByteBuf::readShort()
{
	BUF_READ(short);
}

void acp::ByteBuf::writeShort(short v)
{
	BUF_WRITE(short);
}

int acp::ByteBuf::readInt()
{
	BUF_READ(int);
}

void acp::ByteBuf::writeInt(int v)
{
	BUF_WRITE(int);
}

long acp::ByteBuf::readLong()
{
	BUF_READ(long);
}

void acp::ByteBuf::writeLong(long v)
{
	BUF_WRITE(long);
}


unsigned short acp::ByteBuf::readShortU()
{
	BUF_READ(unsigned short);
}

void acp::ByteBuf::writeShortU(unsigned short v)
{
	BUF_WRITE(unsigned short);
}

unsigned int acp::ByteBuf::readIntU()
{
	BUF_READ(unsigned int);
}

void acp::ByteBuf::writeIntU(unsigned int v)
{
	BUF_WRITE(unsigned int);
}

unsigned long acp::ByteBuf::readLongU()
{
	BUF_READ(unsigned long);
}

void acp::ByteBuf::writeLongU(unsigned long v)
{
	BUF_WRITE(unsigned long);
}


std::string acp::ByteBuf::readStr()
{
	const int len = readVarint();
	byte_t cstr[len];
	readBytes(cstr, len);
	return { cstr, cstr + len };
}

void acp::ByteBuf::writeStr(const std::string& v)
{
	writeVarint(static_cast<int>(v.size()));
	writeBytes(reinterpret_cast<const byte_t*>(v.data()), v.size());
}

acp::UUID acp::ByteBuf::readUuid()
{
	unsigned long high = readLongU();
	unsigned long low = readLongU();
	return { high, low };
}

void acp::ByteBuf::writeUuid(const UUID& uuid)
{
	writeLongU(uuid.getHigh());
	writeLongU(uuid.getLow());
}

acp::Identifier acp::ByteBuf::readIdentifier()
{
	return Identifier::parse(readStr());
}

void acp::ByteBuf::writeIdentifier(const Identifier& v)
{
	writeStr(v.toString());
}


acp::ByteBuf acp::ByteBuf::compress(int level) const
{
	size_t dstLen = compressBound(size());
	byte_t dst[dstLen];

	int code = compress2(dst, &dstLen, data(), size(), level);
	if (code < 0)
		throw ZLibException(code);

	return { dst, dstLen };
}

acp::ByteBuf acp::ByteBuf::decompress(int length) const
{
	size_t dstLen = length;
	byte_t dst[dstLen];

	int code = uncompress(dst, &dstLen, data(), size());
	if (code < 0)
		throw ZLibException(code);

	return { dst, dstLen };
}


std::string acp::ByteBuf::toString() const
{
	std::string byteStr;
	byteStr.reserve(bytes.size() * 5 - 1);

	for (int i = 0; i < bytes.size(); ++i)
	{
		byteStr += std::format("0x{:02x}", bytes[i]);

		if (i + 1 < bytes.size())
			byteStr += ' ';
	}

	return std::format("ByteBuf[{}]{{{}}}", bytes.size(), byteStr);
}

std::string acp::ByteBuf::toStringShort() const
{
	std::string out;
	out.reserve(bytes.size() * 2);

	for (byte_t byte : bytes)
		out += std::format("{:02x}", byte);

	return out;
}

const byte_t* acp::ByteBuf::data() const
{
	return bytes.data();
}

size_t acp::ByteBuf::size() const
{
	return bytes.size();
}
