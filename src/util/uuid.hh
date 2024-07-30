#pragma once
#include "types.hh"

#include <string>

namespace acp
{
	class UUID
	{
		union
		{
			byte_t bytes[16];

			struct
			{
				unsigned long high;
				unsigned long low;
			};
		};

	public:
		UUID();
		UUID(unsigned long high, unsigned long low);

		byte_t* getBytes();
		const byte_t* getBytes() const;
		unsigned long getHigh() const;
		unsigned long getLow() const;

		int getVersion() const;
		void setVersion(int ver);

		std::string toString() const;
		std::string toStringShort() const;

		bool operator==(const UUID& rhs) const;
		bool operator!=(const UUID& rhs) const;


		static UUID random();
		static UUID parse(const std::string& str);
		static UUID fromString(const std::string& str);
	};
}
