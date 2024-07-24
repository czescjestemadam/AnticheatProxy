#include "tag_string.hh"

#include <format>

acp::nbt::TagString::TagString(const std::string& val) : val(val)
{
}

void acp::nbt::TagString::read(ByteBuf& buf)
{
	const ushort len = buf.readShortU();
	byte_t cstr[len];
	buf.readBytes(cstr, len);
	val = { cstr, cstr + len };
}

void acp::nbt::TagString::write(ByteBuf& buf)
{
	const ushort len = val.length();
	buf.writeShortU(len);
	buf.writeBytes(reinterpret_cast<byte_t*>(val.data()), len);
}

std::string acp::nbt::TagString::get() const
{
	return val;
}

void acp::nbt::TagString::set(const std::string& val)
{
	this->val = val;
}

acp::nbt::TagType acp::nbt::TagString::getType() const
{
	return TagType::STRING;
}

std::string acp::nbt::TagString::toString() const
{
	return std::format("{}[{}]", EnumNames<TagType>::get(getType()), val);
}
