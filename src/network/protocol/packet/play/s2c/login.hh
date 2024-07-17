#pragma once
#include "network/protocol/packet/i_packet.hh"

#include <optional>

namespace acp::packet::play::s2c
{
	class Login : public IPacket
	{
		int entityId;
		bool hardcore;
		std::vector<Identifier> dimensionNames;
		int maxPlayers;
		int viewDistance;
		int simulationDistance;
		bool reducedDebugInfo;
		bool enableRespawnScreen;
		bool doLimitedCrafting;
		int dimensionType;
		Identifier dimensionName;
		long hashedSeed;
		byte_t gameMode;
		byte_t previousGameMode;
		bool isDebug;
		bool isFlat;
		std::optional<Identifier> deathDimensionName;
		std::optional<size_t> deathPosition;
		int portalCooldown;
		bool enforcesSecureChat;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		bool apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		int& getEntityId();
		void setEntityId(int entity_id);

		bool& isHardcore();
		void setHardcore(bool hardcore);

		std::vector<Identifier>& getDimensionNames();
		void setDimensionNames(const std::vector<Identifier>& dimension_names);

		int& getMaxPlayers();
		void setMaxPlayers(int max_players);

		int& getViewDistance();
		void setViewDistance(int view_distance);

		int& getSimulationDistance();
		void setSimulationDistance(int simulation_distance);

		bool& isReducedDebugInfo();
		void setReducedDebugInfo(bool reduced_debug_info);

		bool& isEnableRespawnScreen();
		void setEnableRespawnScreen(bool enable_respawn_screen);

		bool& isDoLimitedCrafting();
		void setDoLimitedCrafting(bool do_limited_crafting);

		int& getDimensionType();
		void setDimensionType(int dimension_type);

		Identifier& getDimensionName();
		void setDimensionName(const Identifier& dimension_name);

		long& getHashedSeed();
		void setHashedSeed(long hashed_seed);

		byte_t& getGameMode();
		void setGameMode(byte_t game_mode);

		byte_t& getPreviousGameMode();
		void setPreviousGameMode(byte_t previous_game_mode);

		bool& isIsDebug();
		void setIsDebug(bool is_debug);

		bool& isIsFlat();
		void setIsFlat(bool is_flat);

		std::optional<Identifier>& getDeathDimensionName();
		void setDeathDimensionName(const std::optional<Identifier>& death_dimension_name);

		std::optional<size_t>& getDeathPosition();
		void setDeathPosition(const std::optional<size_t>& death_position);

		int& getPortalCooldown();
		void setPortalCooldown(int portal_cooldown);

		bool& isEnforcesSecureChat();
		void setEnforcesSecureChat(bool enforces_secure_chat);

		std::string toString() const override;
	};
}
