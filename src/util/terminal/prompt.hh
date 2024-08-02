#pragma once

namespace acp::terminal::prompt
{
	void start();
	void stop();

	void handleInput(int c);
	void print();
}
