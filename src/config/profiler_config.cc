#include "profiler_config.hh"

#include "config_macros.hh"

acp::ProfilerConfig::ProfilerConfig() : IConfig("ProfilerConfig")
{
}

void acp::ProfilerConfig::loadJson(const nlohmann::json& json)
{
	JSON_READ("logger-dump", loggerDump);
	JSON_READ("file-dump", fileDump);
}

void acp::ProfilerConfig::saveJson(nlohmann::json& json)
{
	JSON_WRITE("logger-dump", loggerDump);
	JSON_WRITE("file-dump", fileDump);
}

std::filesystem::path acp::ProfilerConfig::getFile()
{
	return std::filesystem::current_path() / "configs" / "profiler.json";
}
