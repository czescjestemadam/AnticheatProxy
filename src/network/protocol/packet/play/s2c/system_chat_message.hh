#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::s2c
{
	class SystemChatMessage : public IPacket
	{
		// TODO chat nbt
		std::string content;
		bool overlay;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		bool apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		std::string& getContent();
		void setContent(const std::string& content);

		bool isOverlay() const;
		void setOverlay(bool overlay);

		std::string toString() const override;
	};
}
