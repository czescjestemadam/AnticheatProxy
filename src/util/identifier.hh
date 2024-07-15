#pragma once
#include <string>

namespace acp
{
	class Identifier
	{
		std::string ns;
		std::string key;

	public:
		Identifier(const std::string& ns, const std::string& key);

		std::string getNs() const;
		void setNs(const std::string& ns);

		std::string getKey() const;
		void setKey(const std::string& key);

		std::string toString() const;

		static Identifier parse(const std::string& str);
	};
}
