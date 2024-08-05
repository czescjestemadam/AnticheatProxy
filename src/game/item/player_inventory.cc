#include "player_inventory.hh"

acp::game::PlayerInventory::PlayerInventory() : Inventory(45)
{
}

acp::game::PlayerInventory::PlayerInventory(const std::vector<ItemStack>& contents) : Inventory(45, contents)
{
}
