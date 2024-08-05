#include "byte_buf.hh"

#include "varint_exception.hh"
#include "z_lib_exception.hh"
#include "util/nbt/tag.hh"

#include <format>
#include <zlib.h>
#include <netinet/in.h>

#include "network/protocol/protocol_version.hh"

#define BUF_UNION(type) union { byte_t bytes[sizeof(type)]; type val; }

#define BUF_READ(type, wrapper)		\
	BUF_UNION(type);				\
	readBytes(bytes, sizeof(type));	\
	return wrapper(val)

#define BUF_WRITE(type, wrapper)	\
	BUF_UNION(type);				\
	val = wrapper(v);				\
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
	for (int i = 0; i < len; i++)
		out[i] = readByte();
}

void acp::ByteBuf::writeBytes(const byte_t* buf, size_t len)
{
	for (int i = 0; i < len; i++)
		bytes.push_back(buf[i]);
}

void acp::ByteBuf::readBytesR(byte_t* out, size_t len)
{
	for (int i = len - 1; i >= 0; i--)
		out[i] = readByte();
}

void acp::ByteBuf::writeBytesR(const byte_t* buf, size_t len)
{
	for (int i = len - 1; i >= 0; i--)
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
	BUF_READ(short, ntohs);
}

void acp::ByteBuf::writeShort(short v)
{
	BUF_WRITE(short, htons);
}

int acp::ByteBuf::readInt()
{
	BUF_READ(int, ntohl);
}

void acp::ByteBuf::writeInt(int v)
{
	BUF_WRITE(int, htonl);
}

long acp::ByteBuf::readLong()
{
	BUF_UNION(long);
	readBytesR(bytes, sizeof(long));
	return val;
}

void acp::ByteBuf::writeLong(long v)
{
	BUF_UNION(long);
	val = v;
	writeBytesR(bytes, sizeof(long));
}


unsigned short acp::ByteBuf::readShortU()
{
	BUF_READ(unsigned short, ntohs);
}

void acp::ByteBuf::writeShortU(unsigned short v)
{
	BUF_WRITE(unsigned short, htons);
}

unsigned int acp::ByteBuf::readIntU()
{
	BUF_READ(unsigned int, ntohl);
}

void acp::ByteBuf::writeIntU(unsigned int v)
{
	BUF_WRITE(unsigned int, htonl);
}

unsigned long acp::ByteBuf::readLongU()
{
	BUF_UNION(unsigned long);
	readBytesR(bytes, sizeof(unsigned long));
	return val;
}

void acp::ByteBuf::writeLongU(unsigned long v)
{
	BUF_UNION(unsigned long);
	val = v;
	writeBytesR(bytes, sizeof(unsigned long));
}

float acp::ByteBuf::readFloat()
{
	BUF_UNION(float);

	for (int i = sizeof(float) - 1; i >= 0; i--)
		bytes[i] = readByte();

	return val;
}

void acp::ByteBuf::writeFloat(float v)
{
	BUF_UNION(float);

	val = v;

	for (int i = sizeof(float) - 1; i >= 0; i--)
		writeByte(bytes[i]);
}

double acp::ByteBuf::readDouble()
{
	BUF_UNION(double);

	for (int i = sizeof(double) - 1; i >= 0; i--)
		bytes[i] = readByte();

	return val;
}

void acp::ByteBuf::writeDouble(double v)
{
	BUF_UNION(double);

	val = v;

	for (int i = sizeof(double) - 1; i >= 0; i--)
		writeByte(bytes[i]);
}

float acp::ByteBuf::readAngle()
{
	const float angle = readByte();
	return angle * 256.f / 360.f;
}

void acp::ByteBuf::writeAngle(float v)
{
	writeByte(static_cast<byte_t>(v / 360.f));
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
	UUID id;
	readBytes(id.getBytes(), 16);
	return id;
}

void acp::ByteBuf::writeUuid(const UUID& uuid)
{
	writeBytes(uuid.getBytes(), 16);
}

acp::Identifier acp::ByteBuf::readIdentifier()
{
	return Identifier::parse(readStr());
}

void acp::ByteBuf::writeIdentifier(const Identifier& v)
{
	writeStr(v.toString());
}

acp::Vec3i acp::ByteBuf::readPosition(int shiftX, int shiftY, int shiftZ)
{
	BUF_UNION(long);
	readBytesR(bytes, sizeof(long));
	return {
		static_cast<int>(val >> shiftX),
		static_cast<int>(val << shiftY >> shiftY),
		static_cast<int>(val << shiftZ >> shiftX)
	};
}

void acp::ByteBuf::writePosition(const Vec3i& v, int maskXZ, int maskY, int shiftX, int shiftZ)
{
	BUF_UNION(long);
	val = static_cast<long>(v.x & maskXZ) << shiftX | static_cast<long>(v.z & maskXZ) << shiftZ | v.y & maskY;
	writeBytesR(bytes, sizeof(long));
}

acp::Vec3s acp::ByteBuf::readVec3s()
{
	Vec3s v;
	v.x = readShort();
	v.y = readShort();
	v.z = readShort();
	return v;
}

void acp::ByteBuf::writeVec3s(const Vec3s& v)
{
	writeShort(v.x);
	writeShort(v.y);
	writeShort(v.z);
}

acp::Vec3f acp::ByteBuf::readVec3f()
{
	Vec3f v;
	v.x = readFloat();
	v.y = readFloat();
	v.z = readFloat();
	return v;
}

void acp::ByteBuf::writeVec3f(const Vec3f& v)
{
	writeFloat(v.x);
	writeFloat(v.y);
	writeFloat(v.z);
}

acp::Vec3d acp::ByteBuf::readVec3d()
{
	Vec3d v;
	v.x = readDouble();
	v.y = readDouble();
	v.z = readDouble();
	return v;
}

void acp::ByteBuf::writeVec3d(const Vec3d& v)
{
	writeDouble(v.x);
	writeDouble(v.y);
	writeDouble(v.z);
}

std::unique_ptr<acp::nbt::Tag> acp::ByteBuf::readNbt(bool readName)
{
	const auto type = static_cast<nbt::TagType>(readByte());

	std::unique_ptr<nbt::Tag> tag = nbt::Tag::createByType(type);
	if (readName)
		tag->readName(*this);
	tag->read(*this);

	return tag;
}

void acp::ByteBuf::writeNbt(std::unique_ptr<nbt::Tag>& v, bool writeName)
{
	writeByte(static_cast<byte_t>(v->getType()));
	if (writeName)
		v->writeName(*this);
	v->write(*this);
}

acp::GameProfile acp::ByteBuf::readGameProfile(bool readProperties)
{
	GameProfile profile;
	profile.uuid = readUuid();
	profile.username = readStr();

	if (readProperties)
	{
		const int len = readVarint();
		for (int i = 0; i < len; ++i)
			profile.properties.emplace_back(readStr(), readStr(), readByte() ? readStr() : "");
	}

	return profile;
}

void acp::ByteBuf::writeGameProfile(const GameProfile& profile, bool writeProperties)
{
	writeUuid(profile.uuid);
	writeStr(profile.username);

	if (writeProperties)
	{
		writeVarint(static_cast<int>(profile.properties.size()));
		for (const GameProfile::Property& property : profile.properties)
		{
			writeStr(property.name);
			writeStr(property.value);

			const bool signaturePresent = !property.signature.empty();
			writeByte(signaturePresent);
			if (signaturePresent)
				writeStr(property.signature);
		}
	}
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

void acp::ByteBuf::clear()
{
	bytes.clear();
}
