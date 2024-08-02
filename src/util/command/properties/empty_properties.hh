#pragma once
#include "i_properties.hh"

namespace acp::command
{
	struct EmptyProperties : IProperties
	{
		ByteBuf serialize() override;
		void deserialize(ByteBuf& v) override;
	};
}
