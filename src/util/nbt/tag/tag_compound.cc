#include "tag_compound.hh"

acp::nbt::TagCompound::TagCompound(TagCompound& tag)
{
	name = tag.name;
	for (const auto& [key, val] : tag.tags)
		tags[key] = val->copy();
}

acp::nbt::TagCompound::TagCompound(std::unordered_map<std::string, std::unique_ptr<Tag>>&& tags) : tags(std::move(tags))
{
}

void acp::nbt::TagCompound::read(ByteBuf& buf)
{
	for (TagType type = static_cast<TagType>(buf.readByte()); type != TagType::END; type = static_cast<TagType>(buf.readByte()))
	{
		std::unique_ptr<Tag> tag = createByType(type);
		tag->readName(buf);
		tag->read(buf);

		tags[tag->getName()] = std::move(tag);
	}
}

void acp::nbt::TagCompound::write(ByteBuf& buf)
{
	for (auto& [name, tag] : tags)
	{
		buf.writeByte(static_cast<byte_t>(tag->getType()));
		tag->setName(name);
		tag->writeName(buf);
		tag->write(buf);
	}

	buf.writeByte(static_cast<byte_t>(TagType::END));
}

std::unique_ptr<acp::nbt::Tag> acp::nbt::TagCompound::copy()
{
	return std::make_unique<TagCompound>(*this);
}

std::unordered_map<std::string, std::unique_ptr<acp::nbt::Tag>>& acp::nbt::TagCompound::get()
{
	return tags;
}

const std::unordered_map<std::string, std::unique_ptr<acp::nbt::Tag>>& acp::nbt::TagCompound::get() const
{
	return tags;
}

bool acp::nbt::TagCompound::contains(const std::string& name) const
{
	return tags.contains(name);
}

std::unique_ptr<acp::nbt::Tag>& acp::nbt::TagCompound::get(const std::string& name)
{
	return tags[name];
}

const std::unique_ptr<acp::nbt::Tag>& acp::nbt::TagCompound::get(const std::string& name) const
{
	return tags.at(name);
}

void acp::nbt::TagCompound::set(const std::string& name, std::unique_ptr<Tag>&& tag)
{
	tags[name] = std::move(tag);
}

acp::nbt::TagType acp::nbt::TagCompound::getType() const
{
	return TagType::COMPOUND;
}

std::string acp::nbt::TagCompound::toString() const
{
	std::string mapStr;

	size_t idx = 0;
	for (auto& [name, tag] : tags)
	{
		mapStr += std::format("\"{}\":{}", name, tag->toString());

		if (++idx < tags.size())
			mapStr += ", ";
	}

	return std::format("{}[{}]", EnumNames<TagType>::get(getType()), mapStr);
}
