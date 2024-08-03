#include "prompt.hh"

#include "format.hh"
#include "util/logger/root_logger.hh"

#include <atomic>
#include <iostream>
#include <termios.h>

constexpr std::string PROMPT = "> ";

static std::atomic_bool running = true;
static std::string inp;
static int cursor;

void acp::terminal::prompt::handleInput(int c)
{
	if (c == 10) // enter
	{
		if (!inp.empty())
		{
			const std::string command = inp;
			inp.clear();
			cursor = 0;

			RootLogger::get()->info("Executing: {}", command);
			// TODO commands
		}
	}
	else if (c == 27) // esape
	{
		c = getchar();
		// std::cout << std::format("\\e: int:{} char:{}\n", c, static_cast<char>(c));


		if (c == 91) // [
		{
			c = getchar();

			if (c == 'A') // up arrow
				std::cout << "up arrow\n";
			else if (c == 'B') // down arrow
				std::cout << "down arrow\n";
			else if (c == 'D') // left arrow
				cursor = std::max(cursor - 1, 0);
			else if (c == 'C') // right arrow
				cursor = std::min(static_cast<int>(inp.length()), cursor + 1);

			else if (c == 72) // home
				cursor = 0;
			else if (c == 70) // end
				cursor = static_cast<int>(inp.length());

			else if (c == 51) // delete
			{
				c = getchar();
				// std::cout << std::format("51: int:{} char:{}\n", c, static_cast<char>(c));

				if (c == '~') // delete
					inp.erase(std::max(cursor, 0), 1);
				else
					handleInput(c);
			}

			// std::cout << std::format("[: int={} char={}\n", c, static_cast<char>(c));
		}
		else
			handleInput(c);
	}
	else if (c == 127) // backspace
	{
		if (cursor > 0)
			inp.erase(--cursor, 1);
	}
	else if (c >= 32 && c < 127)
		inp.insert(cursor++, 1, static_cast<char>(c));

	print();
}

void acp::terminal::prompt::start()
{
	// 0 = stdin
	termios term{};
	tcgetattr(0, &term);

	term.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(0, TCSANOW, &term);

	print();

	while (running)
		handleInput(getchar());
}

void acp::terminal::prompt::stop()
{
	running = false;
	close(0);
}

void acp::terminal::prompt::print()
{
	std::cout << "\033[2K"; // erase line
	std::cout << "\r" + Format::FG_GREEN + PROMPT + Format::RESET + inp;
	std::cout << "\033[" + std::to_string(PROMPT.length() + cursor + 1) + 'G' << std::flush; // move cursor to column
}
