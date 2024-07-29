#include "command_suggestions_response.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::CommandSuggestionsResponse::read(const ProtocolVersion* version)
{
	transactionId = buf.readVarint();
	start = buf.readVarint();
	length = buf.readVarint();

	const int len = buf.readVarint();
	for (int i = 0; i < len; i++)
	{
		const std::string match = buf.readStr();
		std::unique_ptr<nbt::Tag> tooltip = buf.readByte() ? buf.readNbt() : nullptr;

		matches.emplace_back(match, std::move(tooltip));
	}
}

void acp::packet::play::s2c::CommandSuggestionsResponse::write(const ProtocolVersion* version)
{
	buf.writeVarint(transactionId);
	buf.writeVarint(start);
	buf.writeVarint(length);

	buf.writeVarint(static_cast<int>(matches.size()));
	for (auto& [match, tooltip] : matches)
	{
		buf.writeStr(match);
		buf.writeByte(tooltip != nullptr);
		if (tooltip != nullptr)
			buf.writeNbt(tooltip);
	}
}

acp::HandleResult acp::packet::play::s2c::CommandSuggestionsResponse::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::CommandSuggestionsResponse::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x10;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x0F;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x0D;
	if (*version >= ProtocolVersion::v1_19)
		return 0x0E;
	if (*version >= ProtocolVersion::v1_17)
		return 0x11;

	return 0x0F;
}

int acp::packet::play::s2c::CommandSuggestionsResponse::getTransactionId() const
{
	return transactionId;
}

void acp::packet::play::s2c::CommandSuggestionsResponse::setTransactionId(const int transaction_id)
{
	transactionId = transaction_id;
}

int acp::packet::play::s2c::CommandSuggestionsResponse::getStart() const
{
	return start;
}

void acp::packet::play::s2c::CommandSuggestionsResponse::setStart(const int start)
{
	this->start = start;
}

int acp::packet::play::s2c::CommandSuggestionsResponse::getLength() const
{
	return length;
}

void acp::packet::play::s2c::CommandSuggestionsResponse::setLength(const int length)
{
	this->length = length;
}

std::vector<std::pair<std::string, std::unique_ptr<acp::nbt::Tag>>>& acp::packet::play::s2c::CommandSuggestionsResponse::getMatches()
{
	return matches;
}

const std::vector<std::pair<std::string, std::unique_ptr<acp::nbt::Tag>>>& acp::packet::play::s2c::CommandSuggestionsResponse::getMatches() const
{
	return matches;
}

void acp::packet::play::s2c::CommandSuggestionsResponse::setMatches(std::vector<std::pair<std::string, std::unique_ptr<nbt::Tag>>>&& matches)
{
	this->matches = std::move(matches);
}

std::string acp::packet::play::s2c::CommandSuggestionsResponse::toString() const
{
	return std::format("CommandSuggestionsResponse[id={}, start={}, len={}, matches={}]",
					   transactionId,
					   start,
					   length,
					   matches.size()
	);
}
