#pragma once
#include "i_properties.hh"

namespace acp::command
{
	template<class T>
	struct NumberProperties : IProperties
	{
		/// mask
		/// - @c 0x01: min
		/// - @c 0x02: max
		byte_t flags;
		std::optional<T> min, max;

		NumberProperties() = default;
		NumberProperties(byte_t flags, const std::optional<T>& min, const std::optional<T>& max);

		ByteBuf serialize() override;
		void deserialize(ByteBuf& v) override;

		void write(ByteBuf& buf, T val) const;
		T read(ByteBuf& buf) const;
	};

	template<class T>
	NumberProperties<T>::NumberProperties(byte_t flags, const std::optional<T>& min, const std::optional<T>& max) : flags(flags), min(min), max(max)
	{
	}

	template<class T>
	ByteBuf NumberProperties<T>::serialize()
	{
		ByteBuf buf;

		buf.writeByte(flags);

		if (flags & 0x01)
			write(buf, min.value());

		if (flags & 0x02)
			write(buf, max.value());

		return buf;
	}

	template<class T>
	void NumberProperties<T>::deserialize(ByteBuf& v)
	{
		flags = v.readByte();

		if (flags & 0x01)
			min = read(v);

		if (flags & 0x02)
			max = read(v);
	}
}
