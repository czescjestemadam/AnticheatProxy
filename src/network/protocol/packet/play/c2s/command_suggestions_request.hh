#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::c2s
{
	class CommandSuggestionsRequest : public IPacket
	{
		int transactionId;
		std::string text;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		int getTransactionId() const;
		void setTransactionId(int transaction_id);

		const std::string& getText() const;
		void setText(const std::string& text);

		std::string toString() const override;
	};
}
