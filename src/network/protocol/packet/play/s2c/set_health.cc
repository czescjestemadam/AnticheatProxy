#include "set_health.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::SetHealth::read(const ProtocolVersion* version)
{
	health = buf.readFloat();
	food = buf.readVarint();
	foodSaturation = buf.readFloat();
}

void acp::packet::play::s2c::SetHealth::write(const ProtocolVersion* version)
{
	buf.writeFloat(health);
	buf.writeVarint(food);
	buf.writeFloat(foodSaturation);
}

acp::HandleResult acp::packet::play::s2c::SetHealth::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::SetHealth::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x5D;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x5B;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x59;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x57;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x53;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x55;
	if (*version >= ProtocolVersion::v1_17)
		return 0x52;

	return 0x49;
}

float acp::packet::play::s2c::SetHealth::getHealth() const
{
	return health;
}

void acp::packet::play::s2c::SetHealth::setHealth(const float health)
{
	this->health = health;
}

int acp::packet::play::s2c::SetHealth::getFood() const
{
	return food;
}

void acp::packet::play::s2c::SetHealth::setFood(const int food)
{
	this->food = food;
}

float acp::packet::play::s2c::SetHealth::getFoodSaturation() const
{
	return foodSaturation;
}

void acp::packet::play::s2c::SetHealth::setFoodSaturation(const float food_saturation)
{
	foodSaturation = food_saturation;
}

std::string acp::packet::play::s2c::SetHealth::toString() const
{
	return std::format("SetHealth[hp={:.2f}, food={}, sat={:.2f}]", health, food, foodSaturation);
}
