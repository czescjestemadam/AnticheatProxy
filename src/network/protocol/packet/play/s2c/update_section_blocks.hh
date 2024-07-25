#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::s2c
{
	class UpdateSectionBlocks : public IPacket
	{
		Vec3i chunkSectionPosition;
		/// x - 1.19.4
		std::optional<bool> supressLightUpdates;
		std::vector<std::pair<Vec3i, int>> blocks;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;


		Vec3i& getChunkSectionPosition();
		const Vec3i& getChunkSectionPosition() const;
		void setChunkSectionPosition(const Vec3i& chunk_section_position);

		const std::optional<bool>& getSupressLightUpdates() const;
		void setSupressLightUpdates(const std::optional<bool>& supress_light_updates);

		std::vector<std::pair<Vec3i, int>>& getBlocks();
		const std::vector<std::pair<Vec3i, int>>& getBlocks() const;
		void setBlocks(const std::vector<std::pair<Vec3i, int>>& blocks);

		std::string toString() const override;
	};
}
