#include "number_properties.hh"

#define WRITE_IMPL(type, func) template<>										\
void acp::command::NumberProperties<type>::write(ByteBuf& buf, type val) const	\
{																				\
	buf.func(val);																\
}

#define READ_IMPL(type, func) template<>							\
type acp::command::NumberProperties<type>::read(ByteBuf& buf) const \
{																	\
	return buf.func();												\
}


WRITE_IMPL(float, writeFloat)
WRITE_IMPL(double, writeDouble)
WRITE_IMPL(int, writeInt)
WRITE_IMPL(long, writeLong)

READ_IMPL(float, readFloat)
READ_IMPL(double, readDouble)
READ_IMPL(int, readInt)
READ_IMPL(long, readLong)
