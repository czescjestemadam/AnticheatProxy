#pragma once
#include "i_properties.hh"

#include "util/enum_names.hh"

namespace acp
{
	namespace command
	{
		struct StringProperties : IProperties
		{
			enum class Type
			{
				SINGLE_WORD,
				QUOTABLE_PHRASE,
				GREEDY_PHRASE
			};

			Type type;

			StringProperties() = default;
			explicit StringProperties(Type type);

			ByteBuf serialize() override;
			void deserialize(ByteBuf& v) override;
		};
	}

	template<>
	struct EnumNames<command::StringProperties::Type>
	{
		static std::string get(command::StringProperties::Type val);
	};
}
