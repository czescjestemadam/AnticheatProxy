#pragma once
#include "network/protocol/packet/i_packet.hh"

#include <optional>

namespace acp::packet::login::c2s
{
	class CookieResponse : public IPacket
	{
		Identifier key;
		std::optional<ByteBuf> payload = std::nullopt;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		int getId(const ProtocolVersion* version) const override;

		Identifier& getKey();
		void setKey(const Identifier& key);

		std::optional<ByteBuf>& getPayload();
		void setPayload(const std::optional<ByteBuf>& payload);

		std::string toString() const override;
	};
}
