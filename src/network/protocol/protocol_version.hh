#pragma once
#include <string>

namespace acp
{
	class ProtocolVersion
	{
		int idx;
		std::string name;

	public:
		ProtocolVersion(int idx, std::string&& name);

		int getIdx() const;
		std::string getName() const;

		bool operator==(const ProtocolVersion& rhs) const;
		bool operator!=(const ProtocolVersion& rhs) const;
		bool operator<(const ProtocolVersion& rhs) const;
		bool operator<=(const ProtocolVersion& rhs) const;
		bool operator>(const ProtocolVersion& rhs) const;
		bool operator>=(const ProtocolVersion& rhs) const;


		static ProtocolVersion* byIdx(int idx);

		static const ProtocolVersion v1_16_3;
		static const ProtocolVersion v1_16_4;
		static const ProtocolVersion v1_17;
		static const ProtocolVersion v1_17_1;
		static const ProtocolVersion v1_18;
		static const ProtocolVersion v1_18_2;
		static const ProtocolVersion v1_19;
		static const ProtocolVersion v1_19_1;
		static const ProtocolVersion v1_19_3;
		static const ProtocolVersion v1_19_4;
		static const ProtocolVersion v1_20;
		static const ProtocolVersion v1_20_2;
		static const ProtocolVersion v1_20_3;
		static const ProtocolVersion v1_20_5;
		static const ProtocolVersion v1_21;
	};
}
