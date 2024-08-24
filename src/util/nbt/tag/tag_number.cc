#include "tag_number.hh"

#define TAG_COPY_IMPL(type) std::unique_ptr<acp::nbt::Tag> acp::nbt::type::copy() { return std::make_unique<type>(*this); }
#define TAG_READ_IMPL(type, func) void acp::nbt::type::read(ByteBuf& buf) { val = buf.func(); }
#define TAG_WRITE_IMPL(type, func) void acp::nbt::type::write(ByteBuf& buf) { buf.func(val); }

TAG_COPY_IMPL(TagByte)
TAG_READ_IMPL(TagByte, readByte)
TAG_WRITE_IMPL(TagByte, writeByte)

TAG_COPY_IMPL(TagShort)
TAG_READ_IMPL(TagShort, readShort)
TAG_WRITE_IMPL(TagShort, writeShort)

TAG_COPY_IMPL(TagInt)
TAG_READ_IMPL(TagInt, readInt)
TAG_WRITE_IMPL(TagInt, writeInt)

TAG_COPY_IMPL(TagLong)
TAG_READ_IMPL(TagLong, readLong)
TAG_WRITE_IMPL(TagLong, writeLong)

TAG_COPY_IMPL(TagFloat)
TAG_READ_IMPL(TagFloat, readFloat)
TAG_WRITE_IMPL(TagFloat, writeFloat)

TAG_COPY_IMPL(TagDouble)
TAG_READ_IMPL(TagDouble, readDouble)
TAG_WRITE_IMPL(TagDouble, writeDouble)
