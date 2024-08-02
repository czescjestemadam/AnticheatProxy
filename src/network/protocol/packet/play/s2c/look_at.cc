#include "look_at.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::LookAt::read(const ProtocolVersion* version)
{
	feetEyes = buf.readVarint();
	target = buf.readVec3d();

	if (buf.readByte())
		entityIdFeetEyes = { buf.readVarint(), buf.readVarint() };
}

void acp::packet::play::s2c::LookAt::write(const ProtocolVersion* version)
{
	buf.writeVarint(feetEyes);
	buf.writeVec3d(target);

	if (entityIdFeetEyes.has_value())
	{
		const auto& [eId, eFeetEyes] = entityIdFeetEyes.value();
		buf.writeVarint(eId);
		buf.writeVarint(eFeetEyes);
	}
}

acp::HandleResult acp::packet::play::s2c::LookAt::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::LookAt::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x3F;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x3D;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x3B;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x37;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x38;
	if (*version >= ProtocolVersion::v1_19)
		return 0x35;
	if (*version >= ProtocolVersion::v1_17)
		return 0x37;

	return 0x33;
}

int acp::packet::play::s2c::LookAt::getFeetEyes() const
{
	return feetEyes;
}

void acp::packet::play::s2c::LookAt::setFeetEyes(const int feet_eyes)
{
	feetEyes = feet_eyes;
}

const acp::Vec3d& acp::packet::play::s2c::LookAt::getTarget() const
{
	return target;
}

void acp::packet::play::s2c::LookAt::setTarget(const Vec3d& target)
{
	this->target = target;
}

bool acp::packet::play::s2c::LookAt::isIsEntity() const
{
	return isEntity;
}

void acp::packet::play::s2c::LookAt::setIsEntity(const bool is_entity)
{
	isEntity = is_entity;
}

const std::optional<std::pair<int, int>>& acp::packet::play::s2c::LookAt::getEntityIdFeetEyes() const
{
	return entityIdFeetEyes;
}

void acp::packet::play::s2c::LookAt::setEntityIdFeetEyes(const std::optional<std::pair<int, int>>& entity_id_feet_eyes)
{
	entityIdFeetEyes = entity_id_feet_eyes;
}

std::string acp::packet::play::s2c::LookAt::toString() const
{
	const auto& [eId, eFeetEyes] = entityIdFeetEyes.value_or(std::make_pair(-1, -1));

	return std::format("LookAt[f/e={}, target={} {} {}, entity={}, id={}, f/e={}]",
					   feetEyes,
					   target.x, target.y, target.z,
					   isEntity,
					   eId,
					   eFeetEyes
	);
}
