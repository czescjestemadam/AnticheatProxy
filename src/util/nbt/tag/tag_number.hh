#pragma once
#include "util/io/byte_buf.hh"
#include "util/nbt/tag.hh"
#include "util/nbt/tag_type.hh"

#include <format>

namespace acp::nbt
{
	template<TagType type, class T>
	class TagNumber : public Tag
	{
	protected:
		T val;

	public:
		TagNumber() = default;
		TagNumber(TagNumber& tag) : val(tag.val)
		{
			name = tag.name;
		}
		explicit TagNumber(T val) : val(val)
		{
		}

		T get() const
		{
			return val;
		}

		void set(T v)
		{
			val = v;
		}

		TagType getType() const override
		{
			return type;
		}

		std::string toString() const override
		{
			return std::format("{}[{}]", EnumNames<TagType>::get(type), val);
		}
	};

	class TagByte : public TagNumber<TagType::BYTE, byte_t>
	{
	public:
		using TagNumber::TagNumber;

		std::unique_ptr<Tag> copy() override;

		void read(ByteBuf& buf) override;
		void write(ByteBuf& buf) override;
	};

	class TagShort : public TagNumber<TagType::SHORT, short>
	{
	public:
		using TagNumber::TagNumber;

		std::unique_ptr<Tag> copy() override;

		void read(ByteBuf& buf) override;
		void write(ByteBuf& buf) override;
	};

	class TagInt : public TagNumber<TagType::INT, int>
	{
	public:
		using TagNumber::TagNumber;

		std::unique_ptr<Tag> copy() override;

		void read(ByteBuf& buf) override;
		void write(ByteBuf& buf) override;
	};

	class TagLong : public TagNumber<TagType::LONG, long>
	{
	public:
		using TagNumber::TagNumber;

		std::unique_ptr<Tag> copy() override;

		void read(ByteBuf& buf) override;
		void write(ByteBuf& buf) override;
	};

	class TagFloat : public TagNumber<TagType::FLOAT, float>
	{
	public:
		using TagNumber::TagNumber;

		std::unique_ptr<Tag> copy() override;

		void read(ByteBuf& buf) override;
		void write(ByteBuf& buf) override;
	};

	class TagDouble : public TagNumber<TagType::DOUBLE, double>
	{
	public:
		using TagNumber::TagNumber;

		std::unique_ptr<Tag> copy() override;

		void read(ByteBuf& buf) override;
		void write(ByteBuf& buf) override;
	};
}
