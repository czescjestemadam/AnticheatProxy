#pragma once
#include "anticheat/check/i_interact_check.hh"

namespace acp::check
{
	class Reach : public IInteractCheck
	{
	public:
		using IInteractCheck::IInteractCheck;

		void check(packet::play::c2s::Interact* packet) override;
		void check(packet::play::c2s::UseItem* packet) override;
		void check(packet::play::c2s::UseItemOn* packet) override;
		void check(packet::play::c2s::PlayerAction* packet) override;
		void check(packet::play::c2s::SwingArm* packet) override;

		std::string toString() const override;
	};
}
