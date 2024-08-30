#pragma once
#include <string>

namespace acp
{
	class Permission
	{
		int idx;
		std::string name;

	public:
		Permission(int idx, const std::string& name);

		const std::string& getName() const;

		bool operator==(const Permission& rhs) const;
		bool operator!=(const Permission& rhs) const;


		static Permission* getByName(const std::string& name);

		static const Permission ALERT;
		static const Permission CMD;
		static const Permission CMD_IP;
		static const Permission CMD_ADMIN;
		static const Permission PROFILE;
		static const Permission LOGS;
		static const Permission EXEMPT;
		static const Permission RELOAD;
		static const Permission STOP;
	};
}
