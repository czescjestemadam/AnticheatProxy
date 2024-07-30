#pragma once

namespace acp
{
	template<class T>
	struct ISerializable
	{
		virtual ~ISerializable() = default;

		virtual T serialize() = 0;
	};
}
