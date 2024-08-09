#include "parser.hh"

#include "network/protocol/protocol_version.hh"
#include "util/command/properties/flags_properties.hh"
#include "util/command/properties/identifier_properties.hh"
#include "util/command/properties/number_properties.hh"
#include "util/command/properties/string_properties.hh"
#include "util/command/properties/time_properties.hh"

#include <utility>

static std::unordered_map<std::string, acp::command::Parser*> parsersByIdentifier;

acp::command::Parser::Parser(Identifier&& identifier, const std::vector<std::pair<const ProtocolVersion*, int>>& ids,
							 std::function<std::unique_ptr<IProperties>()>&& propertiesConstructor)
	: identifier(identifier), ids(ids), propertiesConstructor(std::move(propertiesConstructor))
{
	std::sort(this->ids.begin(), this->ids.end(), [](const std::pair<const ProtocolVersion*, int>& lhs,
													 const std::pair<const ProtocolVersion*, int>& rhs)
	{
		return *lhs.first > *rhs.first;
	});

	parsersByIdentifier[identifier.toString()] = this;
}

const acp::Identifier& acp::command::Parser::getIdentifier() const
{
	return identifier;
}

int acp::command::Parser::getId(const ProtocolVersion* version) const
{
	for (auto& [pvn, id] : ids)
		if (*version >= *pvn)
			return id;

	return -1;
}

std::unique_ptr<acp::command::IProperties> acp::command::Parser::createProperties() const
{
	return propertiesConstructor();
}


const acp::command::Parser* acp::command::Parser::byName(const std::string& name)
{
	return parsersByIdentifier.contains(name) ? parsersByIdentifier[name] : nullptr;
}

const acp::command::Parser acp::command::Parser::BOOL = {
	{ "brigadier", "bool" },
	{
		{ &ProtocolVersion::v1_19, 0 }
	}
};
const acp::command::Parser acp::command::Parser::FLOAT = {
	{ "brigadier", "float" },
	{
		{ &ProtocolVersion::v1_19, 1 }
	},
	[] { return std::make_unique<NumberProperties<float>>(); }
};
const acp::command::Parser acp::command::Parser::DOUBLE = {
	{ "brigadier", "double" },
	{
		{ &ProtocolVersion::v1_19, 2 }
	},
	[] { return std::make_unique<NumberProperties<double>>(); }
};
const acp::command::Parser acp::command::Parser::INTEGER = {
	{ "brigadier", "integer" },
	{
		{ &ProtocolVersion::v1_19, 3 }
	},
	[] { return std::make_unique<NumberProperties<int>>(); }
};
const acp::command::Parser acp::command::Parser::LONG = {
	{ "brigadier", "long" },
	{
		{ &ProtocolVersion::v1_19, 4 }
	},
	[] { return std::make_unique<NumberProperties<long>>(); }
};
const acp::command::Parser acp::command::Parser::STRING = {
	{ "brigadier", "string" },
	{
		{ &ProtocolVersion::v1_19, 5 }
	},
	[] { return std::make_unique<StringProperties>(); }
};
const acp::command::Parser acp::command::Parser::ENTITY = {
	{ "minecraft", "entity" },
	{
		{ &ProtocolVersion::v1_19, 6 }
	},
	[] { return std::make_unique<EntityProperties>(); }
};
const acp::command::Parser acp::command::Parser::GAME_PROFILE = {
	{ "minecraft", "game_profile" },
	{
		{ &ProtocolVersion::v1_19, 7 }
	}
};
const acp::command::Parser acp::command::Parser::BLOCK_POS = {
	{ "minecraft", "block_pos" },
	{
		{ &ProtocolVersion::v1_19, 8 }
	}
};
const acp::command::Parser acp::command::Parser::COLUMN_POS = {
	{ "minecraft", "column_pos" },
	{
		{ &ProtocolVersion::v1_19, 9 }
	}
};
const acp::command::Parser acp::command::Parser::VEC3 = {
	{ "minecraft", "vec3" },
	{
		{ &ProtocolVersion::v1_19, 10 }
	}
};
const acp::command::Parser acp::command::Parser::VEC2 = {
	{ "minecraft", "vec2" },
	{
		{ &ProtocolVersion::v1_19, 11 }
	}
};
const acp::command::Parser acp::command::Parser::BLOCK_STATE = {
	{ "minecraft", "block_state" },
	{
		{ &ProtocolVersion::v1_19, 12 }
	}
};
const acp::command::Parser acp::command::Parser::BLOCK_PREDICATE = {
	{ "minecraft", "block_predicate" },
	{
		{ &ProtocolVersion::v1_19, 13 }
	}
};
const acp::command::Parser acp::command::Parser::ITEM_STACK = {
	{ "minecraft", "item_stack" },
	{
		{ &ProtocolVersion::v1_19, 14 }
	}
};
const acp::command::Parser acp::command::Parser::ITEM_PREDICATE = {
	{ "minecraft", "item_predicate" },
	{
		{ &ProtocolVersion::v1_19, 15 }
	}
};
const acp::command::Parser acp::command::Parser::COLOR = {
	{ "minecraft", "color" },
	{
		{ &ProtocolVersion::v1_19, 16 }
	}
};
const acp::command::Parser acp::command::Parser::COMPONENT = {
	{ "minecraft", "component" },
	{
		{ &ProtocolVersion::v1_19, 17 }
	}
};
const acp::command::Parser acp::command::Parser::STYLE = {
	{ "minecraft", "style" },
	{
		{ &ProtocolVersion::v1_20_3, 18 }
	}
};
const acp::command::Parser acp::command::Parser::MESSAGE = {
	{ "minecraft", "message" },
	{
		{ &ProtocolVersion::v1_20_3, 19 },
		{ &ProtocolVersion::v1_19, 18 }
	}
};
const acp::command::Parser acp::command::Parser::NBT = {
	{ "minecraft", "nbt" },
	{
		{ &ProtocolVersion::v1_20_3, 20 },
		{ &ProtocolVersion::v1_19, 19 }
	}
};
const acp::command::Parser acp::command::Parser::NBT_TAG = {
	{ "minecraft", "nbt_tag" },
	{
		{ &ProtocolVersion::v1_20_3, 21 },
		{ &ProtocolVersion::v1_19, 20 }
	}
};
const acp::command::Parser acp::command::Parser::NBT_PATH = {
	{ "minecraft", "nbt_path" },
	{
		{ &ProtocolVersion::v1_20_3, 22 },
		{ &ProtocolVersion::v1_19, 21 }
	}
};
const acp::command::Parser acp::command::Parser::OBJECTIVE = {
	{ "minecraft", "objective" },
	{
		{ &ProtocolVersion::v1_20_3, 23 },
		{ &ProtocolVersion::v1_19, 22 }
	}
};
const acp::command::Parser acp::command::Parser::OBJECTIVE_CRITERIA = {
	{ "minecraft", "objective_criteria" },
	{
		{ &ProtocolVersion::v1_20_3, 24 },
		{ &ProtocolVersion::v1_19, 23 }
	}
};
const acp::command::Parser acp::command::Parser::OPERATION = {
	{ "minecraft", "operation" },
	{
		{ &ProtocolVersion::v1_20_3, 25 },
		{ &ProtocolVersion::v1_19, 24 }
	}
};
const acp::command::Parser acp::command::Parser::PARTICLE = {
	{ "minecraft", "particle" },
	{
		{ &ProtocolVersion::v1_20_3, 26 },
		{ &ProtocolVersion::v1_19, 25 }
	}
};
const acp::command::Parser acp::command::Parser::ANGLE = {
	{ "minecraft", "angle" },
	{
		{ &ProtocolVersion::v1_20_3, 27 },
		{ &ProtocolVersion::v1_19, 26 }
	}
};
const acp::command::Parser acp::command::Parser::ROTATION = {
	{ "minecraft", "rotation" },
	{
		{ &ProtocolVersion::v1_20_3, 28 },
		{ &ProtocolVersion::v1_19, 27 }
	}
};
const acp::command::Parser acp::command::Parser::SCOREBOARD_SLOT = {
	{ "minecraft", "scoreboard_slot" },
	{
		{ &ProtocolVersion::v1_20_3, 29 },
		{ &ProtocolVersion::v1_19, 28 }
	}
};
const acp::command::Parser acp::command::Parser::SCORE_HOLDER = {
	{ "minecraft", "score_holder" },
	{
		{ &ProtocolVersion::v1_20_3, 30 },
		{ &ProtocolVersion::v1_19, 29 }
	},
	[] { return std::make_unique<ScoreHolderProperties>(); }
};
const acp::command::Parser acp::command::Parser::SWIZZLE = {
	{ "minecraft", "swizzle" },
	{
		{ &ProtocolVersion::v1_20_3, 31 },
		{ &ProtocolVersion::v1_19, 30 }
	}
};
const acp::command::Parser acp::command::Parser::TEAM = {
	{ "minecraft", "team" },
	{
		{ &ProtocolVersion::v1_20_3, 32 },
		{ &ProtocolVersion::v1_19, 31 }
	}
};
const acp::command::Parser acp::command::Parser::ITEM_SLOT = {
	{ "minecraft", "item_slot" },
	{
		{ &ProtocolVersion::v1_20_3, 33 },
		{ &ProtocolVersion::v1_19, 32 }
	}
};
const acp::command::Parser acp::command::Parser::ITEM_SLOTS = {
	{ "minecraft", "item_slots" },
	{
		{ &ProtocolVersion::v1_20_5, 34 }
	}
};
const acp::command::Parser acp::command::Parser::RESOURCE_LOCATION = {
	{ "minecraft", "resource_location" },
	{
		{ &ProtocolVersion::v1_20_5, 35 },
		{ &ProtocolVersion::v1_20_3, 34 },
		{ &ProtocolVersion::v1_19, 33 }
	}
};
const acp::command::Parser acp::command::Parser::MOB_EFFECT = {
	{ "minecraft", "mob_effect" },
	{
		{ &ProtocolVersion::v1_19_3, -1 },
		{ &ProtocolVersion::v1_19, 34 }
	}
};
const acp::command::Parser acp::command::Parser::FUNCTION = {
	{ "minecraft", "function" },
	{
		{ &ProtocolVersion::v1_20_5, 36 },
		{ &ProtocolVersion::v1_20_3, 35 },
		{ &ProtocolVersion::v1_19_3, 34 },
		{ &ProtocolVersion::v1_19, 35 }
	}
};
const acp::command::Parser acp::command::Parser::ENTITY_ANCHOR = {
	{ "minecraft", "entity_anchor" },
	{
		{ &ProtocolVersion::v1_20_5, 37 },
		{ &ProtocolVersion::v1_20_3, 36 },
		{ &ProtocolVersion::v1_19_3, 35 },
		{ &ProtocolVersion::v1_19, 36 }
	}
};
const acp::command::Parser acp::command::Parser::INT_RANGE = {
	{ "minecraft", "int_range" },
	{
		{ &ProtocolVersion::v1_20_5, 38 },
		{ &ProtocolVersion::v1_20_3, 37 },
		{ &ProtocolVersion::v1_19_3, 36 },
		{ &ProtocolVersion::v1_19, 37 }
	}
};
const acp::command::Parser acp::command::Parser::FLOAT_RANGE = {
	{ "minecraft", "float_range" },
	{
		{ &ProtocolVersion::v1_20_5, 39 },
		{ &ProtocolVersion::v1_20_3, 38 },
		{ &ProtocolVersion::v1_19_3, 37 },
		{ &ProtocolVersion::v1_19, 38 }
	}
};
const acp::command::Parser acp::command::Parser::DIMENSION = {
	{ "minecraft", "dimension" },
	{
		{ &ProtocolVersion::v1_20_5, 40 },
		{ &ProtocolVersion::v1_20_3, 39 },
		{ &ProtocolVersion::v1_19_3, 38 },
		{ &ProtocolVersion::v1_19, 41 }
	}
};
const acp::command::Parser acp::command::Parser::GAMEMODE = {
	{ "minecraft", "gamemode" },
	{
		{ &ProtocolVersion::v1_20_5, 41 },
		{ &ProtocolVersion::v1_20_3, 40 },
		{ &ProtocolVersion::v1_19_3, 39 }
	}
};
const acp::command::Parser acp::command::Parser::TIME = {
	{ "minecraft", "time" },
	{
		{ &ProtocolVersion::v1_20_5, 42 },
		{ &ProtocolVersion::v1_20_3, 41 },
		{ &ProtocolVersion::v1_19_3, 40 },
		{ &ProtocolVersion::v1_19, 42 }
	},
	[] { return std::make_unique<TimeProperties>(); }
};
const acp::command::Parser acp::command::Parser::RESOURCE_OR_TAG = {
	{ "minecraft", "resource_or_tag" },
	{
		{ &ProtocolVersion::v1_20_5, 43 },
		{ &ProtocolVersion::v1_20_3, 42 },
		{ &ProtocolVersion::v1_19_3, 41 },
		{ &ProtocolVersion::v1_19, 43 }
	},
	[] { return std::make_unique<IdentifierProperties>(); }
};
const acp::command::Parser acp::command::Parser::RESOURCE_OR_TAG_KEY = {
	{ "minecraft", "resource_or_tag_key" },
	{
		{ &ProtocolVersion::v1_20_5, 44 },
		{ &ProtocolVersion::v1_20_3, 43 },
		{ &ProtocolVersion::v1_19_3, 42 }
	},
	[] { return std::make_unique<IdentifierProperties>(); }
};
const acp::command::Parser acp::command::Parser::RESOURCE = {
	{ "minecraft", "resource" },
	{
		{ &ProtocolVersion::v1_20_5, 45 },
		{ &ProtocolVersion::v1_20_3, 44 },
		{ &ProtocolVersion::v1_19_3, 43 },
		{ &ProtocolVersion::v1_19, 44 }
	},
	[] { return std::make_unique<IdentifierProperties>(); }
};
const acp::command::Parser acp::command::Parser::RESOURCE_KEY = {
	{ "minecraft", "resource_key" },
	{
		{ &ProtocolVersion::v1_20_5, 46 },
		{ &ProtocolVersion::v1_20_3, 45 },
		{ &ProtocolVersion::v1_19_3, 44 }
	},
	[] { return std::make_unique<IdentifierProperties>(); }
};
const acp::command::Parser acp::command::Parser::TEMPLATE_MIRROR = {
	{ "minecraft", "template_mirror" },
	{
		{ &ProtocolVersion::v1_20_5, 47 },
		{ &ProtocolVersion::v1_20_3, 46 },
		{ &ProtocolVersion::v1_19_3, 45 }
	}
};
const acp::command::Parser acp::command::Parser::TEMPLATE_ROTATION = {
	{ "minecraft", "template_rotation" },
	{
		{ &ProtocolVersion::v1_20_5, 48 },
		{ &ProtocolVersion::v1_20_3, 47 },
		{ &ProtocolVersion::v1_19_3, 46 }
	}
};
const acp::command::Parser acp::command::Parser::HEIGHTMAP = {
	{ "minecraft", "heightmap" },
	{
		{ &ProtocolVersion::v1_20_5, 49 },
		{ &ProtocolVersion::v1_19_4, 47 }
	}
};
const acp::command::Parser acp::command::Parser::UUID = {
	{ "minecraft", "uuid" },
	{
		{ &ProtocolVersion::v1_20_5, 53 },
		{ &ProtocolVersion::v1_19_4, 48 },
		{ &ProtocolVersion::v1_19, 47 }
	}
};
