#include "configuration_handler.hh"

#include "network/connection.hh"

bool acp::ConfigurationHandler::handle(packet::configuration::c2s::ClientInformation* packet)
{
	return false;
}

bool acp::ConfigurationHandler::handle(packet::configuration::c2s::CookieResponse* packet)
{
	return false;
}

bool acp::ConfigurationHandler::handle(packet::configuration::c2s::PluginMessage* packet)
{
	return false;
}

bool acp::ConfigurationHandler::handle(packet::configuration::c2s::AcknowledgeFinishConfiguration* packet)
{
	connection->setState(NetworkState::PLAY);

	return false;
}

bool acp::ConfigurationHandler::handle(packet::configuration::c2s::KeepAlive* packet)
{
	return false;
}

bool acp::ConfigurationHandler::handle(packet::configuration::c2s::Pong* packet)
{
	return false;
}

bool acp::ConfigurationHandler::handle(packet::configuration::c2s::ResourcePackResponse* packet)
{
	return false;
}

bool acp::ConfigurationHandler::handle(packet::configuration::c2s::KnownPacks* packet)
{
	return false;
}


bool acp::ConfigurationHandler::handle(packet::configuration::s2c::CookieRequest* packet)
{
	return false;
}

bool acp::ConfigurationHandler::handle(packet::configuration::s2c::PluginMessage* packet)
{
	return false;
}

bool acp::ConfigurationHandler::handle(packet::configuration::s2c::Disconnect* packet)
{
	return false;
}

bool acp::ConfigurationHandler::handle(packet::configuration::s2c::FinishConfiguration* packet)
{
	return false;
}

bool acp::ConfigurationHandler::handle(packet::configuration::s2c::KeepAlive* packet)
{
	return false;
}

bool acp::ConfigurationHandler::handle(packet::configuration::s2c::Ping* packet)
{
	return false;
}

bool acp::ConfigurationHandler::handle(packet::configuration::s2c::ResetChat* packet)
{
	return false;
}

bool acp::ConfigurationHandler::handle(packet::configuration::s2c::RegistryData* packet)
{
	return false;
}

bool acp::ConfigurationHandler::handle(packet::configuration::s2c::RemoveResourcePack* packet)
{
	return false;
}

bool acp::ConfigurationHandler::handle(packet::configuration::s2c::AddResourcePack* packet)
{
	return false;
}

bool acp::ConfigurationHandler::handle(packet::configuration::s2c::StoreCookie* packet)
{
	return false;
}

bool acp::ConfigurationHandler::handle(packet::configuration::s2c::Transfer* packet)
{
	return false;
}

bool acp::ConfigurationHandler::handle(packet::configuration::s2c::FeatureFlags* packet)
{
	return false;
}

bool acp::ConfigurationHandler::handle(packet::configuration::s2c::UpdateTags* packet)
{
	return false;
}

bool acp::ConfigurationHandler::handle(packet::configuration::s2c::KnownPacks* packet)
{
	return false;
}

bool acp::ConfigurationHandler::handle(packet::configuration::s2c::CustomReportDetails* packet)
{
	return false;
}

bool acp::ConfigurationHandler::handle(packet::configuration::s2c::ServerLinks* packet)
{
	return false;
}
