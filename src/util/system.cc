#include "system.hh"

#include <memory>

#include "logger/root_logger.hh"

std::string acp::System::execute(const std::string& command)
{
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
	if (!pipe)
	{
		RootLogger::get()->error("System::execute(): popen()");
		return "error";
	}

	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
		result += buffer.data();

	return result;
}
