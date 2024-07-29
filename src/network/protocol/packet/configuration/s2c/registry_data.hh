#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::configuration::s2c
{
	class RegistryData : public IPacket
	{
		std::unique_ptr<nbt::Tag> codec;

		Identifier registryId;
		std::vector<std::pair<Identifier, std::unique_ptr<nbt::Tag>>> entries;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		Identifier getRegistryId() const;
		void setRegistryId(const Identifier& registry_id);

		std::vector<std::pair<Identifier, std::unique_ptr<nbt::Tag>>>& getEntries();
		const std::vector<std::pair<Identifier, std::unique_ptr<nbt::Tag>>>& getEntries() const;
		void setEntries(std::vector<std::pair<Identifier, std::unique_ptr<nbt::Tag>>>&& entries);

		std::string toString() const override;
	};
}
