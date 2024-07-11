#pragma once
#include "util/types.hh"

#include <vector>

namespace acp
{
	class ByteBuf
	{
		std::vector<byte_t> bytes;

	public:
		ByteBuf() = default;
		ByteBuf(byte_t* bytes, size_t size);

		byte_t readByte();
		void writeByte(byte_t v);

		// var
		int readVarint();
		void writeVarint(int v);

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

		// misc



		const byte_t* data() const;
		size_t size() const;
	};
}
