#include "i_network_handler.hh"

acp::INetworkHandler::INetworkHandler(Connection* connection) : connection(connection)
{
}

void acp::INetworkHandler::sendPluginMessage(NetworkSide to, const Identifier& channel, const ByteBuf& data)
{
}

void acp::INetworkHandler::disconnect(const std::unique_ptr<text::Component>& reason)
{
}
