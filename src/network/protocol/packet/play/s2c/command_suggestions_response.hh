#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::s2c
{
	class CommandSuggestionsResponse : public IPacket
	{
		int transactionId;
		int start;
		int length;
		std::vector<std::pair<std::string, std::unique_ptr<nbt::Tag>>> matches;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		int getTransactionId() const;
		void setTransactionId(int transaction_id);

		int getStart() const;
		void setStart(int start);

		int getLength() const;
		void setLength(int length);

		std::vector<std::pair<std::string, std::unique_ptr<nbt::Tag>>>& getMatches();
		const std::vector<std::pair<std::string, std::unique_ptr<nbt::Tag>>>& getMatches() const;
		void setMatches(std::vector<std::pair<std::string, std::unique_ptr<nbt::Tag>>>&& matches);

		std::string toString() const override;
	};
}
