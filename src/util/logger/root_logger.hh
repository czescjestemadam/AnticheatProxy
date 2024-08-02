#pragma once
#include "i_logger.hh"

#include <fstream>
#include <filesystem>

namespace acp
{
	class RootLogger : public ILogger
	{
		std::string filename;
		std::ofstream ofs;

		RootLogger();
		~RootLogger() override;

		std::filesystem::path getLogsDir() const;
		std::string getFilename() const;
		void openFile();

	public:
		void log(LogLevel level, const std::string& message) override;

		SubLogger getSubLogger(const std::string& name) override;


		static RootLogger* get();
	};
}

