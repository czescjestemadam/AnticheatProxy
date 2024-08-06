#include "entity_type.hh"

#include "network/protocol/protocol_version.hh"

#include <unordered_map>

static std::unordered_map<std::string, acp::game::EntityType*> typesByName;

acp::game::EntityType::EntityType(std::string&& name, std::string&& displayname, std::vector<std::pair<const ProtocolVersion*, Vec3d>>&& boundig_box_sizes,
								  std::vector<std::pair<const ProtocolVersion*, int>>&& ids)
	: name(name), displayname(std::move(displayname)), boundigBoxSizes(std::move(boundig_box_sizes)), ids(std::move(ids))
{
	std::sort(boundigBoxSizes.begin(), boundigBoxSizes.end(), [](const std::pair<const ProtocolVersion*, Vec3d>& lhs,
																 const std::pair<const ProtocolVersion*, Vec3d>& rhs)
	{
		return *lhs.first > *rhs.first;
	});

	std::sort(this->ids.begin(), this->ids.end(), [](const std::pair<const ProtocolVersion*, int>& lhs,
													 const std::pair<const ProtocolVersion*, int>& rhs)
	{
		return *lhs.first > *rhs.first;
	});

	typesByName[name] = this;
}

const std::string& acp::game::EntityType::getName() const
{
	return name;
}

const std::string& acp::game::EntityType::getDisplayname() const
{
	return displayname;
}

acp::Vec3d acp::game::EntityType::getBoundingBoxSize(const ProtocolVersion* version) const
{
	for (auto& [v, size] : boundigBoxSizes)
	{
		if (*version >= *v)
			return size;
	}

	return { -1, -1, -1 };
}

int acp::game::EntityType::getId(const ProtocolVersion* version) const
{
	for (auto& [v, id] : ids)
	{
		if (*version >= *v)
			return id;
	}

	return -1;
}


const acp::game::EntityType* acp::game::EntityType::byName(const std::string& name)
{
	return typesByName.contains(name) ? typesByName[name] : nullptr;
}

const acp::game::EntityType acp::game::EntityType::ALLAY = {
	"allay",
	"Allay",
	{
		{ &ProtocolVersion::v1_19, { 0.35, 0.6, 0.35 } }
	},
	{
		{ &ProtocolVersion::v1_19, 0 }
	}
};
const acp::game::EntityType acp::game::EntityType::AREA_EFFECT_CLOUD = {
	"area_effect_cloud",
	"Area Effect Cloud",
	{
		{ &ProtocolVersion::v1_16_3, { 6, 0.5, 6 } }
	},
	{
		{ &ProtocolVersion::v1_19, 1 },
		{ &ProtocolVersion::v1_16_3, 0 }
	}
};
const acp::game::EntityType acp::game::EntityType::ARMADILLO = {
	"armadillo",
	"Armadillo",
	{
		{ &ProtocolVersion::v1_21, { 0.7, 0.65, 0.7 } }
	},
	{
		{ &ProtocolVersion::v1_21, 2 }
	}
};
const acp::game::EntityType acp::game::EntityType::ARMOR_STAND = {
	"armor_stand",
	"Armor Stand",
	{
		{ &ProtocolVersion::v1_16_3, { 0.5, 1.975, 0.5 } }
	},
	{
		{ &ProtocolVersion::v1_21, 3 },
		{ &ProtocolVersion::v1_19, 2 },
		{ &ProtocolVersion::v1_16_3, 1 }
	}
};
const acp::game::EntityType acp::game::EntityType::ARROW = {
	"arrow",
	"Arrow",
	{
		{ &ProtocolVersion::v1_16_3, { 0.5, 0.5, 0.5 } }
	},
	{
		{ &ProtocolVersion::v1_21, 4 },
		{ &ProtocolVersion::v1_19, 3 },
		{ &ProtocolVersion::v1_16_3, 2 }
	}
};
const acp::game::EntityType acp::game::EntityType::AXOLOTL = {
	"axolotl",
	"Axolotl",
	{
		{ &ProtocolVersion::v1_17, { 0.75, 0.42, 0.75 } }
	},
	{
		{ &ProtocolVersion::v1_21, 5 },
		{ &ProtocolVersion::v1_19, 4 },
		{ &ProtocolVersion::v1_17, 3 }
	}
};
const acp::game::EntityType acp::game::EntityType::BAT = {
	"bat",
	"Bat",
	{
		{ &ProtocolVersion::v1_16_3, { 0.5, 0.9, 0.5 } }
	},
	{
		{ &ProtocolVersion::v1_21, 6 },
		{ &ProtocolVersion::v1_19, 5 },
		{ &ProtocolVersion::v1_17, 4 },
		{ &ProtocolVersion::v1_16_3, 3 }
	}
};
const acp::game::EntityType acp::game::EntityType::BEE = {
	"bee",
	"Bee",
	{
		{ &ProtocolVersion::v1_16_3, { 0.7, 0.6, 0.7 } }
	},
	{
		{ &ProtocolVersion::v1_21, 7 },
		{ &ProtocolVersion::v1_19, 6 },
		{ &ProtocolVersion::v1_17, 5 },
		{ &ProtocolVersion::v1_16_3, 4 }
	}
};
const acp::game::EntityType acp::game::EntityType::BLAZE = {
	"blaze",
	"Blaze",
	{
		{ &ProtocolVersion::v1_16_3, { 0.6, 1.8, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 8 },
		{ &ProtocolVersion::v1_19, 7 },
		{ &ProtocolVersion::v1_17, 6 },
		{ &ProtocolVersion::v1_16_3, 5 }
	}
};
const acp::game::EntityType acp::game::EntityType::BLOCK_DISPLAY = {
	"block_display",
	"Block Display",
	{
		{ &ProtocolVersion::v1_19_4, { 0, 0, 0 } }
	},
	{
		{ &ProtocolVersion::v1_21, 9 },
		{ &ProtocolVersion::v1_19_4, 8 }
	}
};
const acp::game::EntityType acp::game::EntityType::BOAT = {
	"boat",
	"Boat",
	{
		{ &ProtocolVersion::v1_16_3, { 1.375, 0.5625, 1.375 } }
	},
	{
		{ &ProtocolVersion::v1_21, 10 },
		{ &ProtocolVersion::v1_19_4, 9 },
		{ &ProtocolVersion::v1_19, 8 },
		{ &ProtocolVersion::v1_17, 7 },
		{ &ProtocolVersion::v1_16_3, 6 }
	}
};
const acp::game::EntityType acp::game::EntityType::BOGGED = {
	"bogged",
	"Bogged",
	{
		{ &ProtocolVersion::v1_21, { 0.6, 1.99, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 11 }
	}
};
const acp::game::EntityType acp::game::EntityType::BREEZE = {
	"breeze",
	"Breeze",
	{
		{ &ProtocolVersion::v1_21, { 0.6, 1.77, 0.6 } },
		{ &ProtocolVersion::v1_20_3, { 0.6, 1.7, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 12 },
		{ &ProtocolVersion::v1_20_3, 10 }
	}
};
const acp::game::EntityType acp::game::EntityType::BREEZE_WIND_CHARGE = {
	"breeze_wind_charge",
	"Wind Charge",
	{
		{ &ProtocolVersion::v1_21, { 0.3125, 0.3125, 0.3125 } }
	},
	{
		{ &ProtocolVersion::v1_21, 13 }
	}
};
const acp::game::EntityType acp::game::EntityType::CAMEL = {
	"camel",
	"Camel",
	{
		{ &ProtocolVersion::v1_19_4, { 1.7, 2.375, 1.7 } }
	},
	{
		{ &ProtocolVersion::v1_21, 14 },
		{ &ProtocolVersion::v1_19_3, 11 },
		{ &ProtocolVersion::v1_19_4, 10 }
	}
};
const acp::game::EntityType acp::game::EntityType::CAT = {
	"cat",
	"Cat",
	{
		{ &ProtocolVersion::v1_16_3, { 0.6, 0.7, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 15 },
		{ &ProtocolVersion::v1_20_3, 12 },
		{ &ProtocolVersion::v1_19_4, 11 },
		{ &ProtocolVersion::v1_19, 10 },
		{ &ProtocolVersion::v1_17, 8 },
		{ &ProtocolVersion::v1_16_3, 7 }
	}
};
const acp::game::EntityType acp::game::EntityType::CAVE_SPIDER = {
	"cave_spider",
	"Cave Spider",
	{
		{ &ProtocolVersion::v1_16_3, { 0.7, 0.5, 0.7 } }
	},
	{
		{ &ProtocolVersion::v1_21, 16 },
		{ &ProtocolVersion::v1_20_3, 13 },
		{ &ProtocolVersion::v1_19_3, 12 },
		{ &ProtocolVersion::v1_19, 11 },
		{ &ProtocolVersion::v1_17, 9 },
		{ &ProtocolVersion::v1_16_3, 8 }
	}
};
const acp::game::EntityType acp::game::EntityType::CHEST_BOAT = {
	"chest_boat",
	"Boat with Chest",
	{
		{ &ProtocolVersion::v1_19, { 1.375, 0.5625, 1.375 } }
	},
	{
		{ &ProtocolVersion::v1_21, 17 },
		{ &ProtocolVersion::v1_20_3, 14 },
		{ &ProtocolVersion::v1_19_4, 13 },
		{ &ProtocolVersion::v1_19, 9 }
	}
};
const acp::game::EntityType acp::game::EntityType::CHEST_MINECART = {
	"chest_minecart",
	"Minecart with Chest",
	{
		{ &ProtocolVersion::v1_19_4, { 0.98, 0.7, 0.98 } }
	},
	{
		{ &ProtocolVersion::v1_19_3, 55 },
		{ &ProtocolVersion::v1_19, 54 },
		{ &ProtocolVersion::v1_17, 51 },
		{ &ProtocolVersion::v1_16_3, 46 },
		{ &ProtocolVersion::v1_21, 18 },
		{ &ProtocolVersion::v1_20_3, 15 },
		{ &ProtocolVersion::v1_19_4, 14 }
	}
};
const acp::game::EntityType acp::game::EntityType::CHICKEN = {
	"chicken",
	"Chicken",
	{
		{ &ProtocolVersion::v1_16_3, { 0.4, 0.7, 0.4 } }
	},
	{
		{ &ProtocolVersion::v1_21, 19 },
		{ &ProtocolVersion::v1_20_3, 16 },
		{ &ProtocolVersion::v1_19_4, 15 },
		{ &ProtocolVersion::v1_19_3, 13 },
		{ &ProtocolVersion::v1_19, 12 },
		{ &ProtocolVersion::v1_17, 10 },
		{ &ProtocolVersion::v1_16_3, 9 }
	}
};
const acp::game::EntityType acp::game::EntityType::COD = {
	"cod",
	"Cod",
	{
		{ &ProtocolVersion::v1_16_3, { 0.5, 0.3, 0.5 } }
	},
	{
		{ &ProtocolVersion::v1_21, 20 },
		{ &ProtocolVersion::v1_20_3, 17 },
		{ &ProtocolVersion::v1_19_4, 16 },
		{ &ProtocolVersion::v1_19_3, 14 },
		{ &ProtocolVersion::v1_19, 13 },
		{ &ProtocolVersion::v1_17, 11 },
		{ &ProtocolVersion::v1_16_3, 10 }
	}
};
const acp::game::EntityType acp::game::EntityType::COMMAND_BLOCK_MINECART = {
	"command_block_minecart",
	"Minecart with Command Block",
	{
		{ &ProtocolVersion::v1_19_4, { 0.98, 0.7, 0.98 } }
	},
	{
		{ &ProtocolVersion::v1_19_3, 56 },
		{ &ProtocolVersion::v1_19, 55 },
		{ &ProtocolVersion::v1_17, 52 },
		{ &ProtocolVersion::v1_16_3, 47 },
		{ &ProtocolVersion::v1_21, 21 },
		{ &ProtocolVersion::v1_20_3, 18 },
		{ &ProtocolVersion::v1_19_4, 17 }
	}
};
const acp::game::EntityType acp::game::EntityType::COW = {
	"cow",
	"Cow",
	{
		{ &ProtocolVersion::v1_16_3, { 0.9, 1.4, 0.9 } }
	},
	{
		{ &ProtocolVersion::v1_21, 22 },
		{ &ProtocolVersion::v1_20_3, 19 },
		{ &ProtocolVersion::v1_19_4, 18 },
		{ &ProtocolVersion::v1_19_3, 15 },
		{ &ProtocolVersion::v1_19, 14 },
		{ &ProtocolVersion::v1_17, 12 },
		{ &ProtocolVersion::v1_16_3, 11 }
	}
};
const acp::game::EntityType acp::game::EntityType::CREEPER = {
	"creeper",
	"Creeper",
	{
		{ &ProtocolVersion::v1_16_3, { 0.6, 1.7, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 23 },
		{ &ProtocolVersion::v1_20_3, 20 },
		{ &ProtocolVersion::v1_19_4, 19 },
		{ &ProtocolVersion::v1_19_3, 16 },
		{ &ProtocolVersion::v1_19, 15 },
		{ &ProtocolVersion::v1_17, 13 },
		{ &ProtocolVersion::v1_16_3, 12 }
	}
};
const acp::game::EntityType acp::game::EntityType::DOLPHIN = {
	"dolphin",
	"Dolphin",
	{
		{ &ProtocolVersion::v1_16_3, { 0.9, 0.6, 0.9 } }
	},
	{
		{ &ProtocolVersion::v1_21, 24 },
		{ &ProtocolVersion::v1_20_3, 21 },
		{ &ProtocolVersion::v1_19_4, 20 },
		{ &ProtocolVersion::v1_19_3, 17 },
		{ &ProtocolVersion::v1_19, 16 },
		{ &ProtocolVersion::v1_17, 14 },
		{ &ProtocolVersion::v1_16_3, 13 }
	}
};
const acp::game::EntityType acp::game::EntityType::DONKEY = {
	"donkey",
	"Donkey",
	{
		{ &ProtocolVersion::v1_16_3, { 1.39648, 1.5, 1.39648 } }
	},
	{
		{ &ProtocolVersion::v1_21, 25 },
		{ &ProtocolVersion::v1_20_3, 22 },
		{ &ProtocolVersion::v1_19_4, 21 },
		{ &ProtocolVersion::v1_19_3, 18 },
		{ &ProtocolVersion::v1_19, 17 },
		{ &ProtocolVersion::v1_17, 15 },
		{ &ProtocolVersion::v1_16_3, 14 }
	}
};
const acp::game::EntityType acp::game::EntityType::DRAGON_FIREBALL = {
	"dragon_fireball",
	"Dragon Fireball",
	{
		{ &ProtocolVersion::v1_16_3, { 1, 1, 1 } }
	},
	{
		{ &ProtocolVersion::v1_21, 26 },
		{ &ProtocolVersion::v1_20_3, 23 },
		{ &ProtocolVersion::v1_19_4, 22 },
		{ &ProtocolVersion::v1_19_3, 19 },
		{ &ProtocolVersion::v1_19, 18 },
		{ &ProtocolVersion::v1_17, 16 },
		{ &ProtocolVersion::v1_16_3, 15 }
	}
};
const acp::game::EntityType acp::game::EntityType::DROWNED = {
	"drowned",
	"Drowned",
	{
		{ &ProtocolVersion::v1_16_3, { 0.6, 1.95, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 27 },
		{ &ProtocolVersion::v1_20_3, 24 },
		{ &ProtocolVersion::v1_19_4, 23 },
		{ &ProtocolVersion::v1_19_3, 20 },
		{ &ProtocolVersion::v1_19, 19 },
		{ &ProtocolVersion::v1_17, 17 },
		{ &ProtocolVersion::v1_16_3, 16 }
	}
};
const acp::game::EntityType acp::game::EntityType::EGG = {
	"egg",
	"Thrown Egg",
	{
		{ &ProtocolVersion::v1_19_4, { 0.25, 0.25, 0.25 } }
	},
	{
		{ &ProtocolVersion::v1_19_3, 94 },
		{ &ProtocolVersion::v1_19, 93 },
		{ &ProtocolVersion::v1_17, 89 },
		{ &ProtocolVersion::v1_16_3, 84 },
		{ &ProtocolVersion::v1_21, 28 },
		{ &ProtocolVersion::v1_20_3, 25 },
		{ &ProtocolVersion::v1_19_4, 24 }
	}
};
const acp::game::EntityType acp::game::EntityType::ELDER_GUARDIAN = {
	"elder_guardian",
	"Elder Guardian",
	{
		{ &ProtocolVersion::v1_16_3, { 1.9975, 1.9975, 1.9975 } }
	},
	{
		{ &ProtocolVersion::v1_21, 29 },
		{ &ProtocolVersion::v1_20_3, 26 },
		{ &ProtocolVersion::v1_19_4, 25 },
		{ &ProtocolVersion::v1_19_3, 21 },
		{ &ProtocolVersion::v1_19, 20 },
		{ &ProtocolVersion::v1_17, 18 },
		{ &ProtocolVersion::v1_16_3, 17 }
	}
};
const acp::game::EntityType acp::game::EntityType::END_CRYSTAL = {
	"end_crystal",
	"End Crystal",
	{
		{ &ProtocolVersion::v1_16_3, { 2, 2, 2 } }
	},
	{
		{ &ProtocolVersion::v1_21, 30 },
		{ &ProtocolVersion::v1_20_3, 27 },
		{ &ProtocolVersion::v1_19_4, 26 },
		{ &ProtocolVersion::v1_19_3, 22 },
		{ &ProtocolVersion::v1_19, 21 },
		{ &ProtocolVersion::v1_17, 19 },
		{ &ProtocolVersion::v1_16_3, 18 }
	}
};
const acp::game::EntityType acp::game::EntityType::ENDER_DRAGON = {
	"ender_dragon",
	"Ender Dragon",
	{
		{ &ProtocolVersion::v1_16_3, { 16, 8, 16 } }
	},
	{
		{ &ProtocolVersion::v1_21, 31 },
		{ &ProtocolVersion::v1_20_3, 28 },
		{ &ProtocolVersion::v1_19_4, 27 },
		{ &ProtocolVersion::v1_19_3, 23 },
		{ &ProtocolVersion::v1_19, 22 },
		{ &ProtocolVersion::v1_17, 20 },
		{ &ProtocolVersion::v1_16_3, 19 }
	}
};
const acp::game::EntityType acp::game::EntityType::ENDER_PEARL = {
	"ender_pearl",
	"Thrown Ender Pearl",
	{
		{ &ProtocolVersion::v1_19_4, { 0.25, 0.25, 0.25 } }
	},
	{
		{ &ProtocolVersion::v1_19_3, 95 },
		{ &ProtocolVersion::v1_19, 94 },
		{ &ProtocolVersion::v1_17, 90 },
		{ &ProtocolVersion::v1_16_3, 85 },
		{ &ProtocolVersion::v1_21, 32 },
		{ &ProtocolVersion::v1_20_3, 29 },
		{ &ProtocolVersion::v1_19_4, 28 }
	}
};
const acp::game::EntityType acp::game::EntityType::ENDERMAN = {
	"enderman",
	"Enderman",
	{
		{ &ProtocolVersion::v1_16_3, { 0.6, 2.9, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 33 },
		{ &ProtocolVersion::v1_20_3, 30 },
		{ &ProtocolVersion::v1_19_4, 29 },
		{ &ProtocolVersion::v1_19_3, 24 },
		{ &ProtocolVersion::v1_19, 23 },
		{ &ProtocolVersion::v1_17, 21 },
		{ &ProtocolVersion::v1_16_3, 20 }
	}
};
const acp::game::EntityType acp::game::EntityType::ENDERMITE = {
	"endermite",
	"Endermite",
	{
		{ &ProtocolVersion::v1_16_3, { 0.4, 0.3, 0.4 } }
	},
	{
		{ &ProtocolVersion::v1_21, 34 },
		{ &ProtocolVersion::v1_20_3, 31 },
		{ &ProtocolVersion::v1_19_4, 30 },
		{ &ProtocolVersion::v1_19_3, 25 },
		{ &ProtocolVersion::v1_19, 24 },
		{ &ProtocolVersion::v1_17, 22 },
		{ &ProtocolVersion::v1_16_3, 21 }
	}
};
const acp::game::EntityType acp::game::EntityType::EVOKER = {
	"evoker",
	"Evoker",
	{
		{ &ProtocolVersion::v1_16_3, { 0.6, 1.95, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 35 },
		{ &ProtocolVersion::v1_20_3, 32 },
		{ &ProtocolVersion::v1_19_4, 31 },
		{ &ProtocolVersion::v1_19_3, 26 },
		{ &ProtocolVersion::v1_19, 25 },
		{ &ProtocolVersion::v1_17, 23 },
		{ &ProtocolVersion::v1_16_3, 22 }
	}
};
const acp::game::EntityType acp::game::EntityType::EVOKER_FANGS = {
	"evoker_fangs",
	"Evoker Fangs",
	{
		{ &ProtocolVersion::v1_16_3, { 0.5, 0.8, 0.5 } }
	},
	{
		{ &ProtocolVersion::v1_21, 36 },
		{ &ProtocolVersion::v1_20_3, 33 },
		{ &ProtocolVersion::v1_19_4, 32 },
		{ &ProtocolVersion::v1_19_3, 27 },
		{ &ProtocolVersion::v1_19, 26 },
		{ &ProtocolVersion::v1_17, 24 },
		{ &ProtocolVersion::v1_16_3, 23 }
	}
};
const acp::game::EntityType acp::game::EntityType::EXPERIENCE_BOTTLE = {
	"experience_bottle",
	"Thrown Bottle o' Enchanting",
	{
		{ &ProtocolVersion::v1_19_4, { 0.25, 0.25, 0.25 } }
	},
	{
		{ &ProtocolVersion::v1_19_3, 96 },
		{ &ProtocolVersion::v1_19, 95 },
		{ &ProtocolVersion::v1_17, 91 },
		{ &ProtocolVersion::v1_16_3, 86 },
		{ &ProtocolVersion::v1_21, 37 },
		{ &ProtocolVersion::v1_20_3, 34 },
		{ &ProtocolVersion::v1_19_4, 33 }
	}
};
const acp::game::EntityType acp::game::EntityType::EXPERIENCE_ORB = {
	"experience_orb",
	"Experience Orb",
	{
		{ &ProtocolVersion::v1_16_3, { 0.5, 0.5, 0.5 } }
	},
	{
		{ &ProtocolVersion::v1_21, 38 },
		{ &ProtocolVersion::v1_20_3, 35 },
		{ &ProtocolVersion::v1_19_4, 34 },
		{ &ProtocolVersion::v1_19_3, 28 },
		{ &ProtocolVersion::v1_19, 27 },
		{ &ProtocolVersion::v1_17, 25 },
		{ &ProtocolVersion::v1_16_3, 24 }
	}
};
const acp::game::EntityType acp::game::EntityType::EYE_OF_ENDER = {
	"eye_of_ender",
	"Eye of Ender",
	{
		{ &ProtocolVersion::v1_16_3, { 0.25, 0.25, 0.25 } }
	},
	{
		{ &ProtocolVersion::v1_21, 39 },
		{ &ProtocolVersion::v1_20_3, 36 },
		{ &ProtocolVersion::v1_19_4, 35 },
		{ &ProtocolVersion::v1_19_3, 29 },
		{ &ProtocolVersion::v1_19, 28 },
		{ &ProtocolVersion::v1_17, 26 },
		{ &ProtocolVersion::v1_16_3, 25 }
	}
};
const acp::game::EntityType acp::game::EntityType::FALLING_BLOCK = {
	"falling_block",
	"Falling Block",
	{
		{ &ProtocolVersion::v1_16_3, { 0.98, 0.98, 0.98 } }
	},
	{
		{ &ProtocolVersion::v1_21, 40 },
		{ &ProtocolVersion::v1_20_3, 37 },
		{ &ProtocolVersion::v1_19_4, 36 },
		{ &ProtocolVersion::v1_19_3, 30 },
		{ &ProtocolVersion::v1_19, 29 },
		{ &ProtocolVersion::v1_17, 27 },
		{ &ProtocolVersion::v1_16_3, 26 }
	}
};
const acp::game::EntityType acp::game::EntityType::FIREBALL = {
	"fireball",
	"Fireball",
	{
		{ &ProtocolVersion::v1_16_3, { 1, 1, 1 } }
	},
	{
		{ &ProtocolVersion::v1_21, 62 },
		{ &ProtocolVersion::v1_20_3, 58 },
		{ &ProtocolVersion::v1_19_4, 57 },
		{ &ProtocolVersion::v1_19_3, 47 },
		{ &ProtocolVersion::v1_19, 46 },
		{ &ProtocolVersion::v1_17, 43 },
		{ &ProtocolVersion::v1_16_3, 39 }
	}
};
const acp::game::EntityType acp::game::EntityType::FIREWORK_ROCKET = {
	"firework_rocket",
	"Firework Rocket",
	{
		{ &ProtocolVersion::v1_16_3, { 0.25, 0.25, 0.25 } }
	},
	{
		{ &ProtocolVersion::v1_21, 41 },
		{ &ProtocolVersion::v1_20_3, 38 },
		{ &ProtocolVersion::v1_19_4, 37 },
		{ &ProtocolVersion::v1_19_3, 31 },
		{ &ProtocolVersion::v1_19, 30 },
		{ &ProtocolVersion::v1_17, 28 },
		{ &ProtocolVersion::v1_16_3, 27 }
	}
};
const acp::game::EntityType acp::game::EntityType::FISHING_BOBBER = {
	"fishing_bobber",
	"Fishing Bobber",
	{
		{ &ProtocolVersion::v1_16_3, { 0.25, 0.25, 0.25 } }
	},
	{
		{ &ProtocolVersion::v1_21, 129 },
		{ &ProtocolVersion::v1_20_3, 125 },
		{ &ProtocolVersion::v1_19_4, 123 },
		{ &ProtocolVersion::v1_19_3, 118 },
		{ &ProtocolVersion::v1_19, 117 },
		{ &ProtocolVersion::v1_17, 112 },
		{ &ProtocolVersion::v1_16_3, 107 }
	}
};
const acp::game::EntityType acp::game::EntityType::FOX = {
	"fox",
	"Fox",
	{
		{ &ProtocolVersion::v1_16_3, { 0.6, 0.7, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 42 },
		{ &ProtocolVersion::v1_20_3, 39 },
		{ &ProtocolVersion::v1_19_4, 38 },
		{ &ProtocolVersion::v1_19_3, 32 },
		{ &ProtocolVersion::v1_19, 31 },
		{ &ProtocolVersion::v1_17, 29 },
		{ &ProtocolVersion::v1_16_3, 28 }
	}
};
const acp::game::EntityType acp::game::EntityType::FROG = {
	"frog",
	"Frog",
	{
		{ &ProtocolVersion::v1_19, { 0.5, 0.5, 0.5 } }
	},
	{
		{ &ProtocolVersion::v1_21, 43 },
		{ &ProtocolVersion::v1_20_3, 40 },
		{ &ProtocolVersion::v1_19_4, 39 },
		{ &ProtocolVersion::v1_19_3, 33 },
		{ &ProtocolVersion::v1_19, 32 }
	}
};
const acp::game::EntityType acp::game::EntityType::FURNACE_MINECART = {
	"furnace_minecart",
	"Minecart with Furnace",
	{
		{ &ProtocolVersion::v1_19_4, { 0.98, 0.7, 0.98 } }
	},
	{
		{ &ProtocolVersion::v1_19_3, 57 },
		{ &ProtocolVersion::v1_19, 56 },
		{ &ProtocolVersion::v1_17, 53 },
		{ &ProtocolVersion::v1_16_3, 48 },
		{ &ProtocolVersion::v1_21, 44 },
		{ &ProtocolVersion::v1_20_3, 41 },
		{ &ProtocolVersion::v1_19_4, 40 }
	}
};
const acp::game::EntityType acp::game::EntityType::GHAST = {
	"ghast",
	"Ghast",
	{
		{ &ProtocolVersion::v1_16_3, { 4, 4, 4 } }
	},
	{
		{ &ProtocolVersion::v1_21, 45 },
		{ &ProtocolVersion::v1_20_3, 42 },
		{ &ProtocolVersion::v1_19_4, 41 },
		{ &ProtocolVersion::v1_19_3, 34 },
		{ &ProtocolVersion::v1_19, 33 },
		{ &ProtocolVersion::v1_17, 30 },
		{ &ProtocolVersion::v1_16_3, 29 }
	}
};
const acp::game::EntityType acp::game::EntityType::GIANT = {
	"giant",
	"Giant",
	{
		{ &ProtocolVersion::v1_16_3, { 3.6, 12, 3.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 46 },
		{ &ProtocolVersion::v1_20_3, 43 },
		{ &ProtocolVersion::v1_19_4, 42 },
		{ &ProtocolVersion::v1_19_3, 35 },
		{ &ProtocolVersion::v1_19, 34 },
		{ &ProtocolVersion::v1_17, 31 },
		{ &ProtocolVersion::v1_16_3, 30 }
	}
};
const acp::game::EntityType acp::game::EntityType::GLOW_ITEM_FRAME = {
	"glow_item_frame",
	"Glow Item Frame",
	{
		{ &ProtocolVersion::v1_17, { 0.5, 0.5, 0.5 } }
	},
	{
		{ &ProtocolVersion::v1_21, 47 },
		{ &ProtocolVersion::v1_20_3, 44 },
		{ &ProtocolVersion::v1_19_4, 43 },
		{ &ProtocolVersion::v1_19_3, 36 },
		{ &ProtocolVersion::v1_19, 35 },
		{ &ProtocolVersion::v1_17, 32 }
	}
};
const acp::game::EntityType acp::game::EntityType::GLOW_SQUID = {
	"glow_squid",
	"Glow Squid",
	{
		{ &ProtocolVersion::v1_17, { 0.8, 0.8, 0.8 } }
	},
	{
		{ &ProtocolVersion::v1_21, 48 },
		{ &ProtocolVersion::v1_20_3, 45 },
		{ &ProtocolVersion::v1_19_4, 44 },
		{ &ProtocolVersion::v1_19_3, 37 },
		{ &ProtocolVersion::v1_19, 36 },
		{ &ProtocolVersion::v1_17, 33 }
	}
};
const acp::game::EntityType acp::game::EntityType::GOAT = {
	"goat",
	"Goat",
	{
		{ &ProtocolVersion::v1_17, { 0.9, 1.3, 0.9 } }
	},
	{
		{ &ProtocolVersion::v1_21, 49 },
		{ &ProtocolVersion::v1_20_3, 46 },
		{ &ProtocolVersion::v1_19_4, 45 },
		{ &ProtocolVersion::v1_19_3, 38 },
		{ &ProtocolVersion::v1_19, 37 },
		{ &ProtocolVersion::v1_17, 34 }
	}
};
const acp::game::EntityType acp::game::EntityType::GUARDIAN = {
	"guardian",
	"Guardian",
	{
		{ &ProtocolVersion::v1_16_3, { 0.85, 0.85, 0.85 } }
	},
	{
		{ &ProtocolVersion::v1_21, 50 },
		{ &ProtocolVersion::v1_20_3, 47 },
		{ &ProtocolVersion::v1_19_4, 46 },
		{ &ProtocolVersion::v1_19_3, 39 },
		{ &ProtocolVersion::v1_19, 38 },
		{ &ProtocolVersion::v1_17, 35 },
		{ &ProtocolVersion::v1_16_3, 31 }
	}
};
const acp::game::EntityType acp::game::EntityType::HOGLIN = {
	"hoglin",
	"Hoglin",
	{
		{ &ProtocolVersion::v1_16_3, { 1.39648, 1.4, 1.39648 } }
	},
	{
		{ &ProtocolVersion::v1_21, 51 },
		{ &ProtocolVersion::v1_20_3, 48 },
		{ &ProtocolVersion::v1_19_4, 47 },
		{ &ProtocolVersion::v1_19_3, 40 },
		{ &ProtocolVersion::v1_19, 39 },
		{ &ProtocolVersion::v1_17, 36 },
		{ &ProtocolVersion::v1_16_3, 32 }
	}
};
const acp::game::EntityType acp::game::EntityType::HOPPER_MINECART = {
	"hopper_minecart",
	"Minecart with Hopper",
	{
		{ &ProtocolVersion::v1_19_4, { 0.98, 0.7, 0.98 } }
	},
	{
		{ &ProtocolVersion::v1_19_3, 58 },
		{ &ProtocolVersion::v1_19, 57 },
		{ &ProtocolVersion::v1_17, 54 },
		{ &ProtocolVersion::v1_21, 52 },
		{ &ProtocolVersion::v1_16_3, 49 },
		{ &ProtocolVersion::v1_19_4, 48 }
	}
};
const acp::game::EntityType acp::game::EntityType::HORSE = {
	"horse",
	"Horse",
	{
		{ &ProtocolVersion::v1_16_3, { 1.39648, 1.6, 1.39648 } }
	},
	{
		{ &ProtocolVersion::v1_21, 53 },
		{ &ProtocolVersion::v1_20_3, 50 },
		{ &ProtocolVersion::v1_19_4, 49 },
		{ &ProtocolVersion::v1_19_3, 41 },
		{ &ProtocolVersion::v1_19, 40 },
		{ &ProtocolVersion::v1_17, 37 },
		{ &ProtocolVersion::v1_16_3, 33 }
	}
};
const acp::game::EntityType acp::game::EntityType::HUSK = {
	"husk",
	"Husk",
	{
		{ &ProtocolVersion::v1_16_3, { 0.6, 1.95, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 54 },
		{ &ProtocolVersion::v1_20_3, 51 },
		{ &ProtocolVersion::v1_19_4, 50 },
		{ &ProtocolVersion::v1_19_3, 42 },
		{ &ProtocolVersion::v1_19, 41 },
		{ &ProtocolVersion::v1_17, 38 },
		{ &ProtocolVersion::v1_16_3, 34 }
	}
};
const acp::game::EntityType acp::game::EntityType::ILLUSIONER = {
	"illusioner",
	"Illusioner",
	{
		{ &ProtocolVersion::v1_16_3, { 0.6, 1.95, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 55 },
		{ &ProtocolVersion::v1_20_3, 52 },
		{ &ProtocolVersion::v1_19_4, 51 },
		{ &ProtocolVersion::v1_19_3, 43 },
		{ &ProtocolVersion::v1_19, 42 },
		{ &ProtocolVersion::v1_17, 39 },
		{ &ProtocolVersion::v1_16_3, 35 }
	}
};
const acp::game::EntityType acp::game::EntityType::INTERACTION = {
	"interaction",
	"Interaction",
	{
		{ &ProtocolVersion::v1_19_4, { 0, 0, 0 } }
	},
	{
		{ &ProtocolVersion::v1_21, 56 },
		{ &ProtocolVersion::v1_20_3, 53 },
		{ &ProtocolVersion::v1_19_4, 52 }
	}
};
const acp::game::EntityType acp::game::EntityType::IRON_GOLEM = {
	"iron_golem",
	"Iron Golem",
	{
		{ &ProtocolVersion::v1_16_3, { 1.4, 2.7, 1.4 } }
	},
	{
		{ &ProtocolVersion::v1_21, 57 },
		{ &ProtocolVersion::v1_20_3, 54 },
		{ &ProtocolVersion::v1_19_4, 53 },
		{ &ProtocolVersion::v1_19_3, 44 },
		{ &ProtocolVersion::v1_19, 43 },
		{ &ProtocolVersion::v1_17, 40 },
		{ &ProtocolVersion::v1_16_3, 36 }
	}
};
const acp::game::EntityType acp::game::EntityType::ITEM = {
	"item",
	"Item",
	{
		{ &ProtocolVersion::v1_16_3, { 0.25, 0.25, 0.25 } }
	},
	{
		{ &ProtocolVersion::v1_21, 58 },
		{ &ProtocolVersion::v1_20_3, 55 },
		{ &ProtocolVersion::v1_19_4, 54 },
		{ &ProtocolVersion::v1_19_3, 45 },
		{ &ProtocolVersion::v1_19, 44 },
		{ &ProtocolVersion::v1_17, 41 },
		{ &ProtocolVersion::v1_16_3, 37 }
	}
};
const acp::game::EntityType acp::game::EntityType::ITEM_DISPLAY = {
	"item_display",
	"Item Display",
	{
		{ &ProtocolVersion::v1_19_4, { 0, 0, 0 } }
	},
	{
		{ &ProtocolVersion::v1_21, 59 },
		{ &ProtocolVersion::v1_20_3, 56 },
		{ &ProtocolVersion::v1_19_4, 55 }
	}
};
const acp::game::EntityType acp::game::EntityType::ITEM_FRAME = {
	"item_frame",
	"Item Frame",
	{
		{ &ProtocolVersion::v1_16_3, { 0.5, 0.5, 0.5 } }
	},
	{
		{ &ProtocolVersion::v1_21, 60 },
		{ &ProtocolVersion::v1_20_3, 57 },
		{ &ProtocolVersion::v1_19_4, 56 },
		{ &ProtocolVersion::v1_19_3, 46 },
		{ &ProtocolVersion::v1_19, 45 },
		{ &ProtocolVersion::v1_17, 42 },
		{ &ProtocolVersion::v1_16_3, 38 }
	}
};
const acp::game::EntityType acp::game::EntityType::LEASH_KNOT = {
	"leash_knot",
	"Leash Knot",
	{
		{ &ProtocolVersion::v1_17, { 0.375, 0.5, 0.375 } },
		{ &ProtocolVersion::v1_16_3, { 0.5, 0.5, 0.5 } }
	},
	{
		{ &ProtocolVersion::v1_21, 63 },
		{ &ProtocolVersion::v1_20_3, 59 },
		{ &ProtocolVersion::v1_19_4, 58 },
		{ &ProtocolVersion::v1_19_3, 48 },
		{ &ProtocolVersion::v1_19, 47 },
		{ &ProtocolVersion::v1_17, 44 },
		{ &ProtocolVersion::v1_16_3, 40 }
	}
};
const acp::game::EntityType acp::game::EntityType::LIGHTNING_BOLT = {
	"lightning_bolt",
	"Lightning Bolt",
	{
		{ &ProtocolVersion::v1_16_3, { 0, 0, 0 } }
	},
	{
		{ &ProtocolVersion::v1_21, 64 },
		{ &ProtocolVersion::v1_20_3, 60 },
		{ &ProtocolVersion::v1_19_4, 59 },
		{ &ProtocolVersion::v1_19_3, 49 },
		{ &ProtocolVersion::v1_19, 48 },
		{ &ProtocolVersion::v1_17, 45 },
		{ &ProtocolVersion::v1_16_3, 41 }
	}
};
const acp::game::EntityType acp::game::EntityType::LLAMA = {
	"llama",
	"Llama",
	{
		{ &ProtocolVersion::v1_16_3, { 0.9, 1.87, 0.9 } }
	},
	{
		{ &ProtocolVersion::v1_21, 65 },
		{ &ProtocolVersion::v1_20_3, 61 },
		{ &ProtocolVersion::v1_19_4, 60 },
		{ &ProtocolVersion::v1_19_3, 50 },
		{ &ProtocolVersion::v1_19, 49 },
		{ &ProtocolVersion::v1_17, 46 },
		{ &ProtocolVersion::v1_16_3, 42 }
	}
};
const acp::game::EntityType acp::game::EntityType::LLAMA_SPIT = {
	"llama_spit",
	"Llama Spit",
	{
		{ &ProtocolVersion::v1_16_3, { 0.25, 0.25, 0.25 } }
	},
	{
		{ &ProtocolVersion::v1_21, 66 },
		{ &ProtocolVersion::v1_20_3, 62 },
		{ &ProtocolVersion::v1_19_4, 61 },
		{ &ProtocolVersion::v1_19_3, 51 },
		{ &ProtocolVersion::v1_19, 50 },
		{ &ProtocolVersion::v1_17, 47 },
		{ &ProtocolVersion::v1_16_3, 43 }
	}
};
const acp::game::EntityType acp::game::EntityType::MAGMA_CUBE = {
	"magma_cube",
	"Magma Cube",
	{
		{ &ProtocolVersion::v1_21, { 0.52, 0.52, 0.52 } },
		{ &ProtocolVersion::v1_16_3, { 2.04, 2.04, 2.04 } }
	},
	{
		{ &ProtocolVersion::v1_21, 67 },
		{ &ProtocolVersion::v1_20_3, 63 },
		{ &ProtocolVersion::v1_19_4, 62 },
		{ &ProtocolVersion::v1_19_3, 52 },
		{ &ProtocolVersion::v1_19, 51 },
		{ &ProtocolVersion::v1_17, 48 },
		{ &ProtocolVersion::v1_16_3, 44 }
	}
};
const acp::game::EntityType acp::game::EntityType::MARKER = {
	"marker",
	"Marker",
	{
		{ &ProtocolVersion::v1_17, { 0, 0, 0 } }
	},
	{
		{ &ProtocolVersion::v1_21, 68 },
		{ &ProtocolVersion::v1_20_3, 64 },
		{ &ProtocolVersion::v1_19_4, 63 },
		{ &ProtocolVersion::v1_19_3, 53 },
		{ &ProtocolVersion::v1_19, 52 },
		{ &ProtocolVersion::v1_17, 49 }
	}
};
const acp::game::EntityType acp::game::EntityType::MINECART = {
	"minecart",
	"Minecart",
	{
		{ &ProtocolVersion::v1_16_3, { 0.98, 0.7, 0.98 } }
	},
	{
		{ &ProtocolVersion::v1_21, 69 },
		{ &ProtocolVersion::v1_20_3, 65 },
		{ &ProtocolVersion::v1_19_4, 64 },
		{ &ProtocolVersion::v1_19_3, 54 },
		{ &ProtocolVersion::v1_19, 53 },
		{ &ProtocolVersion::v1_17, 50 },
		{ &ProtocolVersion::v1_16_3, 45 }
	}
};
const acp::game::EntityType acp::game::EntityType::MOOSHROOM = {
	"mooshroom",
	"Mooshroom",
	{
		{ &ProtocolVersion::v1_16_3, { 0.9, 1.4, 0.9 } }
	},
	{
		{ &ProtocolVersion::v1_21, 70 },
		{ &ProtocolVersion::v1_20_3, 66 },
		{ &ProtocolVersion::v1_19_4, 65 },
		{ &ProtocolVersion::v1_19_3, 62 },
		{ &ProtocolVersion::v1_19, 61 },
		{ &ProtocolVersion::v1_17, 58 },
		{ &ProtocolVersion::v1_16_3, 53 }
	}
};
const acp::game::EntityType acp::game::EntityType::MULE = {
	"mule",
	"Mule",
	{
		{ &ProtocolVersion::v1_16_3, { 1.39648, 1.6, 1.39648 } }
	},
	{
		{ &ProtocolVersion::v1_21, 71 },
		{ &ProtocolVersion::v1_20_3, 67 },
		{ &ProtocolVersion::v1_19_4, 66 },
		{ &ProtocolVersion::v1_19_3, 61 },
		{ &ProtocolVersion::v1_19, 60 },
		{ &ProtocolVersion::v1_17, 57 },
		{ &ProtocolVersion::v1_16_3, 52 }
	}
};
const acp::game::EntityType acp::game::EntityType::OCELOT = {
	"ocelot",
	"Ocelot",
	{
		{ &ProtocolVersion::v1_16_3, { 0.6, 0.7, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 72 },
		{ &ProtocolVersion::v1_20_3, 68 },
		{ &ProtocolVersion::v1_19_4, 67 },
		{ &ProtocolVersion::v1_19_3, 63 },
		{ &ProtocolVersion::v1_19, 62 },
		{ &ProtocolVersion::v1_17, 59 },
		{ &ProtocolVersion::v1_16_3, 54 }
	}
};
const acp::game::EntityType acp::game::EntityType::OMINOUS_ITEM_SPAWNER = {
	"ominous_item_spawner",
	"Ominous Item Spawner",
	{
		{ &ProtocolVersion::v1_21, { 0.25, 0.25, 0.25 } }
	},
	{
		{ &ProtocolVersion::v1_21, 61 }
	}
};
const acp::game::EntityType acp::game::EntityType::PAINTING = {
	"painting",
	"Painting",
	{
		{ &ProtocolVersion::v1_16_3, { 0.5, 0.5, 0.5 } }
	},
	{
		{ &ProtocolVersion::v1_21, 73 },
		{ &ProtocolVersion::v1_20_3, 69 },
		{ &ProtocolVersion::v1_19_4, 68 },
		{ &ProtocolVersion::v1_19_3, 64 },
		{ &ProtocolVersion::v1_19, 63 },
		{ &ProtocolVersion::v1_17, 60 },
		{ &ProtocolVersion::v1_16_3, 55 }
	}
};
const acp::game::EntityType acp::game::EntityType::PANDA = {
	"panda",
	"Panda",
	{
		{ &ProtocolVersion::v1_16_3, { 1.3, 1.25, 1.3 } }
	},
	{
		{ &ProtocolVersion::v1_21, 74 },
		{ &ProtocolVersion::v1_20_3, 70 },
		{ &ProtocolVersion::v1_19_4, 69 },
		{ &ProtocolVersion::v1_19_3, 65 },
		{ &ProtocolVersion::v1_19, 64 },
		{ &ProtocolVersion::v1_17, 61 },
		{ &ProtocolVersion::v1_16_3, 56 }
	}
};
const acp::game::EntityType acp::game::EntityType::PARROT = {
	"parrot",
	"Parrot",
	{
		{ &ProtocolVersion::v1_16_3, { 0.5, 0.9, 0.5 } }
	},
	{
		{ &ProtocolVersion::v1_21, 75 },
		{ &ProtocolVersion::v1_20_3, 71 },
		{ &ProtocolVersion::v1_19_4, 70 },
		{ &ProtocolVersion::v1_19_3, 66 },
		{ &ProtocolVersion::v1_19, 65 },
		{ &ProtocolVersion::v1_17, 62 },
		{ &ProtocolVersion::v1_16_3, 57 }
	}
};
const acp::game::EntityType acp::game::EntityType::PHANTOM = {
	"phantom",
	"Phantom",
	{
		{ &ProtocolVersion::v1_16_3, { 0.9, 0.5, 0.9 } }
	},
	{
		{ &ProtocolVersion::v1_21, 76 },
		{ &ProtocolVersion::v1_20_3, 72 },
		{ &ProtocolVersion::v1_19_4, 71 },
		{ &ProtocolVersion::v1_19_3, 67 },
		{ &ProtocolVersion::v1_19, 66 },
		{ &ProtocolVersion::v1_17, 63 },
		{ &ProtocolVersion::v1_16_3, 58 }
	}
};
const acp::game::EntityType acp::game::EntityType::PIG = {
	"pig",
	"Pig",
	{
		{ &ProtocolVersion::v1_16_3, { 0.9, 0.9, 0.9 } }
	},
	{
		{ &ProtocolVersion::v1_21, 77 },
		{ &ProtocolVersion::v1_20_3, 73 },
		{ &ProtocolVersion::v1_19_4, 72 },
		{ &ProtocolVersion::v1_19_3, 68 },
		{ &ProtocolVersion::v1_19, 67 },
		{ &ProtocolVersion::v1_17, 64 },
		{ &ProtocolVersion::v1_16_3, 59 }
	}
};
const acp::game::EntityType acp::game::EntityType::PIGLIN = {
	"piglin",
	"Piglin",
	{
		{ &ProtocolVersion::v1_16_3, { 0.6, 1.95, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 78 },
		{ &ProtocolVersion::v1_20_3, 74 },
		{ &ProtocolVersion::v1_19_4, 73 },
		{ &ProtocolVersion::v1_19_3, 69 },
		{ &ProtocolVersion::v1_19, 68 },
		{ &ProtocolVersion::v1_17, 65 },
		{ &ProtocolVersion::v1_16_3, 60 }
	}
};
const acp::game::EntityType acp::game::EntityType::PIGLIN_BRUTE = {
	"piglin_brute",
	"Piglin Brute",
	{
		{ &ProtocolVersion::v1_16_3, { 0.6, 1.95, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 79 },
		{ &ProtocolVersion::v1_20_3, 75 },
		{ &ProtocolVersion::v1_19_4, 74 },
		{ &ProtocolVersion::v1_19_3, 70 },
		{ &ProtocolVersion::v1_19, 69 },
		{ &ProtocolVersion::v1_17, 66 },
		{ &ProtocolVersion::v1_16_3, 61 }
	}
};
const acp::game::EntityType acp::game::EntityType::PILLAGER = {
	"pillager",
	"Pillager",
	{
		{ &ProtocolVersion::v1_16_3, { 0.6, 1.95, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 80 },
		{ &ProtocolVersion::v1_20_3, 76 },
		{ &ProtocolVersion::v1_19_4, 75 },
		{ &ProtocolVersion::v1_19_3, 71 },
		{ &ProtocolVersion::v1_19, 70 },
		{ &ProtocolVersion::v1_17, 67 },
		{ &ProtocolVersion::v1_16_3, 62 }
	}
};
const acp::game::EntityType acp::game::EntityType::PLAYER = {
	"player",
	"Player",
	{
		{ &ProtocolVersion::v1_16_3, { 0.6, 1.8, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 128 },
		{ &ProtocolVersion::v1_20_3, 124 },
		{ &ProtocolVersion::v1_19_4, 122 },
		{ &ProtocolVersion::v1_19_3, 117 },
		{ &ProtocolVersion::v1_19, 116 },
		{ &ProtocolVersion::v1_17, 111 },
		{ &ProtocolVersion::v1_16_3, 106 }
	}
};
const acp::game::EntityType acp::game::EntityType::POLAR_BEAR = {
	"polar_bear",
	"Polar Bear",
	{
		{ &ProtocolVersion::v1_16_3, { 1.4, 1.4, 1.4 } }
	},
	{
		{ &ProtocolVersion::v1_21, 81 },
		{ &ProtocolVersion::v1_20_3, 77 },
		{ &ProtocolVersion::v1_19_4, 76 },
		{ &ProtocolVersion::v1_19_3, 72 },
		{ &ProtocolVersion::v1_19, 71 },
		{ &ProtocolVersion::v1_17, 68 },
		{ &ProtocolVersion::v1_16_3, 63 }
	}
};
const acp::game::EntityType acp::game::EntityType::POTION = {
	"potion",
	"Potion",
	{
		{ &ProtocolVersion::v1_19_4, { 0.25, 0.25, 0.25 } }
	},
	{
		{ &ProtocolVersion::v1_19_3, 97 },
		{ &ProtocolVersion::v1_19, 96 },
		{ &ProtocolVersion::v1_17, 92 },
		{ &ProtocolVersion::v1_16_3, 87 },
		{ &ProtocolVersion::v1_21, 82 },
		{ &ProtocolVersion::v1_20_3, 78 },
		{ &ProtocolVersion::v1_19_4, 77 }
	}
};
const acp::game::EntityType acp::game::EntityType::PUFFERFISH = {
	"pufferfish",
	"Pufferfish",
	{
		{ &ProtocolVersion::v1_16_3, { 0.7, 0.7, 0.7 } }
	},
	{
		{ &ProtocolVersion::v1_21, 83 },
		{ &ProtocolVersion::v1_20_3, 79 },
		{ &ProtocolVersion::v1_19_4, 78 },
		{ &ProtocolVersion::v1_19_3, 74 },
		{ &ProtocolVersion::v1_19, 73 },
		{ &ProtocolVersion::v1_17, 70 },
		{ &ProtocolVersion::v1_16_3, 65 }
	}
};
const acp::game::EntityType acp::game::EntityType::RABBIT = {
	"rabbit",
	"Rabbit",
	{
		{ &ProtocolVersion::v1_16_3, { 0.4, 0.5, 0.4 } }
	},
	{
		{ &ProtocolVersion::v1_21, 84 },
		{ &ProtocolVersion::v1_20_3, 80 },
		{ &ProtocolVersion::v1_19_4, 79 },
		{ &ProtocolVersion::v1_19_3, 75 },
		{ &ProtocolVersion::v1_19, 74 },
		{ &ProtocolVersion::v1_17, 71 },
		{ &ProtocolVersion::v1_16_3, 66 }
	}
};
const acp::game::EntityType acp::game::EntityType::RAVAGER = {
	"ravager",
	"Ravager",
	{
		{ &ProtocolVersion::v1_16_3, { 1.95, 2.2, 1.95 } }
	},
	{
		{ &ProtocolVersion::v1_21, 85 },
		{ &ProtocolVersion::v1_20_3, 81 },
		{ &ProtocolVersion::v1_19_4, 80 },
		{ &ProtocolVersion::v1_19_3, 76 },
		{ &ProtocolVersion::v1_19, 75 },
		{ &ProtocolVersion::v1_17, 72 },
		{ &ProtocolVersion::v1_16_3, 67 }
	}
};
const acp::game::EntityType acp::game::EntityType::SALMON = {
	"salmon",
	"Salmon",
	{
		{ &ProtocolVersion::v1_16_3, { 0.7, 0.4, 0.7 } }
	},
	{
		{ &ProtocolVersion::v1_21, 86 },
		{ &ProtocolVersion::v1_20_3, 82 },
		{ &ProtocolVersion::v1_19_4, 81 },
		{ &ProtocolVersion::v1_19_3, 77 },
		{ &ProtocolVersion::v1_19, 76 },
		{ &ProtocolVersion::v1_17, 73 },
		{ &ProtocolVersion::v1_16_3, 68 }
	}
};
const acp::game::EntityType acp::game::EntityType::SHEEP = {
	"sheep",
	"Sheep",
	{
		{ &ProtocolVersion::v1_16_3, { 0.9, 1.3, 0.9 } }
	},
	{
		{ &ProtocolVersion::v1_21, 87 },
		{ &ProtocolVersion::v1_20_3, 83 },
		{ &ProtocolVersion::v1_19_4, 82 },
		{ &ProtocolVersion::v1_19_3, 78 },
		{ &ProtocolVersion::v1_19, 77 },
		{ &ProtocolVersion::v1_17, 74 },
		{ &ProtocolVersion::v1_16_3, 69 }
	}
};
const acp::game::EntityType acp::game::EntityType::SHULKER = {
	"shulker",
	"Shulker",
	{
		{ &ProtocolVersion::v1_16_3, { 1, 1, 1 } }
	},
	{
		{ &ProtocolVersion::v1_21, 88 },
		{ &ProtocolVersion::v1_20_3, 84 },
		{ &ProtocolVersion::v1_19_4, 83 },
		{ &ProtocolVersion::v1_19_3, 79 },
		{ &ProtocolVersion::v1_19, 78 },
		{ &ProtocolVersion::v1_17, 75 },
		{ &ProtocolVersion::v1_16_3, 70 }
	}
};
const acp::game::EntityType acp::game::EntityType::SHULKER_BULLET = {
	"shulker_bullet",
	"Shulker Bullet",
	{
		{ &ProtocolVersion::v1_16_3, { 0.3125, 0.3125, 0.3125 } }
	},
	{
		{ &ProtocolVersion::v1_21, 89 },
		{ &ProtocolVersion::v1_20_3, 85 },
		{ &ProtocolVersion::v1_19_4, 84 },
		{ &ProtocolVersion::v1_19_3, 80 },
		{ &ProtocolVersion::v1_19, 79 },
		{ &ProtocolVersion::v1_17, 76 },
		{ &ProtocolVersion::v1_16_3, 71 }
	}
};
const acp::game::EntityType acp::game::EntityType::SILVERFISH = {
	"silverfish",
	"Silverfish",
	{
		{ &ProtocolVersion::v1_16_3, { 0.4, 0.3, 0.4 } }
	},
	{
		{ &ProtocolVersion::v1_21, 90 },
		{ &ProtocolVersion::v1_20_3, 86 },
		{ &ProtocolVersion::v1_19_4, 85 },
		{ &ProtocolVersion::v1_19_3, 81 },
		{ &ProtocolVersion::v1_19, 80 },
		{ &ProtocolVersion::v1_17, 77 },
		{ &ProtocolVersion::v1_16_3, 72 }
	}
};
const acp::game::EntityType acp::game::EntityType::SKELETON = {
	"skeleton",
	"Skeleton",
	{
		{ &ProtocolVersion::v1_16_3, { 0.6, 1.99, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 91 },
		{ &ProtocolVersion::v1_20_3, 87 },
		{ &ProtocolVersion::v1_19_4, 86 },
		{ &ProtocolVersion::v1_19_3, 82 },
		{ &ProtocolVersion::v1_19, 81 },
		{ &ProtocolVersion::v1_17, 78 },
		{ &ProtocolVersion::v1_16_3, 73 }
	}
};
const acp::game::EntityType acp::game::EntityType::SKELETON_HORSE = {
	"skeleton_horse",
	"Skeleton Horse",
	{
		{ &ProtocolVersion::v1_16_3, { 1.39648, 1.6, 1.39648 } }
	},
	{
		{ &ProtocolVersion::v1_21, 92 },
		{ &ProtocolVersion::v1_20_3, 88 },
		{ &ProtocolVersion::v1_19_4, 87 },
		{ &ProtocolVersion::v1_19_3, 83 },
		{ &ProtocolVersion::v1_19, 82 },
		{ &ProtocolVersion::v1_17, 79 },
		{ &ProtocolVersion::v1_16_3, 74 }
	}
};
const acp::game::EntityType acp::game::EntityType::SLIME = {
	"slime",
	"Slime",
	{
		{ &ProtocolVersion::v1_21, { 0.52, 0.52, 0.52 } },
		{ &ProtocolVersion::v1_16_3, { 2.04, 2.04, 2.04 } }
	},
	{
		{ &ProtocolVersion::v1_21, 93 },
		{ &ProtocolVersion::v1_20_3, 89 },
		{ &ProtocolVersion::v1_19_4, 88 },
		{ &ProtocolVersion::v1_19_3, 84 },
		{ &ProtocolVersion::v1_19, 83 },
		{ &ProtocolVersion::v1_17, 80 },
		{ &ProtocolVersion::v1_16_3, 75 }
	}
};
const acp::game::EntityType acp::game::EntityType::SMALL_FIREBALL = {
	"small_fireball",
	"Small Fireball",
	{
		{ &ProtocolVersion::v1_16_3, { 0.3125, 0.3125, 0.3125 } }
	},
	{
		{ &ProtocolVersion::v1_21, 94 },
		{ &ProtocolVersion::v1_20_3, 90 },
		{ &ProtocolVersion::v1_19_4, 89 },
		{ &ProtocolVersion::v1_19_3, 85 },
		{ &ProtocolVersion::v1_19, 84 },
		{ &ProtocolVersion::v1_17, 81 },
		{ &ProtocolVersion::v1_16_3, 76 }
	}
};
const acp::game::EntityType acp::game::EntityType::SNIFFER = {
	"sniffer",
	"Sniffer",
	{
		{ &ProtocolVersion::v1_19_4, { 1.9, 1.75, 1.9 } }
	},
	{
		{ &ProtocolVersion::v1_21, 95 },
		{ &ProtocolVersion::v1_20_3, 91 },
		{ &ProtocolVersion::v1_19_4, 90 }
	}
};
const acp::game::EntityType acp::game::EntityType::SNOW_GOLEM = {
	"snow_golem",
	"Snow Golem",
	{
		{ &ProtocolVersion::v1_16_3, { 0.7, 1.9, 0.7 } }
	},
	{
		{ &ProtocolVersion::v1_21, 96 },
		{ &ProtocolVersion::v1_20_3, 92 },
		{ &ProtocolVersion::v1_19_4, 91 },
		{ &ProtocolVersion::v1_19_3, 86 },
		{ &ProtocolVersion::v1_19, 85 },
		{ &ProtocolVersion::v1_17, 82 },
		{ &ProtocolVersion::v1_16_3, 77 }
	}
};
const acp::game::EntityType acp::game::EntityType::SNOWBALL = {
	"snowball",
	"Snowball",
	{
		{ &ProtocolVersion::v1_16_3, { 0.25, 0.25, 0.25 } }
	},
	{
		{ &ProtocolVersion::v1_21, 97 },
		{ &ProtocolVersion::v1_20_3, 93 },
		{ &ProtocolVersion::v1_19_4, 92 },
		{ &ProtocolVersion::v1_19_3, 87 },
		{ &ProtocolVersion::v1_19, 86 },
		{ &ProtocolVersion::v1_17, 83 },
		{ &ProtocolVersion::v1_16_3, 78 }
	}
};
const acp::game::EntityType acp::game::EntityType::SPAWNER_MINECART = {
	"spawner_minecart",
	"Minecart with Monster Spawner",
	{
		{ &ProtocolVersion::v1_16_3, { 0.98, 0.7, 0.98 } }
	},
	{
		{ &ProtocolVersion::v1_21, 98 },
		{ &ProtocolVersion::v1_20_3, 94 },
		{ &ProtocolVersion::v1_19_4, 93 },
		{ &ProtocolVersion::v1_19_3, 59 },
		{ &ProtocolVersion::v1_19, 58 },
		{ &ProtocolVersion::v1_17, 55 },
		{ &ProtocolVersion::v1_16_3, 50 }
	}
};
const acp::game::EntityType acp::game::EntityType::SPECTRAL_ARROW = {
	"spectral_arrow",
	"Spectral Arrow",
	{
		{ &ProtocolVersion::v1_16_3, { 0.5, 0.5, 0.5 } }
	},
	{
		{ &ProtocolVersion::v1_21, 99 },
		{ &ProtocolVersion::v1_20_3, 95 },
		{ &ProtocolVersion::v1_19_4, 94 },
		{ &ProtocolVersion::v1_19_3, 88 },
		{ &ProtocolVersion::v1_19, 87 },
		{ &ProtocolVersion::v1_17, 84 },
		{ &ProtocolVersion::v1_16_3, 79 }
	}
};
const acp::game::EntityType acp::game::EntityType::SPIDER = {
	"spider",
	"Spider",
	{
		{ &ProtocolVersion::v1_16_3, { 1.4, 0.9, 1.4 } }
	},
	{
		{ &ProtocolVersion::v1_21, 100 },
		{ &ProtocolVersion::v1_20_3, 96 },
		{ &ProtocolVersion::v1_19_4, 95 },
		{ &ProtocolVersion::v1_19_3, 89 },
		{ &ProtocolVersion::v1_19, 88 },
		{ &ProtocolVersion::v1_17, 85 },
		{ &ProtocolVersion::v1_16_3, 80 }
	}
};
const acp::game::EntityType acp::game::EntityType::SQUID = {
	"squid",
	"Squid",
	{
		{ &ProtocolVersion::v1_16_3, { 0.8, 0.8, 0.8 } }
	},
	{
		{ &ProtocolVersion::v1_21, 101 },
		{ &ProtocolVersion::v1_20_3, 97 },
		{ &ProtocolVersion::v1_19_4, 96 },
		{ &ProtocolVersion::v1_19_3, 90 },
		{ &ProtocolVersion::v1_19, 89 },
		{ &ProtocolVersion::v1_17, 86 },
		{ &ProtocolVersion::v1_16_3, 81 }
	}
};
const acp::game::EntityType acp::game::EntityType::STRAY = {
	"stray",
	"Stray",
	{
		{ &ProtocolVersion::v1_16_3, { 0.6, 1.99, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 102 },
		{ &ProtocolVersion::v1_20_3, 98 },
		{ &ProtocolVersion::v1_19_4, 97 },
		{ &ProtocolVersion::v1_19_3, 91 },
		{ &ProtocolVersion::v1_19, 90 },
		{ &ProtocolVersion::v1_17, 87 },
		{ &ProtocolVersion::v1_16_3, 82 }
	}
};
const acp::game::EntityType acp::game::EntityType::STRIDER = {
	"strider",
	"Strider",
	{
		{ &ProtocolVersion::v1_16_3, { 0.9, 1.7, 0.9 } }
	},
	{
		{ &ProtocolVersion::v1_21, 103 },
		{ &ProtocolVersion::v1_20_3, 99 },
		{ &ProtocolVersion::v1_19_4, 98 },
		{ &ProtocolVersion::v1_19_3, 92 },
		{ &ProtocolVersion::v1_19, 91 },
		{ &ProtocolVersion::v1_17, 88 },
		{ &ProtocolVersion::v1_16_3, 83 }
	}
};
const acp::game::EntityType acp::game::EntityType::TADPOLE = {
	"tadpole",
	"Tadpole",
	{
		{ &ProtocolVersion::v1_21, { 0.4, 0.3, 0.4 } },
		{ &ProtocolVersion::v1_19, { 0, 0, 0 } }
	},
	{
		{ &ProtocolVersion::v1_21, 104 },
		{ &ProtocolVersion::v1_20_3, 100 },
		{ &ProtocolVersion::v1_19_4, 99 },
		{ &ProtocolVersion::v1_19_3, 93 },
		{ &ProtocolVersion::v1_19, 92 }
	}
};
const acp::game::EntityType acp::game::EntityType::TEXT_DISPLAY = {
	"text_display",
	"Text Display",
	{
		{ &ProtocolVersion::v1_19_4, { 0, 0, 0 } }
	},
	{
		{ &ProtocolVersion::v1_21, 105 },
		{ &ProtocolVersion::v1_20_3, 101 },
		{ &ProtocolVersion::v1_19_4, 100 }
	}
};
const acp::game::EntityType acp::game::EntityType::TNT = {
	"tnt",
	"Primed TNT",
	{
		{ &ProtocolVersion::v1_16_3, { 0.98, 0.98, 0.98 } }
	},
	{
		{ &ProtocolVersion::v1_21, 106 },
		{ &ProtocolVersion::v1_20_3, 102 },
		{ &ProtocolVersion::v1_19_4, 101 },
		{ &ProtocolVersion::v1_19_3, 73 },
		{ &ProtocolVersion::v1_19, 72 },
		{ &ProtocolVersion::v1_17, 69 },
		{ &ProtocolVersion::v1_16_3, 64 }
	}
};
const acp::game::EntityType acp::game::EntityType::TNT_MINECART = {
	"tnt_minecart",
	"Minecart with TNT",
	{
		{ &ProtocolVersion::v1_16_3, { 0.98, 0.7, 0.98 } }
	},
	{
		{ &ProtocolVersion::v1_21, 107 },
		{ &ProtocolVersion::v1_20_3, 103 },
		{ &ProtocolVersion::v1_19_4, 102 },
		{ &ProtocolVersion::v1_19_3, 60 },
		{ &ProtocolVersion::v1_19, 59 },
		{ &ProtocolVersion::v1_17, 56 },
		{ &ProtocolVersion::v1_16_3, 51 }
	}
};
const acp::game::EntityType acp::game::EntityType::TRADER_LLAMA = {
	"trader_llama",
	"Trader Llama",
	{
		{ &ProtocolVersion::v1_16_3, { 0.9, 1.87, 0.9 } }
	},
	{
		{ &ProtocolVersion::v1_21, 108 },
		{ &ProtocolVersion::v1_20_3, 104 },
		{ &ProtocolVersion::v1_19_4, 103 },
		{ &ProtocolVersion::v1_19_3, 99 },
		{ &ProtocolVersion::v1_19, 98 },
		{ &ProtocolVersion::v1_17, 94 },
		{ &ProtocolVersion::v1_16_3, 89 }
	}
};
const acp::game::EntityType acp::game::EntityType::TRIDENT = {
	"trident",
	"Trident",
	{
		{ &ProtocolVersion::v1_16_3, { 0.5, 0.5, 0.5 } }
	},
	{
		{ &ProtocolVersion::v1_21, 109 },
		{ &ProtocolVersion::v1_20_3, 105 },
		{ &ProtocolVersion::v1_19_4, 104 },
		{ &ProtocolVersion::v1_19_3, 98 },
		{ &ProtocolVersion::v1_19, 97 },
		{ &ProtocolVersion::v1_17, 93 },
		{ &ProtocolVersion::v1_16_3, 88 }
	}
};
const acp::game::EntityType acp::game::EntityType::TROPICAL_FISH = {
	"tropical_fish",
	"Tropical Fish",
	{
		{ &ProtocolVersion::v1_16_3, { 0.5, 0.4, 0.5 } }
	},
	{
		{ &ProtocolVersion::v1_21, 110 },
		{ &ProtocolVersion::v1_20_3, 106 },
		{ &ProtocolVersion::v1_19_4, 105 },
		{ &ProtocolVersion::v1_19_3, 100 },
		{ &ProtocolVersion::v1_19, 99 },
		{ &ProtocolVersion::v1_17, 95 },
		{ &ProtocolVersion::v1_16_3, 90 }
	}
};
const acp::game::EntityType acp::game::EntityType::TURTLE = {
	"turtle",
	"Turtle",
	{
		{ &ProtocolVersion::v1_16_3, { 1.2, 0.4, 1.2 } }
	},
	{
		{ &ProtocolVersion::v1_21, 111 },
		{ &ProtocolVersion::v1_20_3, 107 },
		{ &ProtocolVersion::v1_19_4, 106 },
		{ &ProtocolVersion::v1_19_3, 101 },
		{ &ProtocolVersion::v1_19, 100 },
		{ &ProtocolVersion::v1_17, 96 },
		{ &ProtocolVersion::v1_16_3, 91 }
	}
};
const acp::game::EntityType acp::game::EntityType::VEX = {
	"vex",
	"Vex",
	{
		{ &ProtocolVersion::v1_16_3, { 0.4, 0.8, 0.4 } }
	},
	{
		{ &ProtocolVersion::v1_21, 112 },
		{ &ProtocolVersion::v1_20_3, 108 },
		{ &ProtocolVersion::v1_19_4, 107 },
		{ &ProtocolVersion::v1_19_3, 102 },
		{ &ProtocolVersion::v1_19, 101 },
		{ &ProtocolVersion::v1_17, 97 },
		{ &ProtocolVersion::v1_16_3, 92 }
	}
};
const acp::game::EntityType acp::game::EntityType::VILLAGER = {
	"villager",
	"Villager",
	{
		{ &ProtocolVersion::v1_16_3, { 0.6, 1.95, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 113 },
		{ &ProtocolVersion::v1_20_3, 109 },
		{ &ProtocolVersion::v1_19_4, 108 },
		{ &ProtocolVersion::v1_19_3, 103 },
		{ &ProtocolVersion::v1_19, 102 },
		{ &ProtocolVersion::v1_17, 98 },
		{ &ProtocolVersion::v1_16_3, 93 }
	}
};
const acp::game::EntityType acp::game::EntityType::VINDICATOR = {
	"vindicator",
	"Vindicator",
	{
		{ &ProtocolVersion::v1_16_3, { 0.6, 1.95, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 114 },
		{ &ProtocolVersion::v1_20_3, 110 },
		{ &ProtocolVersion::v1_19_4, 109 },
		{ &ProtocolVersion::v1_19_3, 104 },
		{ &ProtocolVersion::v1_19, 103 },
		{ &ProtocolVersion::v1_17, 99 },
		{ &ProtocolVersion::v1_16_3, 94 }
	}
};
const acp::game::EntityType acp::game::EntityType::WANDERING_TRADER = {
	"wandering_trader",
	"Wandering Trader",
	{
		{ &ProtocolVersion::v1_16_3, { 0.6, 1.95, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 115 },
		{ &ProtocolVersion::v1_20_3, 111 },
		{ &ProtocolVersion::v1_19_4, 110 },
		{ &ProtocolVersion::v1_19_3, 105 },
		{ &ProtocolVersion::v1_19, 104 },
		{ &ProtocolVersion::v1_17, 100 },
		{ &ProtocolVersion::v1_16_3, 95 }
	}
};
const acp::game::EntityType acp::game::EntityType::WARDEN = {
	"warden",
	"Warden",
	{
		{ &ProtocolVersion::v1_19, { 0.9, 2.9, 0.9 } }
	},
	{
		{ &ProtocolVersion::v1_21, 116 },
		{ &ProtocolVersion::v1_20_3, 112 },
		{ &ProtocolVersion::v1_19_4, 111 },
		{ &ProtocolVersion::v1_19_3, 106 },
		{ &ProtocolVersion::v1_19, 105 }
	}
};
const acp::game::EntityType acp::game::EntityType::WIND_CHARGE = {
	"wind_charge",
	"Wind Charge",
	{
		{ &ProtocolVersion::v1_20_3, { 0.3125, 0.3125, 0.3125 } }
	},
	{
		{ &ProtocolVersion::v1_21, 117 },
		{ &ProtocolVersion::v1_20_3, 113 }
	}
};
const acp::game::EntityType acp::game::EntityType::WITCH = {
	"witch",
	"Witch",
	{
		{ &ProtocolVersion::v1_16_3, { 0.6, 1.95, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 118 },
		{ &ProtocolVersion::v1_20_3, 114 },
		{ &ProtocolVersion::v1_19_4, 112 },
		{ &ProtocolVersion::v1_19_3, 107 },
		{ &ProtocolVersion::v1_19, 106 },
		{ &ProtocolVersion::v1_17, 101 },
		{ &ProtocolVersion::v1_16_3, 96 }
	}
};
const acp::game::EntityType acp::game::EntityType::WITHER = {
	"wither",
	"Wither",
	{
		{ &ProtocolVersion::v1_16_3, { 0.9, 3.5, 0.9 } }
	},
	{
		{ &ProtocolVersion::v1_21, 119 },
		{ &ProtocolVersion::v1_20_3, 115 },
		{ &ProtocolVersion::v1_19_4, 113 },
		{ &ProtocolVersion::v1_19_3, 108 },
		{ &ProtocolVersion::v1_19, 107 },
		{ &ProtocolVersion::v1_17, 102 },
		{ &ProtocolVersion::v1_16_3, 97 }
	}
};
const acp::game::EntityType acp::game::EntityType::WITHER_SKELETON = {
	"wither_skeleton",
	"Wither Skeleton",
	{
		{ &ProtocolVersion::v1_16_3, { 0.7, 2.4, 0.7 } }
	},
	{
		{ &ProtocolVersion::v1_21, 120 },
		{ &ProtocolVersion::v1_20_3, 116 },
		{ &ProtocolVersion::v1_19_4, 114 },
		{ &ProtocolVersion::v1_19_3, 109 },
		{ &ProtocolVersion::v1_19, 108 },
		{ &ProtocolVersion::v1_17, 103 },
		{ &ProtocolVersion::v1_16_3, 98 }
	}
};
const acp::game::EntityType acp::game::EntityType::WITHER_SKULL = {
	"wither_skull",
	"Wither Skull",
	{
		{ &ProtocolVersion::v1_16_3, { 0.3125, 0.3125, 0.3125 } }
	},
	{
		{ &ProtocolVersion::v1_21, 121 },
		{ &ProtocolVersion::v1_20_3, 117 },
		{ &ProtocolVersion::v1_19_4, 115 },
		{ &ProtocolVersion::v1_19_3, 110 },
		{ &ProtocolVersion::v1_19, 109 },
		{ &ProtocolVersion::v1_17, 104 },
		{ &ProtocolVersion::v1_16_3, 99 }
	}
};
const acp::game::EntityType acp::game::EntityType::WOLF = {
	"wolf",
	"Wolf",
	{
		{ &ProtocolVersion::v1_16_3, { 0.6, 0.85, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 122 },
		{ &ProtocolVersion::v1_20_3, 118 },
		{ &ProtocolVersion::v1_19_4, 116 },
		{ &ProtocolVersion::v1_19_3, 111 },
		{ &ProtocolVersion::v1_19, 110 },
		{ &ProtocolVersion::v1_17, 105 },
		{ &ProtocolVersion::v1_16_3, 100 }
	}
};
const acp::game::EntityType acp::game::EntityType::ZOGLIN = {
	"zoglin",
	"Zoglin",
	{
		{ &ProtocolVersion::v1_16_3, { 1.39648, 1.4, 1.39648 } }
	},
	{
		{ &ProtocolVersion::v1_21, 123 },
		{ &ProtocolVersion::v1_20_3, 119 },
		{ &ProtocolVersion::v1_19_4, 117 },
		{ &ProtocolVersion::v1_19_3, 112 },
		{ &ProtocolVersion::v1_19, 111 },
		{ &ProtocolVersion::v1_17, 106 },
		{ &ProtocolVersion::v1_16_3, 101 }
	}
};
const acp::game::EntityType acp::game::EntityType::ZOMBIE = {
	"zombie",
	"Zombie",
	{
		{ &ProtocolVersion::v1_16_3, { 0.6, 1.95, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 124 },
		{ &ProtocolVersion::v1_20_3, 120 },
		{ &ProtocolVersion::v1_19_4, 118 },
		{ &ProtocolVersion::v1_19_3, 113 },
		{ &ProtocolVersion::v1_19, 112 },
		{ &ProtocolVersion::v1_17, 107 },
		{ &ProtocolVersion::v1_16_3, 102 }
	}
};
const acp::game::EntityType acp::game::EntityType::ZOMBIE_HORSE = {
	"zombie_horse",
	"Zombie Horse",
	{
		{ &ProtocolVersion::v1_16_3, { 1.39648, 1.6, 1.39648 } }
	},
	{
		{ &ProtocolVersion::v1_21, 125 },
		{ &ProtocolVersion::v1_20_3, 121 },
		{ &ProtocolVersion::v1_19_4, 119 },
		{ &ProtocolVersion::v1_19_3, 114 },
		{ &ProtocolVersion::v1_19, 113 },
		{ &ProtocolVersion::v1_17, 108 },
		{ &ProtocolVersion::v1_16_3, 103 }
	}
};
const acp::game::EntityType acp::game::EntityType::ZOMBIE_VILLAGER = {
	"zombie_villager",
	"Zombie Villager",
	{
		{ &ProtocolVersion::v1_16_3, { 0.6, 1.95, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 126 },
		{ &ProtocolVersion::v1_20_3, 122 },
		{ &ProtocolVersion::v1_19_4, 120 },
		{ &ProtocolVersion::v1_19_3, 115 },
		{ &ProtocolVersion::v1_19, 114 },
		{ &ProtocolVersion::v1_17, 109 },
		{ &ProtocolVersion::v1_16_3, 104 }
	}
};
const acp::game::EntityType acp::game::EntityType::ZOMBIFIED_PIGLIN = {
	"zombified_piglin",
	"Zombified Piglin",
	{
		{ &ProtocolVersion::v1_16_3, { 0.6, 1.95, 0.6 } }
	},
	{
		{ &ProtocolVersion::v1_21, 127 },
		{ &ProtocolVersion::v1_20_3, 123 },
		{ &ProtocolVersion::v1_19_4, 121 },
		{ &ProtocolVersion::v1_19_3, 116 },
		{ &ProtocolVersion::v1_19, 115 },
		{ &ProtocolVersion::v1_17, 110 },
		{ &ProtocolVersion::v1_16_3, 105 }
	}
};
