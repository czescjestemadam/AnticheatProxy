#include "tag_number_array.hh"

// ==BYTE==
std::unique_ptr<acp::nbt::Tag> acp::nbt::TagByteArray::copy()
{
	return std::make_unique<TagByteArray>(*this);
}

void acp::nbt::TagByteArray::readContents(ByteBuf& buf, int len)
{
	for (int i = 0; i < len; ++i)
		arr.push_back(buf.readByte());
}

void acp::nbt::TagByteArray::writeContents(ByteBuf& buf)
{
	for (byte_t b : arr)
		buf.writeByte(b);
}

// ==INT==
std::unique_ptr<acp::nbt::Tag> acp::nbt::TagIntArray::copy()
{
	return std::make_unique<TagIntArray>(*this);
}

void acp::nbt::TagIntArray::readContents(ByteBuf& buf, int len)
{
	for (int i = 0; i < len; ++i)
		arr.push_back(buf.readInt());
}

void acp::nbt::TagIntArray::writeContents(ByteBuf& buf)
{
	for (int i : arr)
		buf.writeInt(i);
}

// ==LONG==
std::unique_ptr<acp::nbt::Tag> acp::nbt::TagLongArray::copy()
{
	return std::make_unique<TagLongArray>(*this);
}

void acp::nbt::TagLongArray::readContents(ByteBuf& buf, int len)
{
	for (int i = 0; i < len; ++i)
		arr.push_back(buf.readLong());
}

void acp::nbt::TagLongArray::writeContents(ByteBuf& buf)
{
	for (long l : arr)
		buf.writeLong(l);
}
