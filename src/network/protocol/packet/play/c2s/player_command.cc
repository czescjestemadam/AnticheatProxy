#include "player_command.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"
#include "util/hash.hh"

void acp::packet::play::c2s::PlayerCommand::read(const ProtocolVersion* version)
{
	entityId = buf.readVarint();
	action = buf.readVarint();
	jumpBoost = buf.readVarint();
}

void acp::packet::play::c2s::PlayerCommand::write(const ProtocolVersion* version)
{
	buf.writeVarint(entityId);
	buf.writeVarint(action);
	buf.writeVarint(jumpBoost);
}

acp::HandleResult acp::packet::play::c2s::PlayerCommand::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::c2s::PlayerCommand::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x25;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x22;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x21;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x1E;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x1D;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x1E;
	if (*version >= ProtocolVersion::v1_19)
		return 0x1D;
	if (*version >= ProtocolVersion::v1_17)
		return 0x1B;

	return 0x1C;
}

int acp::packet::play::c2s::PlayerCommand::getEntityId() const
{
	return entityId;
}

void acp::packet::play::c2s::PlayerCommand::setEntityId(const int entity_id)
{
	entityId = entity_id;
}

int acp::packet::play::c2s::PlayerCommand::getAction() const
{
	return action;
}

void acp::packet::play::c2s::PlayerCommand::setAction(const int action)
{
	this->action = action;
}

int acp::packet::play::c2s::PlayerCommand::getJumpBoost() const
{
	return jumpBoost;
}

void acp::packet::play::c2s::PlayerCommand::setJumpBoost(const int jump_boost)
{
	jumpBoost = jump_boost;
}

std::string acp::packet::play::c2s::PlayerCommand::toString() const
{
	return std::format("PlayerCommand[id={}, action={}, jump={}]", entityId, action, jumpBoost);
}
