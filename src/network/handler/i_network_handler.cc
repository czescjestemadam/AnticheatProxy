#include "i_network_handler.hh"

acp::INetworkHandler::INetworkHandler(Connection* connection) : connection(connection)
{
}

void acp::INetworkHandler::disconnect(const std::unique_ptr<text::Component>& reason)
{
}
