#include "acp_player.hh"

#include <format>

std::string acp::AcpPlayer::toString()
{
	return std::format("AcpPlayer[{}]", Player::toString());
}
