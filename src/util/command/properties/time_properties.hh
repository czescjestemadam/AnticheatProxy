#pragma once
#include "i_properties.hh"

namespace acp::command
{
	struct TimeProperties : IProperties
	{
		/// ticks
		int min;

		TimeProperties() = default;
		explicit TimeProperties(int min);

		ByteBuf serialize() override;
		void deserialize(ByteBuf& v) override;
	};
}
