#include "commands.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::Commands::read(const ProtocolVersion* version)
{
	const int len = buf.readVarint();
	for (int i = 0; i < len; ++i)
	{
		command::Node node;
		node.deserialize(buf);
		nodes.push_back(std::move(node));
	}

	rootIndex = buf.readVarint();
}

void acp::packet::play::s2c::Commands::write(const ProtocolVersion* version)
{
	buf.writeVarint(static_cast<int>(nodes.size()));
	for (command::Node& node : nodes)
		buf.writeBuf(node.serialize());

	buf.writeVarint(rootIndex);
}

acp::HandleResult acp::packet::play::s2c::Commands::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::Commands::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x11;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x10;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x0E;
	if (*version >= ProtocolVersion::v1_19)
		return 0x0F;
	if (*version >= ProtocolVersion::v1_17)
		return 0x12;

	return 0x10;
}

std::vector<acp::command::Node>& acp::packet::play::s2c::Commands::getNodes()
{
	return nodes;
}

const std::vector<acp::command::Node>& acp::packet::play::s2c::Commands::getNodes() const
{
	return nodes;
}

void acp::packet::play::s2c::Commands::setNodes(std::vector<command::Node>&& nodes)
{
	this->nodes = std::move(nodes);
}

int acp::packet::play::s2c::Commands::getRootIndex() const
{
	return rootIndex;
}

void acp::packet::play::s2c::Commands::setRootIndex(const int root_index)
{
	rootIndex = root_index;
}

std::string acp::packet::play::s2c::Commands::toString() const
{
	std::string nodesStr;
	for (int i = 0; i < nodes.size(); ++i)
	{
		nodesStr += std::format("{}: {}", i, nodes[i].toString());

		if (i + 1 < nodes.size())
			nodesStr += ", ";
	}

	return std::format("Commands[nodes[{}]={}, root={}]", nodes.size(), nodesStr, rootIndex);
}
