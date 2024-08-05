#pragma once
#include "item_stack.hh"

#include <vector>

namespace acp::game
{
	class Inventory
	{
	protected:
		int size;
		std::vector<ItemStack> contents;

	public:
		explicit Inventory(int size);
		Inventory(int size, const std::vector<ItemStack>& contents);

		int getSize() const;

		const std::vector<ItemStack>& getContents() const;
		void setContents(const std::vector<ItemStack>& contents);
	};
}
