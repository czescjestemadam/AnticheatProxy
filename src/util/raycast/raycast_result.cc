#include "raycast_result.hh"

acp::RaycastResult::RaycastResult(const Vec3d& hit_position): hitPosition(hit_position)
{
}


acp::RaycastBlockResult::RaycastBlockResult(const Vec3d& hit_position, const Vec3i& block_pos, BoxFace face)
	: RaycastResult(hit_position), blockPos(block_pos), face(face)
{
}

acp::RaycastResult::Type acp::RaycastBlockResult::getType() const
{
	return Type::BLOCK;
}


acp::RaycastEntityResult::RaycastEntityResult(const Vec3d& hit_position, int entity_id)
	: RaycastResult(hit_position), entityId(entity_id)
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
