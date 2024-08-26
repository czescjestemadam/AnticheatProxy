#pragma once
#include "i_config.hh"

namespace acp
{
	class ProfilerConfig : public IConfig
	{
	public:
		bool loggerDump = true;
		bool fileDump = true;

		ProfilerConfig();

	protected:
		void loadJson(const nlohmann::json& json) override;
		void saveJson(nlohmann::json& json) override;

		std::filesystem::path getFile() override;
	};
}
