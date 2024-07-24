#pragma once
#include "util/enum_names.hh"

namespace acp
{
	namespace nbt
	{
		enum class TagType
		{
			END,
			BYTE,
			SHORT,
			INT,
			LONG,
			FLOAT,
			DOUBLE,
			BYTE_ARRAY,
			STRING,
			LIST,
			COMPOUND,
			INT_ARRAY,
			LONG_ARRAY
		};
	}

	template<>
	struct EnumNames<nbt::TagType>
	{
		static std::string get(nbt::TagType val)
		{
			switch (val)
			{
				case nbt::TagType::END: return "END";
				case nbt::TagType::BYTE: return "BYTE";
				case nbt::TagType::SHORT: return "SHORT";
				case nbt::TagType::INT: return "INT";
				case nbt::TagType::LONG: return "LONG";
				case nbt::TagType::FLOAT: return "FLOAT";
				case nbt::TagType::DOUBLE: return "DOUBLE";
				case nbt::TagType::BYTE_ARRAY: return "BYTE_ARRAY";
				case nbt::TagType::STRING: return "STRING";
				case nbt::TagType::LIST: return "LIST";
				case nbt::TagType::COMPOUND: return "COMPOUND";
				case nbt::TagType::INT_ARRAY: return "INT_ARRAY";
				case nbt::TagType::LONG_ARRAY: return "LONG_ARRAY";
				default: return "unknown";
			}
		}
	};
}
