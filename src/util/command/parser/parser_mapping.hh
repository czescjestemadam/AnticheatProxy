#pragma once
#include "parser.hh"

#include <unordered_map>

namespace acp
{
	class ProtocolVersion;
}

namespace acp::command
{
	class ParserMapping
	{
		std::unordered_map<int, const Parser*> mappings;

	public:
		ParserMapping() = default;
		explicit ParserMapping(const ProtocolVersion* version);

		const Parser* get(int id) const;

		size_t size() const;
	};
}
