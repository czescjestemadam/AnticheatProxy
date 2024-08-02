#include "i_properties.hh"

#include "empty_properties.hh"
#include "flags_properties.hh"
#include "identifier_properties.hh"
#include "number_properties.hh"
#include "string_properties.hh"
#include "time_properties.hh"

std::unique_ptr<acp::command::IProperties> acp::command::IProperties::fromParserId(int id)
{
	switch (id)
	{
		case 1: return std::make_unique<NumberProperties<float>>();
		case 2: return std::make_unique<NumberProperties<double>>();
		case 3: return std::make_unique<NumberProperties<int>>();
		case 4: return std::make_unique<NumberProperties<long>>();
		case 5: return std::make_unique<StringProperties>();
		case 6: return std::make_unique<EntityProperties>();

		case 30: return std::make_unique<ScoreHolderProperties>();

		case 41: return std::make_unique<TimeProperties>();

		case 42:
		case 43:
		case 44:
		case 45: return std::make_unique<IdentifierProperties>();

		default: return std::make_unique<EmptyProperties>();
	}
}
