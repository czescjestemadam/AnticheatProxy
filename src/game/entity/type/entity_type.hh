#pragma once
#include "util/vec3.hh"

#include <string>
#include <vector>

namespace acp
{
	class ProtocolVersion;
}

namespace acp::game
{
	class EntityType
	{
		std::string name;
		std::string displayname;
		std::vector<std::pair<const ProtocolVersion*, Vec3d>> boundigBoxSizes;
		std::vector<std::pair<const ProtocolVersion*, int>> ids;

	public:
		EntityType(std::string&& name, std::string&& displayname, std::vector<std::pair<const ProtocolVersion*, Vec3d>>&& boundig_box_sizes,
				   std::vector<std::pair<const ProtocolVersion*, int>>&& ids);

		const std::string& getName() const;
		const std::string& getDisplayname() const;
		Vec3d getBoundingBoxSize(const ProtocolVersion* version) const;
		int getId(const ProtocolVersion* version) const;


		static const EntityType* byName(const std::string& name);

		static const EntityType ALLAY;
		static const EntityType AREA_EFFECT_CLOUD;
		static const EntityType ARMADILLO;
		static const EntityType ARMOR_STAND;
		static const EntityType ARROW;
		static const EntityType AXOLOTL;
		static const EntityType BAT;
		static const EntityType BEE;
		static const EntityType BLAZE;
		static const EntityType BLOCK_DISPLAY;
		static const EntityType BOAT;
		static const EntityType BOGGED;
		static const EntityType BREEZE;
		static const EntityType BREEZE_WIND_CHARGE;
		static const EntityType CAMEL;
		static const EntityType CAT;
		static const EntityType CAVE_SPIDER;
		static const EntityType CHEST_BOAT;
		static const EntityType CHEST_MINECART;
		static const EntityType CHICKEN;
		static const EntityType COD;
		static const EntityType COMMAND_BLOCK_MINECART;
		static const EntityType COW;
		static const EntityType CREEPER;
		static const EntityType DOLPHIN;
		static const EntityType DONKEY;
		static const EntityType DRAGON_FIREBALL;
		static const EntityType DROWNED;
		static const EntityType EGG;
		static const EntityType ELDER_GUARDIAN;
		static const EntityType END_CRYSTAL;
		static const EntityType ENDER_DRAGON;
		static const EntityType ENDER_PEARL;
		static const EntityType ENDERMAN;
		static const EntityType ENDERMITE;
		static const EntityType EVOKER;
		static const EntityType EVOKER_FANGS;
		static const EntityType EXPERIENCE_BOTTLE;
		static const EntityType EXPERIENCE_ORB;
		static const EntityType EYE_OF_ENDER;
		static const EntityType FALLING_BLOCK;
		static const EntityType FIREBALL;
		static const EntityType FIREWORK_ROCKET;
		static const EntityType FISHING_BOBBER;
		static const EntityType FOX;
		static const EntityType FROG;
		static const EntityType FURNACE_MINECART;
		static const EntityType GHAST;
		static const EntityType GIANT;
		static const EntityType GLOW_ITEM_FRAME;
		static const EntityType GLOW_SQUID;
		static const EntityType GOAT;
		static const EntityType GUARDIAN;
		static const EntityType HOGLIN;
		static const EntityType HOPPER_MINECART;
		static const EntityType HORSE;
		static const EntityType HUSK;
		static const EntityType ILLUSIONER;
		static const EntityType INTERACTION;
		static const EntityType IRON_GOLEM;
		static const EntityType ITEM;
		static const EntityType ITEM_DISPLAY;
		static const EntityType ITEM_FRAME;
		static const EntityType LEASH_KNOT;
		static const EntityType LIGHTNING_BOLT;
		static const EntityType LLAMA;
		static const EntityType LLAMA_SPIT;
		static const EntityType MAGMA_CUBE;
		static const EntityType MARKER;
		static const EntityType MINECART;
		static const EntityType MOOSHROOM;
		static const EntityType MULE;
		static const EntityType OCELOT;
		static const EntityType OMINOUS_ITEM_SPAWNER;
		static const EntityType PAINTING;
		static const EntityType PANDA;
		static const EntityType PARROT;
		static const EntityType PHANTOM;
		static const EntityType PIG;
		static const EntityType PIGLIN;
		static const EntityType PIGLIN_BRUTE;
		static const EntityType PILLAGER;
		static const EntityType PLAYER;
		static const EntityType POLAR_BEAR;
		static const EntityType POTION;
		static const EntityType PUFFERFISH;
		static const EntityType RABBIT;
		static const EntityType RAVAGER;
		static const EntityType SALMON;
		static const EntityType SHEEP;
		static const EntityType SHULKER;
		static const EntityType SHULKER_BULLET;
		static const EntityType SILVERFISH;
		static const EntityType SKELETON;
		static const EntityType SKELETON_HORSE;
		static const EntityType SLIME;
		static const EntityType SMALL_FIREBALL;
		static const EntityType SNIFFER;
		static const EntityType SNOW_GOLEM;
		static const EntityType SNOWBALL;
		static const EntityType SPAWNER_MINECART;
		static const EntityType SPECTRAL_ARROW;
		static const EntityType SPIDER;
		static const EntityType SQUID;
		static const EntityType STRAY;
		static const EntityType STRIDER;
		static const EntityType TADPOLE;
		static const EntityType TEXT_DISPLAY;
		static const EntityType TNT;
		static const EntityType TNT_MINECART;
		static const EntityType TRADER_LLAMA;
		static const EntityType TRIDENT;
		static const EntityType TROPICAL_FISH;
		static const EntityType TURTLE;
		static const EntityType VEX;
		static const EntityType VILLAGER;
		static const EntityType VINDICATOR;
		static const EntityType WANDERING_TRADER;
		static const EntityType WARDEN;
		static const EntityType WIND_CHARGE;
		static const EntityType WITCH;
		static const EntityType WITHER;
		static const EntityType WITHER_SKELETON;
		static const EntityType WITHER_SKULL;
		static const EntityType WOLF;
		static const EntityType ZOGLIN;
		static const EntityType ZOMBIE;
		static const EntityType ZOMBIE_HORSE;
		static const EntityType ZOMBIE_VILLAGER;
		static const EntityType ZOMBIFIED_PIGLIN;
	};
}
