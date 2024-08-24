#pragma once
#include "network/protocol/packet/i_packet.hh"
#include "util/nbt/tag.hh"

namespace acp::packet::play::s2c
{
	class SystemChatMessage : public IPacket
	{
		std::unique_ptr<text::Component> message;
		bool overlay;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		std::unique_ptr<text::Component>& getMessage();
		void setMessage(std::unique_ptr<text::Component>&& message);

		bool isOverlay() const;
		void setOverlay(bool overlay);

		std::string toString() const override;
	};
}
