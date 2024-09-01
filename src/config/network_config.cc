#include "network_config.hh"

#include "config_macros.hh"
#include "globals.hh"

acp::NetworkConfig::NetworkConfig() : IConfig("NetworkConfig")
{
}

void acp::NetworkConfig::loadJson(const nlohmann::json& json)
{
	JSON_READ("listen-ip", listenIp);
	JSON_READ("listen-port", listenPort);

	JSON_READ("destination-ip", destinationIp);
	JSON_READ("destination-port", destinationPort);
	JSON_READ("destination-out-compression-threshold", destinationOutCompressionThreshold);

	JSON_READ("ping-tracker-samples-count", pingTrackerSamplesCount);
	JSON_READ("keep-alive-sender-interval-ms", keepAliveSenderIntervalMs);
}

void acp::NetworkConfig::saveJson(nlohmann::json& json)
{
	JSON_WRITE("listen-ip", listenIp);
	JSON_WRITE("listen-port", listenPort);

	JSON_WRITE("destination-ip", destinationIp);
	JSON_WRITE("destination-port", destinationPort);
	JSON_WRITE("destination-out-compression-threshold", destinationOutCompressionThreshold);

	JSON_WRITE("ping-tracker-samples-count", pingTrackerSamplesCount);
	JSON_WRITE("keep-alive-sender-interval-ms", keepAliveSenderIntervalMs);
}

std::filesystem::path acp::NetworkConfig::getFile()
{
	return globals::RUNDIR / "configs" / "network.json";
}
