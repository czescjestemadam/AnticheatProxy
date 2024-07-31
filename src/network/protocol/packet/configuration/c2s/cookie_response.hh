#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::configuration::c2s
{
	class CookieResponse : public IPacket
	{
		Identifier key;
		std::optional<ByteBuf> payload;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		Identifier getKey() const;
		void setKey(const Identifier& key);

		std::optional<ByteBuf>& getPayload();
		void setPayload(const std::optional<ByteBuf>& payload);

		std::string toString() const override;
	};
}
