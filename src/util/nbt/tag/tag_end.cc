#include "tag_end.hh"

void acp::nbt::TagEnd::read(ByteBuf& buf)
{
}

void acp::nbt::TagEnd::write(ByteBuf& buf)
{
}

acp::nbt::TagType acp::nbt::TagEnd::getType() const
{
	return TagType::END;
}

std::string acp::nbt::TagEnd::toString() const
{
	return EnumNames<TagType>::get(getType());
}
