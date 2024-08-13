#include "alert_config.hh"

#include "config_macros.hh"

acp::AlertConfig::AlertConfig() : IConfig("AlertConfig")
{
}

void acp::AlertConfig::loadJson(const nlohmann::json& json)
{
	JSON_READ("antispam-log-size", antispamLogSize);
	JSON_READ("format", format);
	JSON_READ("hover-format", hoverFormat);
	JSON_READ("click-format", clickFormat);
}

void acp::AlertConfig::saveJson(nlohmann::json& json)
{
	JSON_WRITE("antispam-log-size", antispamLogSize);
	JSON_WRITE("format", format);
	JSON_WRITE("hover-format", hoverFormat);
	JSON_WRITE("click-format", clickFormat);
}

std::filesystem::path acp::AlertConfig::getFile()
{
	return std::filesystem::current_path() / "configs" / "alert.json";
}
