#pragma once
#include "i_config.hh"

namespace acp
{
	class NetworkConfig : public IConfig
	{
	public:
		std::string listenIp = "0.0.0.0";
		ushort listenPort = 30066;

		std::string destinationIp = "127.0.0.1";
		ushort destinationPort = 30077;
		int outCompressionThreshold = -1;


		NetworkConfig();

	protected:
		void loadJson(const nlohmann::json& json) override;
		void saveJson(nlohmann::json& json) override;

		std::filesystem::path getFile() override;
	};
}
