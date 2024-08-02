#include "teleport_to_entity.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::c2s::TeleportToEntity::read(const ProtocolVersion* version)
{
	targetPlayer = buf.readUuid();
}

void acp::packet::play::c2s::TeleportToEntity::write(const ProtocolVersion* version)
{
	buf.writeUuid(targetPlayer);
}

acp::HandleResult acp::packet::play::c2s::TeleportToEntity::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::c2s::TeleportToEntity::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x37;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x34;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x33;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x30;
	if (*version >= ProtocolVersion::v1_19)
		return 0x2F;

	return 0x2D;
}

const acp::UUID& acp::packet::play::c2s::TeleportToEntity::getTargetPlayer() const
{
	return targetPlayer;
}

void acp::packet::play::c2s::TeleportToEntity::setTargetPlayer(const UUID& target_player)
{
	targetPlayer = target_player;
}

std::string acp::packet::play::c2s::TeleportToEntity::toString() const
{
	return std::format("TeleportToEntity[{}]", targetPlayer.toString());
}
