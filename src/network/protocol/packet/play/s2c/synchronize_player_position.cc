#include "synchronize_player_position.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::SynchronizePlayerPosition::read(const ProtocolVersion* version)
{
	position = buf.readVec3d();
	yaw = buf.readFloat();
	pitch = buf.readFloat();
	flags = buf.readByte();
	teleportId = buf.readVarint();

	if (*version >= ProtocolVersion::v1_17 && *version <= ProtocolVersion::v1_19_3)
		dismount = buf.readByte();
}

void acp::packet::play::s2c::SynchronizePlayerPosition::write(const ProtocolVersion* version)
{
	buf.writeVec3d(position);
	buf.writeFloat(yaw);
	buf.writeFloat(pitch);
	buf.writeByte(flags);
	buf.writeVarint(teleportId);

	if (*version >= ProtocolVersion::v1_17 && *version <= ProtocolVersion::v1_19_3)
		buf.writeByte(dismount.value());
}

acp::HandleResult acp::packet::play::s2c::SynchronizePlayerPosition::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::SynchronizePlayerPosition::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x40;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x3E;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x3C;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x38;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x39;
	if (*version >= ProtocolVersion::v1_19)
		return 0x36;
	if (*version >= ProtocolVersion::v1_17)
		return 0x38;

	return 0x34;
}

acp::Vec3d& acp::packet::play::s2c::SynchronizePlayerPosition::getPosition()
{
	return position;
}

void acp::packet::play::s2c::SynchronizePlayerPosition::setPosition(const Vec3d& position)
{
	this->position = position;
}

float acp::packet::play::s2c::SynchronizePlayerPosition::getYaw() const
{
	return yaw;
}

void acp::packet::play::s2c::SynchronizePlayerPosition::setYaw(const float yaw)
{
	this->yaw = yaw;
}

float acp::packet::play::s2c::SynchronizePlayerPosition::getPitch() const
{
	return pitch;
}

void acp::packet::play::s2c::SynchronizePlayerPosition::setPitch(const float pitch)
{
	this->pitch = pitch;
}

byte_t acp::packet::play::s2c::SynchronizePlayerPosition::getFlags() const
{
	return flags;
}

void acp::packet::play::s2c::SynchronizePlayerPosition::setFlags(const byte_t flags)
{
	this->flags = flags;
}

int acp::packet::play::s2c::SynchronizePlayerPosition::getTeleportId() const
{
	return teleportId;
}

void acp::packet::play::s2c::SynchronizePlayerPosition::setTeleportId(const int teleport_id)
{
	teleportId = teleport_id;
}

std::optional<bool>& acp::packet::play::s2c::SynchronizePlayerPosition::getDismount()
{
	return dismount;
}

void acp::packet::play::s2c::SynchronizePlayerPosition::setDismount(const std::optional<bool>& dismount)
{
	this->dismount = dismount;
}

std::string acp::packet::play::s2c::SynchronizePlayerPosition::toString() const
{
	return std::format("SynchronizePlayerPosition[pos={} {} {}, rot={} {}, fl={:02x}, id={}, dismount={}]",
					   position.x, position.y, position.z,
					   yaw, pitch,
					   flags,
					   teleportId,
					   dismount.value_or(false)
	);
}
