#include "raycast_result.hh"

acp::RaycastBlockResult::RaycastBlockResult(const Vec3i& block_pos, BoxFace face) : blockPos(block_pos), face(face)
{
}

acp::RaycastResult::Type acp::RaycastBlockResult::getType() const
{
	return Type::BLOCK;
}


acp::RaycastEntityResult::RaycastEntityResult(int entity_id) : entityId(entity_id)
{
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
