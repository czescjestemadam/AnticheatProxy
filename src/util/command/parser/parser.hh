#pragma once
#include "util/identifier.hh"
#include "util/command/properties/empty_properties.hh"

#include <functional>
#include <vector>

namespace acp
{
	class ProtocolVersion;
}

namespace acp::command
{
	class Parser
	{
		Identifier identifier;
		std::vector<std::pair<const ProtocolVersion*, int>> ids;
		std::function<std::unique_ptr<IProperties>()> propertiesConstructor;

	public:
		Parser(Identifier&& identifier, const std::vector<std::pair<const ProtocolVersion*, int>>& ids,
			   std::function<std::unique_ptr<IProperties>()>&& propertiesConstructor = [] { return std::make_unique<EmptyProperties>(); });

		const Identifier& getIdentifier() const;
		int getId(const ProtocolVersion* version) const;
		std::unique_ptr<IProperties> createProperties() const;


		static const Parser* byName(const std::string& name);

		static const Parser BOOL;
		static const Parser FLOAT;
		static const Parser DOUBLE;
		static const Parser INTEGER;
		static const Parser LONG;
		static const Parser STRING;
		static const Parser ENTITY;
		static const Parser GAME_PROFILE;
		static const Parser BLOCK_POS;
		static const Parser COLUMN_POS;
		static const Parser VEC3;
		static const Parser VEC2;
		static const Parser BLOCK_STATE;
		static const Parser BLOCK_PREDICATE;
		static const Parser ITEM_STACK;
		static const Parser ITEM_PREDICATE;
		static const Parser COLOR;
		static const Parser COMPONENT;
		static const Parser STYLE;
		static const Parser MESSAGE;
		static const Parser NBT;
		static const Parser NBT_TAG;
		static const Parser NBT_PATH;
		static const Parser OBJECTIVE;
		static const Parser OBJECTIVE_CRITERIA;
		static const Parser OPERATION;
		static const Parser PARTICLE;
		static const Parser ANGLE;
		static const Parser ROTATION;
		static const Parser SCOREBOARD_SLOT;
		static const Parser SCORE_HOLDER;
		static const Parser SWIZZLE;
		static const Parser TEAM;
		static const Parser ITEM_SLOT;
		static const Parser ITEM_SLOTS;
		static const Parser RESOURCE_LOCATION;
		static const Parser MOB_EFFECT;
		static const Parser FUNCTION;
		static const Parser ENTITY_ANCHOR;
		static const Parser INT_RANGE;
		static const Parser FLOAT_RANGE;
		static const Parser DIMENSION;
		static const Parser GAMEMODE;
		static const Parser TIME;
		static const Parser RESOURCE_OR_TAG;
		static const Parser RESOURCE_OR_TAG_KEY;
		static const Parser RESOURCE;
		static const Parser RESOURCE_KEY;
		static const Parser TEMPLATE_MIRROR;
		static const Parser TEMPLATE_ROTATION;
		static const Parser HEIGHTMAP;
		static const Parser UUID;
	};
}
