#include "move_vehicle.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::c2s::MoveVehicle::read(const ProtocolVersion* version)
{
	position = buf.readVec3d();
	yaw = buf.readFloat();
	pitch = buf.readFloat();
}

void acp::packet::play::c2s::MoveVehicle::write(const ProtocolVersion* version)
{
	buf.writeVec3d(position);
	buf.writeFloat(yaw);
	buf.writeFloat(pitch);
}

acp::HandleResult acp::packet::play::c2s::MoveVehicle::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::c2s::MoveVehicle::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x1E;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x1B;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x1A;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x18;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x17;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x18;
	if (*version >= ProtocolVersion::v1_19)
		return 0x17;
	if (*version >= ProtocolVersion::v1_17)
		return 0x15;

	return 0x16;
}

const acp::Vec3d& acp::packet::play::c2s::MoveVehicle::getPosition() const
{
	return position;
}

void acp::packet::play::c2s::MoveVehicle::setPosition(const Vec3d& position)
{
	this->position = position;
}

float acp::packet::play::c2s::MoveVehicle::getYaw() const
{
	return yaw;
}

void acp::packet::play::c2s::MoveVehicle::setYaw(const float yaw)
{
	this->yaw = yaw;
}

float acp::packet::play::c2s::MoveVehicle::getPitch() const
{
	return pitch;
}

void acp::packet::play::c2s::MoveVehicle::setPitch(const float pitch)
{
	this->pitch = pitch;
}

std::string acp::packet::play::c2s::MoveVehicle::toString() const
{
	return std::format("MoveVehicle[pos={} {} {}, rot={} {}]",
					   position.x, position.y, position.z,
					   yaw, pitch
	);
}
