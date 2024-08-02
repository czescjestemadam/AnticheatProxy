#pragma once
#include "network/protocol/packet/i_packet.hh"
#include "util/command/command_node.hh"

namespace acp::packet::play::s2c
{
	class Commands : public IPacket
	{
		std::vector<command::Node> nodes;
		int rootIndex;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		std::vector<command::Node>& getNodes();
		const std::vector<command::Node>& getNodes() const;
		void setNodes(std::vector<command::Node>&& nodes);

		int getRootIndex() const;
		void setRootIndex(int root_index);

		std::string toString() const override;
	};
}
