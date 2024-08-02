#pragma once
#include "game/entity/player.hh"

namespace acp
{
	class AcpPlayer : public game::Player
	{
	public:
		using Player::Player;

		std::string toString() override;
	};
}
