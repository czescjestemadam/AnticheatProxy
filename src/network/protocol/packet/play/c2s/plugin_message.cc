#include "plugin_message.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::c2s::PluginMessage::read(const ProtocolVersion* version)
{
	channel = buf.readIdentifier();
	data = buf.readBuf(buf.size());
}

void acp::packet::play::c2s::PluginMessage::write(const ProtocolVersion* version)
{
	buf.writeIdentifier(channel);
	buf.writeBuf(data);
}

acp::HandleResult acp::packet::play::c2s::PluginMessage::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::c2s::PluginMessage::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x12;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x10;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x0F;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x0D;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x0C;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x0D;
	if (*version >= ProtocolVersion::v1_19)
		return 0x0C;
	if (*version >= ProtocolVersion::v1_17)
		return 0x0A;

	return 0x0B;
}

acp::Identifier& acp::packet::play::c2s::PluginMessage::getChannel()
{
	return channel;
}

const acp::Identifier& acp::packet::play::c2s::PluginMessage::getChannel() const
{
	return channel;
}

void acp::packet::play::c2s::PluginMessage::setChannel(const Identifier& channel)
{
	this->channel = channel;
}

acp::ByteBuf& acp::packet::play::c2s::PluginMessage::getData()
{
	return data;
}

const acp::ByteBuf& acp::packet::play::c2s::PluginMessage::getData() const
{
	return data;
}

void acp::packet::play::c2s::PluginMessage::setData(const ByteBuf& data)
{
	this->data = data;
}

std::string acp::packet::play::c2s::PluginMessage::toString() const
{
	return std::format("PluginMessage[ch={}, data={}]", channel.toString(), data.toStringShort());
}

