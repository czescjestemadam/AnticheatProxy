#pragma once
#include "i_logger.hh"

namespace acp
{
	class SubLogger : public ILogger
	{
		ILogger* parent;
		std::string name;

	public:
		SubLogger(ILogger* parent, const std::string& name);

		void log(LogLevel level, const std::string& message) override;

		SubLogger getSubLogger(const std::string& name) override;

		const std::string& getName() const;
		void setName(const std::string& name);


		static SubLogger fromRoot(const std::string& name);
	};
}
