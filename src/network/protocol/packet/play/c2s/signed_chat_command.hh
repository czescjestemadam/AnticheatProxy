#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::c2s
{
	class SignedChatCommand : public IPacket
	{
		std::string command;
		long timestamp;
		long salt;
		std::vector<std::pair<std::string, ByteBuf>> argumentSignatures;
		/// 1.19 - 1.19.2
		std::optional<bool> signedPreview;
		/// 1.19.3 - now
		std::optional<int> messageCount;
		/// 1.19.3 - now
		std::vector<bool> acknowledged;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		std::string& getCommand();
		void setCommand(const std::string& command);

		long getTimestamp();
		void setTimestamp(long timestamp);

		long getSalt();
		void setSalt(long salt);

		std::vector<std::pair<std::string, ByteBuf>>& getArgumentSignatures();
		void setArgumentSignatures(const std::vector<std::pair<std::string, ByteBuf>>& argument_signatures);

		std::optional<bool>& getSignedPreview();
		void setSignedPreview(const std::optional<bool>& signed_preview);

		std::optional<int>& getMessageCount();
		void setMessageCount(const std::optional<int>& message_count);

		const std::vector<bool>& getAcknowledged() const;
		void setAcknowledged(const std::vector<bool>& acknowledged);

		std::string toString() const override;
	};
}
