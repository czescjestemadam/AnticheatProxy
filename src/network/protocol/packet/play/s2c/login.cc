#include "login.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::Login::read(const ProtocolVersion* version)
{
	entityId = buf.readInt();
	hardcore = buf.readByte();

	if (*version >= ProtocolVersion::v1_20_2)
	{
		const int dimensionCount = buf.readVarint();
		for (int i = 0; i < dimensionCount; ++i)
			dimensionNames.push_back(buf.readIdentifier());

		maxPlayers = buf.readVarint();
		viewDistance = buf.readVarint();
		if (*version >= ProtocolVersion::v1_18)
			simulationDistance = buf.readVarint();

		reducedDebugInfo = buf.readByte();
		enableRespawnScreen = buf.readByte();
		doLimitedCrafting = buf.readByte();

		if (*version >= ProtocolVersion::v1_20_5)
			dimensionType = buf.readVarint();
		else
			dimensionType = buf.readIdentifier();

		dimensionName = buf.readIdentifier();
		hashedSeed = buf.readLong();

		gameMode = buf.readByte();
		previousGameMode = buf.readByte();
	}
	else
	{
		gameMode = buf.readByte();
		previousGameMode = buf.readByte();

		const int dimensionCount = buf.readVarint();
		for (int i = 0; i < dimensionCount; ++i)
			dimensionNames.push_back(buf.readIdentifier());

		// TODO
		const auto dimensionCodec = buf.readNbt();
		if (*version >= ProtocolVersion::v1_19)
			dimensionType = buf.readIdentifier();
		else
			const auto dimension = buf.readNbt();

		dimensionName = buf.readIdentifier();
		hashedSeed = buf.readLong();
		maxPlayers = buf.readVarint();
		viewDistance = buf.readVarint();

		if (*version >= ProtocolVersion::v1_18)
			simulationDistance = buf.readVarint();

		reducedDebugInfo = buf.readByte();
		enableRespawnScreen = buf.readByte();
	}

	isDebug = buf.readByte();
	isFlat = buf.readByte();

	if (*version >= ProtocolVersion::v1_19)
	{
		if (buf.readByte())
			deathDimensionNamePosition = { buf.readIdentifier(), buf.readPosition() };
	}

	if (*version >= ProtocolVersion::v1_20)
		portalCooldown = buf.readVarint();

	if (*version >= ProtocolVersion::v1_20_5)
		enforcesSecureChat = buf.readByte();
}

void acp::packet::play::s2c::Login::write(const ProtocolVersion* version)
{
	buf.writeInt(entityId);
	buf.writeByte(hardcore);

	if (*version >= ProtocolVersion::v1_20_2)
	{
		buf.writeVarint(static_cast<int>(dimensionNames.size()));
		for (const Identifier& name : dimensionNames)
			buf.writeIdentifier(name);

		buf.writeVarint(maxPlayers);
		buf.writeVarint(viewDistance);
		buf.writeVarint(simulationDistance.value());

		buf.writeByte(reducedDebugInfo);
		buf.writeByte(enableRespawnScreen);
		buf.writeByte(doLimitedCrafting);

		if (*version >= ProtocolVersion::v1_20_5)
			buf.writeVarint(std::get<int>(dimensionType));
		else
			buf.writeIdentifier(std::get<Identifier>(dimensionType));

		buf.writeIdentifier(dimensionName);
		buf.writeLong(hashedSeed);

		buf.writeByte(gameMode);
		buf.writeByte(previousGameMode);
	}
	else
	{
		buf.writeByte(gameMode);
		buf.writeByte(previousGameMode);

		buf.writeVarint(static_cast<int>(dimensionNames.size()));
		for (const Identifier& name : dimensionNames)
			buf.writeIdentifier(name);

		// TODO
		std::unique_ptr<nbt::Tag> tag = std::make_unique<nbt::TagCompound>();
		buf.writeNbt(tag);
		if (*version >= ProtocolVersion::v1_19)
			buf.writeIdentifier(std::get<Identifier>(dimensionType));
		else
			buf.writeNbt(tag);

		buf.writeIdentifier(dimensionName);
		buf.writeLong(hashedSeed);
		buf.writeVarint(maxPlayers);
		buf.writeVarint(viewDistance);

		if (*version >= ProtocolVersion::v1_18)
			buf.writeVarint(simulationDistance.value());

		buf.writeByte(reducedDebugInfo);
		buf.writeByte(enableRespawnScreen);
	}

	buf.writeByte(isDebug);
	buf.writeByte(isFlat);

	if (*version >= ProtocolVersion::v1_19)
	{
		const auto& [id, pos] = deathDimensionNamePosition.value();
		buf.writeIdentifier(id);
		buf.writePosition(pos);
	}

	if (*version >= ProtocolVersion::v1_20)
		buf.writeVarint(portalCooldown.value());

	if (*version >= ProtocolVersion::v1_20_5)
		buf.writeByte(enforcesSecureChat.value());
}

acp::HandleResult acp::packet::play::s2c::Login::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::Login::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x2B;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x29;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x28;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x24;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x25;
	if (*version >= ProtocolVersion::v1_19)
		return 0x23;
	if (*version >= ProtocolVersion::v1_17)
		return 0x26;

	return 0x24;
}

int acp::packet::play::s2c::Login::getEntityId() const
{
	return entityId;
}

void acp::packet::play::s2c::Login::setEntityId(int entity_id)
{
	entityId = entity_id;
}

bool acp::packet::play::s2c::Login::isHardcore() const
{
	return hardcore;
}

void acp::packet::play::s2c::Login::setHardcore(bool hardcore)
{
	this->hardcore = hardcore;
}

const std::vector<acp::Identifier>& acp::packet::play::s2c::Login::getDimensionNames() const
{
	return dimensionNames;
}

void acp::packet::play::s2c::Login::setDimensionNames(const std::vector<Identifier>& dimension_names)
{
	dimensionNames = dimension_names;
}

int acp::packet::play::s2c::Login::getMaxPlayers() const
{
	return maxPlayers;
}

void acp::packet::play::s2c::Login::setMaxPlayers(const int max_players)
{
	maxPlayers = max_players;
}

int acp::packet::play::s2c::Login::getViewDistance() const
{
	return viewDistance;
}

void acp::packet::play::s2c::Login::setViewDistance(const int view_distance)
{
	viewDistance = view_distance;
}

const std::optional<int>& acp::packet::play::s2c::Login::getSimulationDistance() const
{
	return simulationDistance;
}

void acp::packet::play::s2c::Login::setSimulationDistance(const std::optional<int>& simulation_distance)
{
	simulationDistance = simulation_distance;
}

bool acp::packet::play::s2c::Login::isReducedDebugInfo() const
{
	return reducedDebugInfo;
}

void acp::packet::play::s2c::Login::setReducedDebugInfo(const bool reduced_debug_info)
{
	reducedDebugInfo = reduced_debug_info;
}

bool acp::packet::play::s2c::Login::isEnableRespawnScreen() const
{
	return enableRespawnScreen;
}

void acp::packet::play::s2c::Login::setEnableRespawnScreen(const bool enable_respawn_screen)
{
	enableRespawnScreen = enable_respawn_screen;
}

bool acp::packet::play::s2c::Login::isDoLimitedCrafting() const
{
	return doLimitedCrafting;
}

void acp::packet::play::s2c::Login::setDoLimitedCrafting(const bool do_limited_crafting)
{
	doLimitedCrafting = do_limited_crafting;
}

const std::variant<acp::Identifier, int>& acp::packet::play::s2c::Login::getDimensionType() const
{
	return dimensionType;
}

void acp::packet::play::s2c::Login::setDimensionType(const std::variant<Identifier, int>& dimension_type)
{
	dimensionType = dimension_type;
}

const acp::Identifier& acp::packet::play::s2c::Login::getDimensionName() const
{
	return dimensionName;
}

void acp::packet::play::s2c::Login::setDimensionName(const Identifier& dimension_name)
{
	dimensionName = dimension_name;
}

long acp::packet::play::s2c::Login::getHashedSeed() const
{
	return hashedSeed;
}

void acp::packet::play::s2c::Login::setHashedSeed(const long hashed_seed)
{
	hashedSeed = hashed_seed;
}

byte_t acp::packet::play::s2c::Login::getGameMode() const
{
	return gameMode;
}

void acp::packet::play::s2c::Login::setGameMode(const byte_t game_mode)
{
	gameMode = game_mode;
}

byte_t acp::packet::play::s2c::Login::getPreviousGameMode() const
{
	return previousGameMode;
}

void acp::packet::play::s2c::Login::setPreviousGameMode(const byte_t previous_game_mode)
{
	previousGameMode = previous_game_mode;
}

bool acp::packet::play::s2c::Login::isIsDebug() const
{
	return isDebug;
}

void acp::packet::play::s2c::Login::setIsDebug(const bool is_debug)
{
	isDebug = is_debug;
}

bool acp::packet::play::s2c::Login::isIsFlat() const
{
	return isFlat;
}

void acp::packet::play::s2c::Login::setIsFlat(const bool is_flat)
{
	isFlat = is_flat;
}

const std::optional<std::pair<acp::Identifier, acp::Vec3i>>& acp::packet::play::s2c::Login::getDeathDimensionNamePosition() const
{
	return deathDimensionNamePosition;
}

void acp::packet::play::s2c::Login::setDeathDimensionNamePosition(const std::optional<std::pair<Identifier, Vec3i>>& death_dimension_name_position)
{
	deathDimensionNamePosition = death_dimension_name_position;
}

const std::optional<int>& acp::packet::play::s2c::Login::getPortalCooldown() const
{
	return portalCooldown;
}

void acp::packet::play::s2c::Login::setPortalCooldown(const std::optional<int>& portal_cooldown)
{
	portalCooldown = portal_cooldown;
}

const std::optional<bool>& acp::packet::play::s2c::Login::getEnforcesSecureChat() const
{
	return enforcesSecureChat;
}

void acp::packet::play::s2c::Login::setEnforcesSecureChat(const std::optional<bool>& enforces_secure_chat)
{
	enforcesSecureChat = enforces_secure_chat;
}

std::string acp::packet::play::s2c::Login::toString() const
{
	return std::format("Login[id={}, viewDist={}, simDist={}, gm={}, dim={}]",
					   entityId,
					   viewDistance,
					   simulationDistance.value_or(-1),
					   gameMode,
					   dimensionName.toString()
	);
}
