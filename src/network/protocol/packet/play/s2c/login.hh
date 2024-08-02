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
		std::optional<int> simulationDistance;
		bool reducedDebugInfo;
		bool enableRespawnScreen;
		bool doLimitedCrafting;
		std::variant<Identifier, int> dimensionType;
		Identifier dimensionName;
		long hashedSeed;
		byte_t gameMode;
		byte_t previousGameMode;
		bool isDebug;
		bool isFlat;
		std::optional<std::pair<Identifier, Vec3i>> deathDimensionNamePosition;
		std::optional<int> portalCooldown;
		std::optional<bool> enforcesSecureChat;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		int getEntityId() const;
		void setEntityId(int entity_id);

		bool isHardcore() const;
		void setHardcore(bool hardcore);

		const std::vector<Identifier>& getDimensionNames() const;
		void setDimensionNames(const std::vector<Identifier>& dimension_names);

		int getMaxPlayers() const;
		void setMaxPlayers(int max_players);

		int getViewDistance() const;
		void setViewDistance(int view_distance);

		const std::optional<int>& getSimulationDistance() const;
		void setSimulationDistance(const std::optional<int>& simulation_distance);

		bool isReducedDebugInfo() const;
		void setReducedDebugInfo(bool reduced_debug_info);

		bool isEnableRespawnScreen() const;
		void setEnableRespawnScreen(bool enable_respawn_screen);

		bool isDoLimitedCrafting() const;
		void setDoLimitedCrafting(bool do_limited_crafting);

		const std::variant<Identifier, int>& getDimensionType() const;
		void setDimensionType(const std::variant<Identifier, int>& dimension_type);

		const Identifier& getDimensionName() const;
		void setDimensionName(const Identifier& dimension_name);

		long getHashedSeed() const;
		void setHashedSeed(long hashed_seed);

		byte_t getGameMode() const;
		void setGameMode(byte_t game_mode);

		byte_t getPreviousGameMode() const;
		void setPreviousGameMode(byte_t previous_game_mode);

		bool isIsDebug() const;
		void setIsDebug(bool is_debug);

		bool isIsFlat() const;
		void setIsFlat(bool is_flat);

		const std::optional<std::pair<Identifier, Vec3i>>& getDeathDimensionNamePosition() const;
		void setDeathDimensionNamePosition(const std::optional<std::pair<Identifier, Vec3i>>& death_dimension_name_position);

		const std::optional<int>& getPortalCooldown() const;
		void setPortalCooldown(const std::optional<int>& portal_cooldown);

		const std::optional<bool>& getEnforcesSecureChat() const;
		void setEnforcesSecureChat(const std::optional<bool>& enforces_secure_chat);

		std::string toString() const override;
	};
}
