#include "chunk_data_and_update_light.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"
#include "util/logger/root_logger.hh"

template<class T>
static std::string vecToStr(const std::vector<T>& vec, const std::function<std::string(const T&)>& func = [](const T& v) { return std::to_string(v); })
{
	std::string str;

	for (int i = 0; i < vec.size(); ++i)
	{
		str += func(vec[i]);

		if (i + 1 < vec.size())
			str += ", ";
	}

	return str;
}


void acp::packet::play::s2c::ChunkData16::read(ByteBuf& buf, const ProtocolVersion* version)
{
	SubLogger log = RootLogger::get()->getSubLogger("ChunkData16");

	fullChunk = buf.readByte();
	primaryBitMask = buf.readVarint();
	heightmaps = buf.readNbt();

	if (fullChunk)
	{
		const int len = buf.readVarint();
		for (int i = 0; i < len; ++i)
			biomes.push_back(buf.readVarint());
	}

	int len = buf.readVarint();
	data = buf.readBuf(len);

	len = buf.readVarint();
	for (int i = 0; i < len; ++i)
	{
		std::unique_ptr<nbt::Tag> entityTag = buf.readNbt();
		log.debug("entity[{}]: {}", i, entityTag->toString());
	}
}

void acp::packet::play::s2c::ChunkData16::write(ByteBuf& buf, const ProtocolVersion* version)
{
	buf.writeByte(fullChunk);
	buf.writeVarint(primaryBitMask);
	buf.writeNbt(heightmaps);

	if (fullChunk)
	{
		buf.writeVarint(static_cast<int>(biomes.size()));
		for (int biome : biomes)
			buf.writeVarint(biome);
	}

	buf.writeVarint(static_cast<int>(data.size()));
	buf.writeBuf(data);

	buf.writeVarint(static_cast<int>(blockEntities.size()));
	// buf.writeNbt() todo
}

std::string acp::packet::play::s2c::ChunkData16::toString()
{
	return std::format("ChunkData16[fullChunk={}, primBitMask={}, height={}, biomes={}, data[{}], entities={}]",
					   fullChunk,
					   primaryBitMask,
					   heightmaps->toString(),
					   vecToStr(biomes),
					   data.size(),
					   vecToStr<std::unique_ptr<game::Entity>>(blockEntities, [](const std::unique_ptr<game::Entity>& e) { return e->toString(); })
	);
}


void acp::packet::play::s2c::ChunkData17::read(ByteBuf& buf, const ProtocolVersion* version)
{
	SubLogger log = RootLogger::get()->getSubLogger("ChunkData17");

	int len = buf.readVarint();
	for (int i = 0; i < len; ++i)
		primaryBitMask.push_back(buf.readVarlong());

	heightmaps = buf.readNbt();

	len = buf.readVarint();
	for (int i = 0; i < len; ++i)
		biomes.push_back(buf.readVarint());

	len = buf.readVarint();
	data = buf.readBuf(len);

	len = buf.readVarint();
	for (int i = 0; i < len; ++i)
	{
		std::unique_ptr<nbt::Tag> entityTag = buf.readNbt();
		log.debug("entity[{}]: {}", i, entityTag->toString());
	}
}

void acp::packet::play::s2c::ChunkData17::write(ByteBuf& buf, const ProtocolVersion* version)
{
	buf.writeVarint(static_cast<int>(primaryBitMask.size()));
	for (long mask : primaryBitMask)
		buf.writeVarlong(mask);

	buf.writeNbt(heightmaps);

	buf.writeVarint(static_cast<int>(biomes.size()));
	for (int biome : biomes)
		buf.writeVarint(biome);

	buf.writeVarint(static_cast<int>(data.size()));
	buf.writeBuf(data);

	buf.writeVarint(static_cast<int>(blockEntities.size()));
	// buf.writeNbt()
}

std::string acp::packet::play::s2c::ChunkData17::toString()
{
	return std::format("ChunkData17[primBitMask={}, height={}, biomes={}, data[{}], entities={}]",
					   vecToStr(primaryBitMask),
					   heightmaps->toString(),
					   vecToStr(biomes),
					   data.size(),
					   vecToStr<std::unique_ptr<game::Entity>>(blockEntities, [](const auto& e) { return e->toString(); })
	);
}


void acp::packet::play::s2c::ChunkData18::read(ByteBuf& buf, const ProtocolVersion* version)
{
	SubLogger log = RootLogger::get()->getSubLogger("ChunkData18");

	heightmaps = buf.readNbt(*version < ProtocolVersion::v1_20_2);

	int len = buf.readVarint();
	data = buf.readBuf(len);

	len = buf.readVarint();
	for (int i = 0; i < len; ++i)
	{
		const byte_t xz = buf.readByte();
		const short y = buf.readShort();
		const int type = buf.readVarint();
		const auto data = buf.readNbt(*version < ProtocolVersion::v1_20_2);

		log.debug("block entity[{}]: xz={}, y={} type={}, data={}", i, xz, y, type, data->toString());
	}

	if (*version < ProtocolVersion::v1_20)
		trustEdges = buf.readByte();

	skyLightMask = buf.readBitset();
	blockLightMask = buf.readBitset();
	emptySkyLightMask = buf.readBitset();
	emptyBlockLightMask = buf.readBitset();

	len = buf.readVarint();
	for (int i = 0; i < len; ++i)
	{
		const int innerLen = buf.readVarint();
		skyLight.push_back(buf.readBuf(innerLen));
	}

	len = buf.readVarint();
	for (int i = 0; i < len; ++i)
	{
		const int innerLen = buf.readVarint();
		blockLight.push_back(buf.readBuf(innerLen));
	}
}

void acp::packet::play::s2c::ChunkData18::write(ByteBuf& buf, const ProtocolVersion* version)
{
	buf.writeNbt(heightmaps, *version < ProtocolVersion::v1_20_2);

	buf.writeVarint(static_cast<int>(data.size()));
	buf.writeBuf(data);

	buf.writeVarint(static_cast<int>(blockEntities.size()));
	for (std::unique_ptr<game::Entity>& entity : blockEntities)
	{
		buf.writeByte(0); // TODO
		buf.writeShort(static_cast<short>(entity->getPosition().y));
		buf.writeVarint(0); // TODO
		// buf.writeNbt(entity->to) // TODO
	}

	if (*version < ProtocolVersion::v1_20)
		buf.writeByte(trustEdges.value());

	buf.writeBitset(skyLightMask);
	buf.writeBitset(blockLightMask);
	buf.writeBitset(emptySkyLightMask);
	buf.writeBitset(emptyBlockLightMask);

	buf.writeVarint(static_cast<int>(skyLight.size()));
	for (ByteBuf& b : skyLight)
	{
		buf.writeVarint(static_cast<int>(b.size()));
		buf.writeBuf(b);
	}

	buf.writeVarint(static_cast<int>(blockLight.size()));
	for (ByteBuf& b : blockLight)
	{
		buf.writeVarint(static_cast<int>(b.size()));
		buf.writeBuf(b);
	}
}

std::string acp::packet::play::s2c::ChunkData18::toString()
{
	return std::format("ChunkData18[height={}, data[{}], entities={}, trustEdges={}, skyLightM={}, blockLightM={}, !skyLightM={}, !blockLightM={}, skyLight=[{}], blockLight=[{}]]",
					   heightmaps->toString(),
					   data.size(),
					   vecToStr<std::unique_ptr<game::Entity>>(blockEntities, [](const auto& e) { return e->toString(); }),
					   trustEdges.value_or(true),
					   vecToStr(skyLightMask),
					   vecToStr(blockLightMask),
					   vecToStr(emptySkyLightMask),
					   vecToStr(emptyBlockLightMask),
					   vecToStr<ByteBuf>(skyLight, [](const ByteBuf& buf) { return std::to_string(buf.size()); }),
					   vecToStr<ByteBuf>(blockLight, [](const ByteBuf& buf) { return std::to_string(buf.size()); })
	);
}


void acp::packet::play::s2c::ChunkDataAndUpdateLight::read(const ProtocolVersion* version)
{
	x = buf.readInt();
	z = buf.readInt();

	if (*version >= ProtocolVersion::v1_18)
		chunkData = std::make_unique<ChunkData18>();
	else if (*version >= ProtocolVersion::v1_17)
		chunkData = std::make_unique<ChunkData17>();
	else
		chunkData = std::make_unique<ChunkData16>();

	chunkData->read(buf, version);
}

void acp::packet::play::s2c::ChunkDataAndUpdateLight::write(const ProtocolVersion* version)
{
	buf.writeInt(x);
	buf.writeInt(z);

	chunkData->write(buf, version);
}

acp::HandleResult acp::packet::play::s2c::ChunkDataAndUpdateLight::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::ChunkDataAndUpdateLight::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x27;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x25;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x24;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x20;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x21;
	if (*version >= ProtocolVersion::v1_19)
		return 0x1F;
	if (*version >= ProtocolVersion::v1_17)
		return 0x22;

	return 0x20;
}

int acp::packet::play::s2c::ChunkDataAndUpdateLight::getX() const
{
	return x;
}

void acp::packet::play::s2c::ChunkDataAndUpdateLight::setX(const int x)
{
	this->x = x;
}

int acp::packet::play::s2c::ChunkDataAndUpdateLight::getZ() const
{
	return z;
}

void acp::packet::play::s2c::ChunkDataAndUpdateLight::setZ(const int z)
{
	this->z = z;
}

std::unique_ptr<acp::packet::play::s2c::ChunkData>& acp::packet::play::s2c::ChunkDataAndUpdateLight::getChunkData()
{
	return chunkData;
}

const std::unique_ptr<acp::packet::play::s2c::ChunkData>& acp::packet::play::s2c::ChunkDataAndUpdateLight::getChunkData() const
{
	return chunkData;
}

void acp::packet::play::s2c::ChunkDataAndUpdateLight::setChunkData(std::unique_ptr<ChunkData>&& chunk_data)
{
	chunkData = std::move(chunk_data);
}

std::string acp::packet::play::s2c::ChunkDataAndUpdateLight::toString() const
{
	return std::format("ChunkDataAndUpdateLight[x={}, z={}, data={}]", x, z, chunkData == nullptr ? "nullptr" : chunkData->toString());
}
