#include "reach.hh"

void acp::check::Reach::check(packet::play::c2s::Interact* packet)
{
}

void acp::check::Reach::check(packet::play::c2s::UseItem* packet)
{
}

void acp::check::Reach::check(packet::play::c2s::UseItemOn* packet)
{
}

void acp::check::Reach::check(packet::play::c2s::PlayerAction* packet)
{
}

void acp::check::Reach::check(packet::play::c2s::SwingArm* packet)
{
}

std::string acp::check::Reach::toString() const
{
	return "Reach";
}
