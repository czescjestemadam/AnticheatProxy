#pragma once
#include "i_logger.hh"

#include <fstream>

namespace acp
{
	class RootLogger : public ILogger
	{
		std::ofstream ofs;

		RootLogger();
		~RootLogger() override;

	public:
		RootLogger(RootLogger&) = delete;

		void log(LogLevel level, const std::string& message) override;

		SubLogger getSubLogger(const std::string& name) override;


		static RootLogger* get();
	};
}

