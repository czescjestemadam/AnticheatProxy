#pragma once
#include "util/uuid.hh"
#include "util/identifier.hh"
#include "util/vec3.hh"

#include <vector>

namespace acp
{
	class ByteBuf
	{
		std::vector<byte_t> bytes;

	public:
		ByteBuf() = default;
		ByteBuf(byte_t* bytes, size_t size);

		// byte
		byte_t readByte();
		void writeByte(byte_t v);

		void readBytes(byte_t* out, size_t len);
		void writeBytes(const byte_t* buf, size_t len);

		ByteBuf readBuf(size_t len);
		void writeBuf(const ByteBuf& buf);

		// var
		int readVarint();
		void writeVarint(int v);

		long readVarlong();
		void writeVarlong(long v);

		// signed
		short readShort();
		void writeShort(short v);

		int readInt();
		void writeInt(int v);

		long readLong();
		void writeLong(long v);

		// unsigned
		unsigned short readShortU();
		void writeShortU(unsigned short v);

		unsigned int readIntU();
		void writeIntU(unsigned int v);

		unsigned long readLongU();
		void writeLongU(unsigned long v);

		// float
		float readFloat();
		void writeFloat(float v);

		double readDouble();
		void writeDouble(double v);

		float readAngle();
		void writeAngle(float v);

		// misc
		std::string readStr();
		void writeStr(const std::string& v);

		UUID readUuid();
		void writeUuid(const UUID& uuid);

		Identifier readIdentifier();
		void writeIdentifier(const Identifier& v);

		Vec3i readPosition();
		void writePosition(const Vec3i& v);

		Vec3f readVec3f();
		void writeVec3f(const Vec3f& v);

		Vec3d readVec3d();
		void writeVec3d(const Vec3d& v);

		// zlib
		ByteBuf compress(int level = -1) const;
		ByteBuf decompress(int length) const;


		std::string toString() const;
		std::string toStringShort() const;

		const byte_t* data() const;
		size_t size() const;
		void clear();
	};
}
