#pragma once
#include "i_check.hh"

#include <memory>
#include <unordered_map>

namespace acp
{
	class Connection;

	class CheckManager
	{
		Connection* connection;
		bool exempt = false;
		std::unordered_map<std::string, std::unique_ptr<ICheck>> checks;

	public:
		explicit CheckManager(Connection* player);

		Connection* getConnection() const;

		bool isExempt() const;
		void setExempt(bool exempt);

		std::unordered_map<std::string, std::unique_ptr<ICheck>>& getChecks();
		const std::unordered_map<std::string, std::unique_ptr<ICheck>>& getChecks() const;

		ICheck* getByName(const std::string& name);

	private:
		template<class T>
		void addCheck()
		{
			std::unique_ptr<ICheck> check = std::make_unique<T>(connection);
			const std::string name = check->getName();
			checks[name] = std::move(check);
		}
	};
}
