#pragma once

namespace acp
{
	template<class T>
	struct ISerializable
	{
		virtual ~ISerializable() = default;

		virtual T serialize() = 0;
		virtual void deserialize(T& v) = 0;
	};
}
