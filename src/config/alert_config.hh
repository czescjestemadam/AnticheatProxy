#pragma once
#include "i_config.hh"

namespace acp
{
	class AlertConfig : public IConfig
	{
	public:
		int antispamLogSize = 4;
		std::string format = "<red><bold>[ACP] <reset><player> <red>failed <reset><check> <gray>x<count> <dark_gray><check-info>";
		std::string hoverFormat = "<yellow><check-description>";
		std::string clickFormat = "/tp <player>";


		AlertConfig();

	protected:
		void loadJson(const nlohmann::json& json) override;
		void saveJson(nlohmann::json& json) override;

		std::filesystem::path getFile() override;
	};
}
