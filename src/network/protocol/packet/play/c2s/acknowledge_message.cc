#include "acknowledge_message.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::c2s::AcknowledgeMessage::read(const ProtocolVersion* version)
{
	if (*version >= ProtocolVersion::v1_19_3)
		messageCount = buf.readVarint();
	else
	{
		if (buf.readByte())
		{
			const UUID id = buf.readUuid();
			const int len = buf.readVarint();
			profileLastSig = { id, buf.readBuf(len) };
		}
	}
}

void acp::packet::play::c2s::AcknowledgeMessage::write(const ProtocolVersion* version)
{
	if (*version >= ProtocolVersion::v1_19_3)
		buf.writeVarint(messageCount);
	else
	{
		buf.writeByte(profileLastSig.has_value());
		if (profileLastSig.has_value())
		{
			const auto& [id, sig] = profileLastSig.value();
			buf.writeUuid(id);
			buf.writeVarint(static_cast<int>(sig.size()));
			buf.writeBuf(sig);
		}
	}
}

acp::HandleResult acp::packet::play::c2s::AcknowledgeMessage::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::c2s::AcknowledgeMessage::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x03;

	return -1;
}

int acp::packet::play::c2s::AcknowledgeMessage::getMessageCount() const
{
	return messageCount;
}

void acp::packet::play::c2s::AcknowledgeMessage::setMessageCount(const int message_count)
{
	messageCount = message_count;
}

const std::optional<std::pair<acp::UUID, acp::ByteBuf>>& acp::packet::play::c2s::AcknowledgeMessage::getProfileLastSig() const
{
	return profileLastSig;
}

void acp::packet::play::c2s::AcknowledgeMessage::setProfileLastSig(const std::optional<std::pair<UUID, ByteBuf>>& profile_last_sig)
{
	profileLastSig = profile_last_sig;
}

std::string acp::packet::play::c2s::AcknowledgeMessage::toString() const
{
	const auto& [id, sig] = profileLastSig.value_or(std::make_pair(UUID{ 0, 0 }, ByteBuf{}));
	return std::format("AcknowledgeMessage[{}, {}, {}]", messageCount, id.toString(), sig.toString());
}
