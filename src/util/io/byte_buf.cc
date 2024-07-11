#include "byte_buf.hh"

acp::ByteBuf::ByteBuf(byte_t* bytes, size_t size) : bytes(bytes, bytes + size)
{
}



const byte_t* acp::ByteBuf::data() const
{
	return bytes.data();
}

size_t acp::ByteBuf::size() const
{
	return bytes.size();
}
