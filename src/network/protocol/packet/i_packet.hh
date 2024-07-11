#pragma once
#include "util/io/byte_buf.hh"

namespace acp::packet
{
	class IPacket
	{
	protected:
		ByteBuf buf;

	public:
		explicit IPacket(const ByteBuf& buf);
		virtual ~IPacket() = default;

		virtual void read() = 0;
		virtual void write() = 0;

		ByteBuf& getBuf();

		virtual std::string toString() const = 0;
	};
}
