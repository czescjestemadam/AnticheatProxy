#pragma once
#include "i_logger.hh"

namespace acp
{
	class Logger : public ILogger
	{
		std::string name;

	public:
		Logger() = default;
		explicit Logger(const std::string& name);

		void log(LogLevel level, const std::string& message) override;
	};
}
