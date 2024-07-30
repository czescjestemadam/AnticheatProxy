#pragma once
#include <string>

namespace acp::text
{
	class Type
	{
		int id;
		std::string name;

	public:
		Type(int id, const std::string& name);

		const std::string& getName() const;

		bool operator==(const Type& rhs) const;
		bool operator!=(const Type& rhs) const;


		static Type* byName(const std::string& name);

		static const Type TEXT;
		static const Type TRANSLATABLE;
		static const Type KEYBIND;
		static const Type SCORE;
		static const Type SELECTOR;
		static const Type NBT;
	};
}
