#pragma once
#include "tag_type.hh"
#include "util/io/byte_buf.hh"

#include <string>

namespace acp::nbt
{
	class Tag
	{
	protected:
		std::string name;

	public:
		virtual ~Tag() = default;

		virtual void read(ByteBuf& buf) = 0;
		virtual void write(ByteBuf& buf) = 0;

		void readName(ByteBuf& buf);
		void writeName(ByteBuf& buf);

		virtual TagType getType() const = 0;

		std::string getName() const;
		void setName(const std::string& name);

		virtual std::string toString() const = 0;


		static std::unique_ptr<Tag> createByType(TagType type);
	};
}
