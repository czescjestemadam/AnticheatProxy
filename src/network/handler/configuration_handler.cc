#include "configuration_handler.hh"

#include "network/connection.hh"

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::c2s::ClientInformation* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::c2s::CookieResponse* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::c2s::PluginMessage* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::c2s::AcknowledgeFinishConfiguration* packet)
{
	connection->setState(NetworkState::PLAY);

	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::c2s::KeepAlive* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::c2s::Pong* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::c2s::ResourcePackResponse* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::c2s::KnownPacks* packet)
{
	return HandleResult::FORWARD;
}


acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::CookieRequest* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::PluginMessage* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::Disconnect* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::FinishConfiguration* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::KeepAlive* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::Ping* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::ResetChat* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::RegistryData* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::RemoveResourcePack* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::AddResourcePack* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::StoreCookie* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::Transfer* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::FeatureFlags* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::UpdateTags* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::KnownPacks* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::CustomReportDetails* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::ConfigurationHandler::handle(packet::configuration::s2c::ServerLinks* packet)
{
	return HandleResult::FORWARD;
}


void acp::ConfigurationHandler::disconnect(const std::unique_ptr<text::Component>& reason)
{
	auto packet = std::make_unique<packet::configuration::s2c::Disconnect>();
	packet->setReason(reason->copy());

	connection->sendPacket(NetworkSide::CLIENT, std::move(packet));
}
