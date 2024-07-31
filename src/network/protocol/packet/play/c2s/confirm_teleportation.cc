#include "confirm_teleportation.hh"

#include "network/handler/play_handler.hh"

void acp::packet::play::c2s::ConfirmTeleportation::read(const ProtocolVersion* version)
{
	teleportId = buf.readVarint();
}

void acp::packet::play::c2s::ConfirmTeleportation::write(const ProtocolVersion* version)
{
	buf.writeVarint(teleportId);
}

acp::HandleResult acp::packet::play::c2s::ConfirmTeleportation::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::c2s::ConfirmTeleportation::getId(const ProtocolVersion* version) const
{
	return 0x00;
}

int acp::packet::play::c2s::ConfirmTeleportation::getTeleportId() const
{
	return teleportId;
}

void acp::packet::play::c2s::ConfirmTeleportation::setTeleportId(const int teleport_id)
{
	teleportId = teleport_id;
}

std::string acp::packet::play::c2s::ConfirmTeleportation::toString() const
{
	return std::format("ConfirmTeleport[{}]", teleportId);
}
