#pragma once
#include "util/io/byte_buf.hh"
#include "network/handler/i_network_handler.hh"

#include <memory>

namespace acp
{
	class ProtocolVersion;
}

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

		virtual bool apply(std::unique_ptr<INetworkHandler>& handler) = 0;

		ByteBuf& getBuf();

		virtual int getId(const ProtocolVersion* version) const = 0;

		virtual std::string toString() const = 0;
	};
}
