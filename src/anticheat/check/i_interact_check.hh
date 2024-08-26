#pragma once
#include "i_check.hh"
#include "network/protocol/packet/play/c2s/interact.hh"
#include "network/protocol/packet/play/c2s/player_action.hh"
#include "network/protocol/packet/play/c2s/swing_arm.hh"
#include "network/protocol/packet/play/c2s/use_item.hh"
#include "network/protocol/packet/play/c2s/use_item_on.hh"

namespace acp
{
	class IInteractCheck : public ICheck
	{
	public:
		using ICheck::ICheck;

		virtual HandleResult check(packet::play::c2s::Interact* packet) = 0;

		virtual HandleResult check(packet::play::c2s::UseItem* packet) = 0;

		virtual HandleResult check(packet::play::c2s::UseItemOn* packet) = 0;

		virtual HandleResult check(packet::play::c2s::PlayerAction* packet) = 0;

		virtual HandleResult check(packet::play::c2s::SwingArm* packet) = 0;
	};
}
