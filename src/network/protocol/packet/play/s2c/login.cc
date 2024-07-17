#include "login.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::Login::read(const ProtocolVersion* version)
{
	entityId = buf.readVarint();
}

void acp::packet::play::s2c::Login::write(const ProtocolVersion* version)
{
	buf.writeVarint(entityId);
}

bool acp::packet::play::s2c::Login::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return false;
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
	if (*version >= ProtocolVersion::v1_17_1)
		return 0x26;

	return 0x24;
}

int& acp::packet::play::s2c::Login::getEntityId()
{
	return entityId;
}

void acp::packet::play::s2c::Login::setEntityId(int entity_id)
{
	entityId = entity_id;
}

bool& acp::packet::play::s2c::Login::isHardcore()
{
	return hardcore;
}

void acp::packet::play::s2c::Login::setHardcore(bool hardcore)
{
	this->hardcore = hardcore;
}

std::vector<acp::Identifier>& acp::packet::play::s2c::Login::getDimensionNames()
{
	return dimensionNames;
}

void acp::packet::play::s2c::Login::setDimensionNames(const std::vector<Identifier>& dimension_names)
{
	dimensionNames = dimension_names;
}

int& acp::packet::play::s2c::Login::getMaxPlayers()
{
	return maxPlayers;
}

void acp::packet::play::s2c::Login::setMaxPlayers(int max_players)
{
	maxPlayers = max_players;
}

int& acp::packet::play::s2c::Login::getViewDistance()
{
	return viewDistance;
}

void acp::packet::play::s2c::Login::setViewDistance(int view_distance)
{
	viewDistance = view_distance;
}

int& acp::packet::play::s2c::Login::getSimulationDistance()
{
	return simulationDistance;
}

void acp::packet::play::s2c::Login::setSimulationDistance(int simulation_distance)
{
	simulationDistance = simulation_distance;
}

bool& acp::packet::play::s2c::Login::isReducedDebugInfo()
{
	return reducedDebugInfo;
}

void acp::packet::play::s2c::Login::setReducedDebugInfo(bool reduced_debug_info)
{
	reducedDebugInfo = reduced_debug_info;
}

bool& acp::packet::play::s2c::Login::isEnableRespawnScreen()
{
	return enableRespawnScreen;
}

void acp::packet::play::s2c::Login::setEnableRespawnScreen(bool enable_respawn_screen)
{
	enableRespawnScreen = enable_respawn_screen;
}

bool& acp::packet::play::s2c::Login::isDoLimitedCrafting()
{
	return doLimitedCrafting;
}

void acp::packet::play::s2c::Login::setDoLimitedCrafting(bool do_limited_crafting)
{
	doLimitedCrafting = do_limited_crafting;
}

int& acp::packet::play::s2c::Login::getDimensionType()
{
	return dimensionType;
}

void acp::packet::play::s2c::Login::setDimensionType(int dimension_type)
{
	dimensionType = dimension_type;
}

acp::Identifier& acp::packet::play::s2c::Login::getDimensionName()
{
	return dimensionName;
}

void acp::packet::play::s2c::Login::setDimensionName(const Identifier& dimension_name)
{
	dimensionName = dimension_name;
}

long& acp::packet::play::s2c::Login::getHashedSeed()
{
	return hashedSeed;
}

void acp::packet::play::s2c::Login::setHashedSeed(long hashed_seed)
{
	hashedSeed = hashed_seed;
}

byte_t& acp::packet::play::s2c::Login::getGameMode()
{
	return gameMode;
}

void acp::packet::play::s2c::Login::setGameMode(byte_t game_mode)
{
	gameMode = game_mode;
}

byte_t& acp::packet::play::s2c::Login::getPreviousGameMode()
{
	return previousGameMode;
}

void acp::packet::play::s2c::Login::setPreviousGameMode(byte_t previous_game_mode)
{
	previousGameMode = previous_game_mode;
}

bool& acp::packet::play::s2c::Login::isIsDebug()
{
	return isDebug;
}

void acp::packet::play::s2c::Login::setIsDebug(bool is_debug)
{
	isDebug = is_debug;
}

bool& acp::packet::play::s2c::Login::isIsFlat()
{
	return isFlat;
}

void acp::packet::play::s2c::Login::setIsFlat(bool is_flat)
{
	isFlat = is_flat;
}

std::optional<acp::Identifier>& acp::packet::play::s2c::Login::getDeathDimensionName()
{
	return deathDimensionName;
}

void acp::packet::play::s2c::Login::setDeathDimensionName(const std::optional<Identifier>& death_dimension_name)
{
	deathDimensionName = death_dimension_name;
}

std::optional<size_t>& acp::packet::play::s2c::Login::getDeathPosition()
{
	return deathPosition;
}

void acp::packet::play::s2c::Login::setDeathPosition(const std::optional<size_t>& death_position)
{
	deathPosition = death_position;
}

int& acp::packet::play::s2c::Login::getPortalCooldown()
{
	return portalCooldown;
}

void acp::packet::play::s2c::Login::setPortalCooldown(int portal_cooldown)
{
	portalCooldown = portal_cooldown;
}

bool& acp::packet::play::s2c::Login::isEnforcesSecureChat()
{
	return enforcesSecureChat;
}

void acp::packet::play::s2c::Login::setEnforcesSecureChat(bool enforces_secure_chat)
{
	enforcesSecureChat = enforces_secure_chat;
}

std::string acp::packet::play::s2c::Login::toString() const
{
	return std::format("Login[id={}, viewDist={}, simDist={}, gm={}]", entityId, viewDistance, simulationDistance, gameMode);
}
