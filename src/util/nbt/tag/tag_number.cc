#include "tag_number.hh"

#define TAG_READ_IMPL(type, func) void acp::nbt::type::read(ByteBuf& buf) { val = buf.func(); }
#define TAG_WRITE_IMPL(type, func) void acp::nbt::type::write(ByteBuf& buf) { buf.func(val); }

TAG_READ_IMPL(TagByte, readByte)
TAG_WRITE_IMPL(TagByte, writeByte)

TAG_READ_IMPL(TagShort, readShort)
TAG_WRITE_IMPL(TagShort, writeShort)

TAG_READ_IMPL(TagInt, readInt)
TAG_WRITE_IMPL(TagInt, writeInt)

TAG_READ_IMPL(TagLong, readLong)
TAG_WRITE_IMPL(TagLong, writeLong)

TAG_READ_IMPL(TagFloat, readFloat)
TAG_WRITE_IMPL(TagFloat, writeFloat)

TAG_READ_IMPL(TagDouble, readDouble)
TAG_WRITE_IMPL(TagDouble, writeDouble)
