#pragma once
#include "network/protocol/packet/i_packet.hh"
#include "game/entity/entity.hh"
#include "network/protocol/protocol_version.hh"

namespace acp::packet::play::s2c
{
	struct ChunkData
	{
		std::unique_ptr<nbt::Tag> heightmaps;
		ByteBuf data;
		std::vector<std::unique_ptr<game::Entity>> blockEntities;

		virtual ~ChunkData() = default;

		virtual void read(ByteBuf& buf, const ProtocolVersion* version) = 0;
		virtual void write(ByteBuf& buf, const ProtocolVersion* version) = 0;

		virtual std::string toString() = 0;
	};

	struct ChunkData16 : ChunkData
	{
		bool fullChunk;
		int primaryBitMask;
		std::vector<int> biomes;

		void read(ByteBuf& buf, const ProtocolVersion* version) override;
		void write(ByteBuf& buf, const ProtocolVersion* version) override;

		std::string toString() override;
	};

	struct ChunkData17 : ChunkData
	{
		std::vector<long> primaryBitMask;
		std::vector<int> biomes;

		void read(ByteBuf& buf, const ProtocolVersion* version) override;
		void write(ByteBuf& buf, const ProtocolVersion* version) override;

		std::string toString() override;
	};

	struct ChunkData18 : ChunkData
	{
		/// 1.18 - 1.19.4
		std::optional<bool> trustEdges;
		std::vector<bool> skyLightMask;
		std::vector<bool> blockLightMask;
		std::vector<bool> emptySkyLightMask;
		std::vector<bool> emptyBlockLightMask;
		std::vector<ByteBuf> skyLight;
		std::vector<ByteBuf> blockLight;

		void read(ByteBuf& buf, const ProtocolVersion* version) override;
		void write(ByteBuf& buf, const ProtocolVersion* version) override;

		std::string toString() override;
	};

	class ChunkDataAndUpdateLight : public IPacket
	{
		int x, z;
		std::unique_ptr<ChunkData> chunkData;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		int getX() const;
		void setX(int x);

		int getZ() const;
		void setZ(int z);

		std::unique_ptr<ChunkData>& getChunkData();
		const std::unique_ptr<ChunkData>& getChunkData() const;
		void setChunkData(std::unique_ptr<ChunkData>&& chunk_data);

		std::string toString() const override;
	};
}
