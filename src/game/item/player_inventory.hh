#pragma once
#include "inventory.hh"

namespace acp::game
{
	class PlayerInventory : public Inventory
	{
	public:
		PlayerInventory();
		explicit PlayerInventory(const std::vector<ItemStack>& contents);
	};
}
