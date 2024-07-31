#pragma once
#include "network/protocol/packet/i_packet.hh"
#include "util/text/component.hh"

namespace acp::packet::play::s2c
{
	class OpenScreen : public IPacket
	{
		int windowId;
		int type;
		std::unique_ptr<text::Component> title;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		int getWindowId() const;
		void setWindowId(int window_id);

		int getType() const;
		void setType(int type);

		std::unique_ptr<text::Component>& getTitle();
		const std::unique_ptr<text::Component>& getTitle() const;
		void setTitle(std::unique_ptr<text::Component>&& title);

		std::string toString() const override;
	};
}
