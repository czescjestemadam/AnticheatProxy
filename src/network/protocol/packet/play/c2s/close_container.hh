#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::c2s
{
	class CloseContainer : public IPacket
	{
		/// 0 - player inventory
		byte_t windowId;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		byte_t getWindowId() const;
		void setWindowId(byte_t window_id);

		std::string toString() const override;
	};
}
