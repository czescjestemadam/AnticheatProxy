#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::login::c2s
{
	class LoginStart : public IPacket
	{
		std::string username;

		/// 1.19 - 1.19.1
		std::optional<std::tuple<long, ByteBuf, ByteBuf>> signatureData;

		/// 1.19 - now, optional <= 1.20
		std::optional<UUID> uuid;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		std::string getUsername() const;
		void setUsername(const std::string& username);

		const std::optional<UUID>& getUuid() const;
		void setUuid(const std::optional<UUID>& uuid);

		std::string toString() const override;
	};
}
