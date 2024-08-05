#include "inventory.hh"

acp::game::Inventory::Inventory(int size) : size(size)
{
}

acp::game::Inventory::Inventory(int size, const std::vector<ItemStack>& contents) : size(size), contents(contents)
{
}

int acp::game::Inventory::getSize() const
{
	return size;
}

const std::vector<acp::game::ItemStack>& acp::game::Inventory::getContents() const
{
	return contents;
}

void acp::game::Inventory::setContents(const std::vector<ItemStack>& contents)
{
	this->contents = contents;
}

