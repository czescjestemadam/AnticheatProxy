#pragma once
#include "i_check.hh"

#include <unordered_map>
#include <memory>

namespace acp
{
	class AcpPlayer;

	class CheckManager
	{
		AcpPlayer* player;
		bool exempt;
		std::unordered_map<std::string, std::unique_ptr<ICheck>> checks;

	public:
		explicit CheckManager(AcpPlayer* player);

		void fail(ICheck* check);
		void alert(const ICheck* check, const std::string& info = "");

		AcpPlayer* getPlayer() const;

		bool isExempt() const;
		void setExempt(bool exempt);

		std::unordered_map<std::string, std::unique_ptr<ICheck>>& getChecks();
		const std::unordered_map<std::string, std::unique_ptr<ICheck>>& getChecks() const;

		ICheck* getByName(const std::string& name);
	};
}
