#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::c2s
{
	class AcknowledgeMessage : public IPacket
	{
		int messageCount;

		/// 1.19.1
		std::optional<std::pair<UUID, ByteBuf>> profileLastSig;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		int getMessageCount() const;
		void setMessageCount(int message_count);

		const std::optional<std::pair<UUID, ByteBuf>>& getProfileLastSig() const;
		void setProfileLastSig(const std::optional<std::pair<UUID, ByteBuf>>& profile_last_sig);

		std::string toString() const override;
	};
}
