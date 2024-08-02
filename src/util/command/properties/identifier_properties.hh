#pragma once
#include "i_properties.hh"

namespace acp::command
{
	struct IdentifierProperties : IProperties
	{
		Identifier id;

		IdentifierProperties() = default;
		explicit IdentifierProperties(const Identifier& id);

		ByteBuf serialize() override;
		void deserialize(ByteBuf& v) override;
	};
}
