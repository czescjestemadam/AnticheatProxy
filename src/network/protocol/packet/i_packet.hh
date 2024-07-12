#pragma once
#include "network/protocol/protocol_version.hh"
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

		virtual void read(const ProtocolVersion* version) = 0;
		virtual void write(const ProtocolVersion* version) = 0;

		ByteBuf& getBuf();

		virtual int getId(const ProtocolVersion* version) const = 0;

		virtual std::string toString() const = 0;
	};
}
