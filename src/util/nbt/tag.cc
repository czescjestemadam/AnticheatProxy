#include "tag.hh"

#include "tag/tag_compound.hh"
#include "tag/tag_end.hh"
#include "tag/tag_list.hh"
#include "tag/tag_number.hh"
#include "tag/tag_number_array.hh"
#include "tag/tag_string.hh"

void acp::nbt::Tag::readName(ByteBuf& buf)
{
	const ushort len = buf.readShortU();
	byte_t cstr[len];
	buf.readBytes(cstr, len);
	name = { cstr, cstr + len };
}

void acp::nbt::Tag::writeName(ByteBuf& buf)
{
	const ushort len = name.length();
	buf.writeShortU(len);
	buf.writeBytes(reinterpret_cast<byte_t*>(name.data()), len);
}

std::string acp::nbt::Tag::getName() const
{
	return name;
}

void acp::nbt::Tag::setName(const std::string& name)
{
	this->name = name;
}


std::unique_ptr<acp::nbt::Tag> acp::nbt::Tag::createByType(TagType type)
{
	switch (type)
	{
		case TagType::END: return std::make_unique<TagEnd>();
		case TagType::BYTE: return std::make_unique<TagByte>();
		case TagType::SHORT: return std::make_unique<TagShort>();
		case TagType::INT: return std::make_unique<TagInt>();
		case TagType::LONG: return std::make_unique<TagLong>();
		case TagType::FLOAT: return std::make_unique<TagFloat>();
		case TagType::DOUBLE: return std::make_unique<TagDouble>();
		case TagType::BYTE_ARRAY: return std::make_unique<TagByteArray>();
		case TagType::STRING: return std::make_unique<TagString>();
		case TagType::LIST: return std::make_unique<TagList>();
		case TagType::COMPOUND: return std::make_unique<TagCompound>();
		case TagType::INT_ARRAY: return std::make_unique<TagIntArray>();
		case TagType::LONG_ARRAY: return std::make_unique<TagLongArray>();
		default: return nullptr;
	}
}
