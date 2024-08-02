#pragma once
#include "i_properties.hh"

namespace acp::command
{
	struct FlagsProperties : IProperties
	{
		byte_t flags;

		FlagsProperties() = default;
		explicit FlagsProperties(byte_t flags);

		ByteBuf serialize() override;
		void deserialize(ByteBuf& v) override;
	};

	/// mask
	/// - @c 0x01: single entity / player
	/// - @c 0x02: only players
	typedef FlagsProperties EntityProperties;

	/// mask
	/// - @c 0x01: allows multiple
	typedef FlagsProperties ScoreHolderProperties;
}
