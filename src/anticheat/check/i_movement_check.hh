#pragma once
#include "i_check.hh"
#include "network/protocol/packet/play/c2s/move_vehicle.hh"
#include "network/protocol/packet/play/c2s/player_command.hh"
#include "network/protocol/packet/play/c2s/player_input.hh"
#include "network/protocol/packet/play/c2s/set_player_on_ground.hh"
#include "network/protocol/packet/play/c2s/set_player_position.hh"
#include "network/protocol/packet/play/c2s/set_player_position_rotation.hh"
#include "network/protocol/packet/play/c2s/set_player_rotation.hh"

namespace acp
{
	class IMovementCheck : public ICheck
	{
	public:
		virtual void check(packet::play::c2s::SetPlayerPosition* packet) = 0;

		virtual void check(packet::play::c2s::SetPlayerPositionRotation* packet) = 0;

		virtual void check(packet::play::c2s::SetPlayerRotation* packet) = 0;

		virtual void check(packet::play::c2s::SetPlayerOnGround* packet) = 0;

		virtual void check(packet::play::c2s::MoveVehicle* packet) = 0;

		virtual void check(packet::play::c2s::PlayerInput* packet) = 0;

		virtual void check(packet::play::c2s::PlayerCommand* packet) = 0;
	};
}
