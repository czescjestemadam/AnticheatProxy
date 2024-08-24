#pragma once
#include "util/nbt/tag.hh"

#include <format>

namespace acp::nbt
{
	template<TagType type, class T>
	class TagNumberArray : public Tag
	{
	protected:
		std::vector<T> arr;

	public:
		TagNumberArray() = default;
		TagNumberArray(TagNumberArray& tag) : arr(tag.arr)
		{
			name = tag.name;
		}
		explicit TagNumberArray(const std::vector<T>& arr) : arr(arr)
		{
		}

		void read(ByteBuf& buf) override
		{
			const int len = buf.readInt();
			readContents(buf, len);
		}

		void write(ByteBuf& buf) override
		{
			buf.writeInt(arr.size());
			writeContents(buf);
		}

		std::vector<T>& get()
		{
			return arr;
		}

		const std::vector<T>& get() const
		{
			return arr;
		}

		TagType getType() const override
		{
			return type;
		}

		std::string toString() const override
		{
			std::string arrStr;

			for (int i = 0; i < arr.size(); ++i)
			{
				const T& v = arr[i];
				arrStr += std::to_string(v);

				if (i + 1 < arr.size())
					arrStr += ", ";
			}

			return std::format("{}[{}]", EnumNames<TagType>::get(type), arrStr);
		}

	protected:
		virtual void readContents(ByteBuf& buf, int len) = 0;
		virtual void writeContents(ByteBuf& buf) = 0;
	};

	class TagByteArray : public TagNumberArray<TagType::BYTE_ARRAY, byte_t>
	{
	public:
		using TagNumberArray::TagNumberArray;

		std::unique_ptr<Tag> copy() override;

	protected:
		void readContents(ByteBuf& buf, int len) override;
		void writeContents(ByteBuf& buf) override;
	};

	class TagIntArray : public TagNumberArray<TagType::INT_ARRAY, int>
	{
	public:
		using TagNumberArray::TagNumberArray;

		std::unique_ptr<Tag> copy() override;

	protected:
		void readContents(ByteBuf& buf, int len) override;
		void writeContents(ByteBuf& buf) override;
	};

	class TagLongArray : public TagNumberArray<TagType::LONG_ARRAY, long>
	{
	public:
		using TagNumberArray::TagNumberArray;

		std::unique_ptr<Tag> copy() override;

	protected:
		void readContents(ByteBuf& buf, int len) override;
		void writeContents(ByteBuf& buf) override;
	};
}
