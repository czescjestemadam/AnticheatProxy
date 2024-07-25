#include "handshake.hh"

#include "network/handler/handshake_handler.hh"

#include <format>

void acp::packet::handshake::Handshake::read(const ProtocolVersion* version)
{
	protocolVersion = buf.readVarint();
	address = buf.readStr();
	port = buf.readShortU();
	nextState = buf.readVarint();
}

void acp::packet::handshake::Handshake::write(const ProtocolVersion* version)
{
	buf.writeVarint(protocolVersion);
	buf.writeStr(address);
	buf.writeShortU(port);
	buf.writeVarint(nextState);
}

acp::HandleResult acp::packet::handshake::Handshake::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* handshakeHandler = dynamic_cast<HandshakeHandler*>(handler.get()))
		return handshakeHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::handshake::Handshake::getId(const ProtocolVersion* version) const
{
	return 0x00;
}

int acp::packet::handshake::Handshake::getProtocolVersion() const
{
	return protocolVersion;
}

void acp::packet::handshake::Handshake::setProtocolVersion(int protocol_version)
{
	protocolVersion = protocol_version;
}

const std::string& acp::packet::handshake::Handshake::getAddress() const
{
	return address;
}

void acp::packet::handshake::Handshake::setAddress(const std::string& address)
{
	this->address = address;
}

ushort acp::packet::handshake::Handshake::getPort() const
{
	return port;
}

void acp::packet::handshake::Handshake::setPort(ushort port)
{
	this->port = port;
}

int acp::packet::handshake::Handshake::getNextState() const
{
	return nextState;
}

void acp::packet::handshake::Handshake::setNextState(int next_state)
{
	nextState = next_state;
}


std::string acp::packet::handshake::Handshake::toString() const
{
	return std::format("Handshake[pvn={}, addr={}:{}, next={}]", protocolVersion, address, port, nextState);
}
