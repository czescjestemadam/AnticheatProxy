#pragma once
#include "util/logger/logger.hh"

#include <nlohmann/json.hpp>

namespace acp
{
	class IConfig
	{
	protected:
		Logger logger;

		explicit IConfig(const std::string& name);

	public:
		virtual ~IConfig() = default;

		void load();
		void save();

	protected:
		virtual void loadJson(const nlohmann::json& json) = 0;
		virtual void saveJson(nlohmann::json& json) = 0;

		virtual std::filesystem::path getFile() = 0;
	};
}
