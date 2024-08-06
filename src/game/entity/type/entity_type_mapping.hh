#pragma once
#include "entity_type.hh"

#include <unordered_map>

namespace acp
{
	class ProtocolVersion;
}

namespace acp::game
{
	class EntityTypeMapping
	{
		std::unordered_map<int, const EntityType*> mappings;

	public:
		EntityTypeMapping() = default;
		explicit EntityTypeMapping(const ProtocolVersion* version);

		const EntityType* get(int idx) const;

		size_t size() const;
	};
}
