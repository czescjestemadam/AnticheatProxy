#include "i_config.hh"

#include <fstream>

acp::IConfig::IConfig(const std::string& name) : logger(name)
{
}

void acp::IConfig::load()
{
	const std::filesystem::path file = getFile();
	if (!exists(file))
	{
		logger.info("Saving default config to {}", file.c_str());
		save();
		return;
	}

	try
	{
		std::ifstream ifs(file);
		if (!ifs.good())
			throw std::runtime_error("fstream::good() == false");

		loadJson(nlohmann::json::parse(ifs));
		ifs.close();

		logger.info("Loaded {}", file.c_str());
	}
	catch (const std::exception& ex)
	{
		logger.info("Failed to load {}, using default config: {}", file.c_str(), ex.what());
	}
}

void acp::IConfig::save()
{
	const std::filesystem::path file = getFile();

	try
	{
		nlohmann::json json;
		saveJson(json);

		std::ofstream ofs(file);
		if (!ofs.good())
			throw std::runtime_error("fstream::good() == false");

		ofs << json.dump(2);
		ofs.close();

		logger.info("Saved {}", file.c_str());
	}
	catch (const std::exception& ex)
	{
		logger.error("Failed to save {}: {}", file.c_str(), ex.what());
	}
}
