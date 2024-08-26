#include "reach.hh"

acp::HandleResult acp::check::Reach::check(packet::play::c2s::Interact* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::check::Reach::check(packet::play::c2s::UseItem* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::check::Reach::check(packet::play::c2s::UseItemOn* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::check::Reach::check(packet::play::c2s::PlayerAction* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::check::Reach::check(packet::play::c2s::SwingArm* packet)
{
	fail(true, "testink failed swing");
	return HandleResult::FORWARD;
}

std::string acp::check::Reach::getName() const
{
	return "Reach";
}

std::string acp::check::Reach::getDescription() const
{
	return "Extended reach player interact";
}
