#pragma once
#include "log_level.hh"

#include <format>

namespace acp
{
	class SubLogger;

	class ILogger
	{
	public:
		virtual ~ILogger() = default;

		virtual void log(LogLevel level, const std::string& message) = 0;

		void debug(const std::string& message);
		void info(const std::string& message);
		void warn(const std::string& message);
		void error(const std::string& message);
		void crash(const std::string& message);

		template<class ...Args>
		void debug(const std::format_string<Args...>& format, Args&& ...args)
		{
			debug(std::vformat(format.get(), std::make_format_args<>(args...)));
		}

		template<class ...Args>
		void info(const std::format_string<Args...>& format, Args&& ...args)
		{
			info(std::vformat(format.get(), std::make_format_args<>(args...)));
		}

		template<class ...Args>
		void warn(const std::format_string<Args...>& format, Args&& ...args)
		{
			warn(std::vformat(format.get(), std::make_format_args<>(args...)));
		}

		template<class ...Args>
		void error(const std::format_string<Args...>& format, Args&& ...args)
		{
			error(std::vformat(format.get(), std::make_format_args<>(args...)));
		}

		template<class ...Args>
		void crash(const std::format_string<Args...>& format, Args&& ...args)
		{
			crash(std::vformat(format.get(), std::make_format_args<>(args...)));
		}

		virtual SubLogger getSubLogger(const std::string& name) = 0;
	};

	inline void ILogger::debug(const std::string& message)
	{
		log(LogLevel::DEBUG, message);
	}

	inline void ILogger::info(const std::string& message)
	{
		log(LogLevel::INFO, message);
	}

	inline void ILogger::warn(const std::string& message)
	{
		log(LogLevel::WARN, message);
	}

	inline void ILogger::error(const std::string& message)
	{
		log(LogLevel::ERROR, message);
	}

	inline void ILogger::crash(const std::string& message)
	{
		log(LogLevel::CRASH, message);
	}
}
