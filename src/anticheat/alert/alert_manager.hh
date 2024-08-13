#pragma once
#include "alert.hh"

#include <vector>

namespace acp
{
	class AlertManager
	{
		std::vector<Alert> lastSent;

	public:
		void send(const Alert& alert);
	};
}
