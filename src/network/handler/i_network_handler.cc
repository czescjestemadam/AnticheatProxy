#include "i_network_handler.hh"

acp::INetworkHandler::INetworkHandler(const Connection* connection) : connection(connection)
{
}

void acp::INetworkHandler::disconnect()
{
}
