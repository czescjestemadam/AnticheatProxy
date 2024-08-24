#include "tag_end.hh"

void acp::nbt::TagEnd::read(ByteBuf& buf)
{
}

void acp::nbt::TagEnd::write(ByteBuf& buf)
{
}

std::unique_ptr<acp::nbt::Tag> acp::nbt::TagEnd::copy()
{
	return std::make_unique<TagEnd>();
}

acp::nbt::TagType acp::nbt::TagEnd::getType() const
{
	return TagType::END;
}

std::string acp::nbt::TagEnd::toString() const
{
	return EnumNames<TagType>::get(getType());
}
