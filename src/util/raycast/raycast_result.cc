#include "raycast_result.hh"

acp::RaycastResult::Type acp::RaycastBlockResult::getType() const
{
	return Type::BLOCK;
}

acp::RaycastResult::Type acp::RaycastEntityResult::getType() const
{
	return Type::ENTITY;
}

std::string acp::EnumNames<acp::RaycastResult::Type>::get(RaycastResult::Type val)
{
	switch (val)
	{
		case RaycastResult::Type::BLOCK: return "BLOCK";
		case RaycastResult::Type::ENTITY: return "ENTITY";
		default: return "unknown";
	}
}
