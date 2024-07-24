#include "tag_list.hh"

#include <utility>

acp::nbt::TagList::TagList(std::vector<std::unique_ptr<Tag>>&& elements) : arr(std::move(elements))
{
}

void acp::nbt::TagList::read(ByteBuf& buf)
{
	const TagType type = static_cast<TagType>(buf.readByte());

	const int len = buf.readInt();
	for (int i = 0; i < len; ++i)
	{
		std::unique_ptr<Tag> tag = createByType(type);
		tag->read(buf);
		arr.push_back(std::move(tag));
	}
}

void acp::nbt::TagList::write(ByteBuf& buf)
{
	buf.writeByte(static_cast<byte_t>(arr.empty() ? TagType::END : arr[0]->getType()));

	buf.writeInt(static_cast<int>(arr.size()));
	for (std::unique_ptr<Tag>& element : arr)
		element->write(buf);
}

std::vector<std::unique_ptr<acp::nbt::Tag>>& acp::nbt::TagList::get()
{
	return arr;
}

const std::vector<std::unique_ptr<acp::nbt::Tag>>& acp::nbt::TagList::get() const
{
	return arr;
}

void acp::nbt::TagList::set(std::vector<std::unique_ptr<Tag>>&& arr)
{
	this->arr = std::move(arr);
}

acp::nbt::TagType acp::nbt::TagList::getType() const
{
	return TagType::LIST;
}

std::string acp::nbt::TagList::toString() const
{
	std::string arrStr;

	for (int i = 0; i < arr.size(); ++i)
	{
		arrStr += arr[i]->toString();

		if (i + 1 < arr.size())
			arrStr += ", ";
	}

	return std::format("{}[{}]", EnumNames<TagType>::get(getType()), arrStr);
}
