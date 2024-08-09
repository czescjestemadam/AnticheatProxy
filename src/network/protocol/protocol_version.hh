#pragma once
#include "protocol_mapping.hh"
#include "game/entity/type/entity_type_mapping.hh"
#include "util/command/parser/parser_mapping.hh"
#include "util/logger/sub_logger.hh"

#include <string>

namespace acp
{
	class ProtocolVersion
	{
		int idx;
		std::string name;
		ProtocolMapping protocolMapping;
		game::EntityTypeMapping entityTypeMapping;
		command::ParserMapping commandParserMapping;

	public:
		ProtocolVersion(int idx, std::string&& name);

		int getIdx() const;
		std::string getName() const;
		const ProtocolMapping& getProtocolMapping() const;
		const game::EntityTypeMapping& getEntityTypeMapping() const;
		const command::ParserMapping& getCommandParserMapping() const;

		bool operator==(const ProtocolVersion& rhs) const;
		bool operator!=(const ProtocolVersion& rhs) const;
		bool operator<(const ProtocolVersion& rhs) const;
		bool operator<=(const ProtocolVersion& rhs) const;
		bool operator>(const ProtocolVersion& rhs) const;
		bool operator>=(const ProtocolVersion& rhs) const;


		static void compileMappings(SubLogger&& logger);

		static ProtocolVersion* byIdx(int idx);

		static const ProtocolVersion v1_16_3;
		static const ProtocolVersion v1_16_4;
		static const ProtocolVersion v1_17;
		static const ProtocolVersion v1_17_1;
		static const ProtocolVersion v1_18;
		static const ProtocolVersion v1_18_2;
		static const ProtocolVersion v1_19;
		static const ProtocolVersion v1_19_1;
		static const ProtocolVersion v1_19_3;
		static const ProtocolVersion v1_19_4;
		static const ProtocolVersion v1_20;
		static const ProtocolVersion v1_20_2;
		static const ProtocolVersion v1_20_3;
		static const ProtocolVersion v1_20_5;
		static const ProtocolVersion v1_21;
	};
}
