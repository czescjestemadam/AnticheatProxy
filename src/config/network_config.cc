#include "network_config.hh"

acp::NetworkConfig::NetworkConfig() : IConfig("NetworkConfig")
{
}

void acp::NetworkConfig::loadJson(const nlohmann::json& json)
{
	listenIp = json["listen-ip"];
	listenPort = json["listen-port"];

	destinationIp = json["destination-ip"];
	destinationPort = json["destination-port"];
	outCompressionThreshold = json["out-compression-threshold"];
}

void acp::NetworkConfig::saveJson(nlohmann::json& json)
{
	json["listen-ip"] = listenIp;
	json["listen-port"] = listenPort;

	json["destination-ip"] = destinationIp;
	json["destination-port"] = destinationPort;
	json["out-compression-threshold"] = outCompressionThreshold;
}

std::filesystem::path acp::NetworkConfig::getFile()
{
	return std::filesystem::current_path() / "configs" / "network.json";
}
