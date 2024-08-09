#include "parser_mapping.hh"

#define ADD_PARSER(parser) {		\
	int id = parser.getId(version); \
	if (id >= 0)					\
		mappings[id] = &parser;		\
}

acp::command::ParserMapping::ParserMapping(const ProtocolVersion* version)
{
	ADD_PARSER(Parser::BOOL)
	ADD_PARSER(Parser::FLOAT)
	ADD_PARSER(Parser::DOUBLE)
	ADD_PARSER(Parser::INTEGER)
	ADD_PARSER(Parser::LONG)
	ADD_PARSER(Parser::STRING)
	ADD_PARSER(Parser::ENTITY)
	ADD_PARSER(Parser::GAME_PROFILE)
	ADD_PARSER(Parser::BLOCK_POS)
	ADD_PARSER(Parser::COLUMN_POS)
	ADD_PARSER(Parser::VEC3)
	ADD_PARSER(Parser::VEC2)
	ADD_PARSER(Parser::BLOCK_STATE)
	ADD_PARSER(Parser::BLOCK_PREDICATE)
	ADD_PARSER(Parser::ITEM_STACK)
	ADD_PARSER(Parser::ITEM_PREDICATE)
	ADD_PARSER(Parser::COLOR)
	ADD_PARSER(Parser::COMPONENT)
	ADD_PARSER(Parser::STYLE)
	ADD_PARSER(Parser::MESSAGE)
	ADD_PARSER(Parser::NBT)
	ADD_PARSER(Parser::NBT_TAG)
	ADD_PARSER(Parser::NBT_PATH)
	ADD_PARSER(Parser::OBJECTIVE)
	ADD_PARSER(Parser::OBJECTIVE_CRITERIA)
	ADD_PARSER(Parser::OPERATION)
	ADD_PARSER(Parser::PARTICLE)
	ADD_PARSER(Parser::ANGLE)
	ADD_PARSER(Parser::ROTATION)
	ADD_PARSER(Parser::SCOREBOARD_SLOT)
	ADD_PARSER(Parser::SCORE_HOLDER)
	ADD_PARSER(Parser::SWIZZLE)
	ADD_PARSER(Parser::TEAM)
	ADD_PARSER(Parser::ITEM_SLOT)
	ADD_PARSER(Parser::ITEM_SLOTS)
	ADD_PARSER(Parser::RESOURCE_LOCATION)
	ADD_PARSER(Parser::MOB_EFFECT)
	ADD_PARSER(Parser::FUNCTION)
	ADD_PARSER(Parser::ENTITY_ANCHOR)
	ADD_PARSER(Parser::INT_RANGE)
	ADD_PARSER(Parser::FLOAT_RANGE)
	ADD_PARSER(Parser::DIMENSION)
	ADD_PARSER(Parser::GAMEMODE)
	ADD_PARSER(Parser::TIME)
	ADD_PARSER(Parser::RESOURCE_OR_TAG)
	ADD_PARSER(Parser::RESOURCE_OR_TAG_KEY)
	ADD_PARSER(Parser::RESOURCE)
	ADD_PARSER(Parser::RESOURCE_KEY)
	ADD_PARSER(Parser::TEMPLATE_MIRROR)
	ADD_PARSER(Parser::TEMPLATE_ROTATION)
	ADD_PARSER(Parser::HEIGHTMAP)
	ADD_PARSER(Parser::UUID)
}

const acp::command::Parser* acp::command::ParserMapping::get(int id) const
{
	return mappings.contains(id) ? mappings.at(id) : nullptr;
}

size_t acp::command::ParserMapping::size() const
{
	return mappings.size();
}
