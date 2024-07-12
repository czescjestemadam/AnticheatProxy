#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::status::s2c
{
	class StatusResponse : public IPacket
	{
		std::string json;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		int getId(const ProtocolVersion* version) const override;

		std::string getJson() const;
		void setJson(const std::string& json);

		std::string toString() const override;
	};
}
