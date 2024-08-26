#pragma once
#include "anticheat/check/i_interact_check.hh"

namespace acp::check
{
	class Reach : public IInteractCheck
	{
	public:
		using IInteractCheck::IInteractCheck;

		HandleResult check(packet::play::c2s::Interact* packet) override;
		HandleResult check(packet::play::c2s::UseItem* packet) override;
		HandleResult check(packet::play::c2s::UseItemOn* packet) override;
		HandleResult check(packet::play::c2s::PlayerAction* packet) override;
		HandleResult check(packet::play::c2s::SwingArm* packet) override;

		std::string getName() const override;
		std::string getDescription() const override;
	};
}
