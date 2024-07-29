#include "command_suggestions_request.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::c2s::CommandSuggestionsRequest::read(const ProtocolVersion* version)
{
	transactionId = buf.readVarint();
	text = buf.readStr();
}

void acp::packet::play::c2s::CommandSuggestionsRequest::write(const ProtocolVersion* version)
{
	buf.writeVarint(transactionId);
	buf.writeStr(text);
}

acp::HandleResult acp::packet::play::c2s::CommandSuggestionsRequest::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::c2s::CommandSuggestionsRequest::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x0B;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x0A;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x09;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x08;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x09;
	if (*version >= ProtocolVersion::v1_19)
		return 0x08;

	return 0x06;
}

int acp::packet::play::c2s::CommandSuggestionsRequest::getTransactionId() const
{
	return transactionId;
}

void acp::packet::play::c2s::CommandSuggestionsRequest::setTransactionId(const int transaction_id)
{
	transactionId = transaction_id;
}

const std::string& acp::packet::play::c2s::CommandSuggestionsRequest::getText() const
{
	return text;
}

void acp::packet::play::c2s::CommandSuggestionsRequest::setText(const std::string& text)
{
	this->text = text;
}

std::string acp::packet::play::c2s::CommandSuggestionsRequest::toString() const
{
	return std::format("CommandSuggestionsRequest[id={}, text={}]", transactionId, text);
}
