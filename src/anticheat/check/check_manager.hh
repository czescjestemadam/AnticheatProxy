#pragma once
#include "i_check.hh"

#include <unordered_map>
#include <memory>

namespace acp
{
	class CheckManager
	{
		std::unordered_map<std::string, std::unique_ptr<ICheck>> checks;

	public:
		CheckManager();

		ICheck* getByName(const std::string& name);
	};
}
