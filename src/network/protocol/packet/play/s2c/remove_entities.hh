#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::s2c
{
	class RemoveEntities : public IPacket
	{
		/// in 1.17 only [0] is read/written
		std::vector<int> ids;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		std::vector<int>& getIds();
		const std::vector<int>& getIds() const;
		void setIds(const std::vector<int>& ids);

		std::string toString() const override;
	};
}
