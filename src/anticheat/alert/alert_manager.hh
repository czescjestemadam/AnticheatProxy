#pragma once
#include "alert.hh"
#include "network/protocol/packet/i_packet.hh"
#include "util/text/component.hh"

#include <vector>

namespace acp
{
	class AlertManager
	{
		std::vector<Alert> lastSent;

	public:
		void send(const Alert& alert);

	private:
		std::string formatString(const std::string& str, const Alert& alert);

		void send(std::unique_ptr<text::Component>&& component);
		void send(std::unique_ptr<packet::IPacket>&& packet);
	};
}
