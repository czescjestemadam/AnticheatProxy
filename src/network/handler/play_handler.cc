#include "play_handler.hh"

#include "anticheat_proxy.hh"
#include "anticheat/check/i_interact_check.hh"
#include "network/connection.hh"
#include "util/command/properties/string_properties.hh"

#include <cmath>

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::ConfirmTeleportation* packet)
{
	if (pendingTeleports.contains(packet->getTeleportId()))
	{
		auto& pending = pendingTeleports[packet->getTeleportId()];

		AcpPlayer& player = connection->getPlayer();

		const byte_t fl = pending.getFlags();
		player.getPosition().x = fl & 0x01 ? player.getPosition().x + pending.getPosition().x : pending.getPosition().x;
		player.getPosition().y = fl & 0x02 ? player.getPosition().y + pending.getPosition().y : pending.getPosition().y;
		player.getPosition().z = fl & 0x04 ? player.getPosition().z + pending.getPosition().z : pending.getPosition().z;

		player.setPitch(fl & 0x08 ? player.getPitch() + pending.getPitch() : pending.getPitch());
		player.setYaw(fl & 0x10 ? player.getYaw() + pending.getYaw() : pending.getYaw());

		pendingTeleports.erase(packet->getTeleportId());
	}

	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::QueryBlockEntityTag* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::ChangeDifficulty* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::AcknowledgeMessage* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::ChatCommand* packet)
{
	if (packet->getCommand().starts_with("acp") && connection->getPlayer().hasPermission(Permission::CMD))
	{
		connection->getLogger().info("{} executed: /{}", connection->getGameProfile().username, packet->getCommand());
		AnticheatProxy::get()->getCommandManager().executePacket(&connection->getPlayer(), packet->getCommand());
		return HandleResult::CANCEL;
	}

	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::SignedChatCommand* packet)
{
	if (packet->getCommand().starts_with("acp") && connection->getPlayer().hasPermission(Permission::CMD))
	{
		connection->getLogger().info("{} executed signed: /{}", connection->getGameProfile().username, packet->getCommand());
		AnticheatProxy::get()->getCommandManager().executePacket(&connection->getPlayer(), packet->getCommand());
		return HandleResult::CANCEL;
	}

	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::ChatMessage* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::PlayerSession* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::ChunkBatchReceived* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::ClientStatus* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::ClientInformation* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::CommandSuggestionsRequest* packet)
{
	if (packet->getText().starts_with("acp") && connection->getPlayer().hasPermission(Permission::CMD))
	{
		AnticheatProxy::get()->getCommandManager().completePacket(&connection->getPlayer(), packet->getText(), packet->getTransactionId());
		return HandleResult::CANCEL;
	}

	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::AcknowledgeConfiguration* packet)
{
	connection->setState(NetworkState::CONFIGURATION);

	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::ClickContainerButton* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::ClickContainer* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::CloseContainer* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::ChangeContainerSlotState* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::CookieResponse* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::PluginMessage* packet)
{
	return connection->getMessenger().onPluginMessage(NetworkSide::DEST, packet);
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::DebugSampleSubscription* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::EditBook* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::QueryEntityTag* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::Interact* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::JigsawGenerate* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::KeepAlive* packet)
{
	const long id = packet->getKeepAliveId();
	connection->getPingTracker().onReceive(id);

	return id < 0 ? HandleResult::CANCEL : HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::LockDifficulty* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::SetPlayerPosition* packet)
{
	AcpPlayer& player = connection->getPlayer();
	player.setPosition(packet->getPosition());
	player.setOnGround(packet->isOnGround());

	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::SetPlayerPositionRotation* packet)
{
	AcpPlayer& player = connection->getPlayer();
	player.setPosition(packet->getPosition());
	player.setPitch(packet->getPitch());
	player.setYaw(packet->getYaw());
	player.setOnGround(packet->isOnGround());

	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::SetPlayerRotation* packet)
{
	AcpPlayer& player = connection->getPlayer();
	player.setPitch(packet->getPitch());
	player.setYaw(packet->getYaw());
	player.setOnGround(packet->isOnGround());

	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::SetPlayerOnGround* packet)
{
	AcpPlayer& player = connection->getPlayer();
	player.setOnGround(packet->isOnGround());

	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::MoveVehicle* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::PaddleBoat* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::PickItem* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::PingRequest* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::PlaceRecipe* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::PlayerAbilities* packet)
{
	connection->getPlayer().setFlying(packet->getFlags() & 0x02);

	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::PlayerAction* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::PlayerCommand* packet)
{
	AcpPlayer& player = connection->getPlayer();

	if (packet->getAction() == 0)
		player.setSneaking(true);
	else if (packet->getAction() == 1)
		player.setSneaking(false);

	else if (packet->getAction() == 3)
		player.setSprinting(true);
	else if (packet->getAction() == 4)
		player.setSprinting(false);

	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::PlayerInput* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::Pong* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::ChangeRecipeBookSettings* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::SetSeenRecipe* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::RenameItem* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::ResourcePackResponse* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::SeenAdvancements* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::SelectTrade* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::SetBeaconEffect* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::SetHeldItem* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::ProgramCommandBlock* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::ProgramCommandBlockMinecart* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::SetCreativeModeSlot* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::ProgramJigsawBlock* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::ProgramStructureBlock* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::UpdateSign* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::SwingArm* packet)
{
	for (auto& [name, check] : connection->getPlayer().getCheckManager().getChecks())
	{
		if (auto* interactCheck = dynamic_cast<IInteractCheck*>(check.get()))
		{
			const HandleResult result = interactCheck->check(packet);
			if (result != HandleResult::FORWARD)
				return result;
		}
	}

	// SubLogger logger = connection->getLogger().getSubLogger("Raycasting");
	// logger.debug("");
	// logger.debug("dir: {}", connection->getPlayer().getDirection().toString("{:.06f}"));
	//
	// RaycastingOptions options;
	// options.distance = 6;
	// options.blocks = false;
	// auto results = connection->getPlayer().raycast(options);
	// for (const std::unique_ptr<RaycastResult>& result : results)
	// {
	// 	logger.debug("{}: {} -> {}, {} -> {}",
	// 				 EnumNames<RaycastResult::Type>::get(result->getType()),
	// 				 result->hitDistanceMin,
	// 				 result->hitDistanceMax,
	// 				 result->hitPositionMin.toString("{:.06f}"),
	// 				 result->hitPositionMax.toString("{:.06f}")
	// 	);
	// }
	//
	// // AnticheatProxy::get()->getAlertManager().send(Alert(connection->getGameProfile().username));

	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::TeleportToEntity* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::UseItemOn* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::UseItem* packet)
{
	return HandleResult::FORWARD;
}


acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::BundleDelimiter* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SpawnEntity* packet)
{
	const game::EntityType* type = connection->getProtocolVersion()->getEntityTypeMapping().get(packet->getType());
	if (!type)
	{
		connection->getLogger().error("Unknown entity type: {}", packet->toString());
		return HandleResult::FORWARD;
	}

	auto& entities = connection->getPlayer().getTrackedWorld().getEntities();
	entities[packet->getEntityId()] = std::make_unique<game::Entity>(
		packet->getEntityId(),
		packet->getEntityUuid(),
		type,
		packet->getPosition(),
		packet->getYaw(),
		packet->getPitch(),
		true
	);

	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SpawnExperienceOrb* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::EntityAnimation* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::AwardStatistics* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::AcknowledgeBlockChange* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetBlockDestroyStage* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::BlockEntityData* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::BlockAction* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::BlockUpdate* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::BossBar* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::ChangeDifficulty* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::ChunkBatchFinished* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::ChunkBatchStart* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::ChunkBiomes* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::ClearTitles* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::CommandSuggestionsResponse* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::Commands* packet)
{
	if (!connection->getPlayer().hasPermission(Permission::CMD))
		return HandleResult::FORWARD;

	std::vector<command::Node>& nodes = packet->getNodes();

	const int acpNodeIdx = static_cast<int>(nodes.size());
	command::Node& acpNode = nodes.emplace_back(command::Node(
		command::Node::LITERAL | command::Node::EXECUTABLE,
		{},
		std::nullopt,
		"acp",
		std::nullopt,
		nullptr,
		std::nullopt
	));

	const int acpArgsNodeIdx = static_cast<int>(nodes.size());
	nodes.emplace_back(command::Node(
		command::Node::ARGUMENT | command::Node::EXECUTABLE | command::Node::SUGGESTIONS,
		{},
		std::nullopt,
		"args",
		command::Parser::STRING.getId(connection->getProtocolVersion()),
		std::make_unique<command::StringProperties>(command::StringProperties::Type::GREEDY_PHRASE),
		Identifier("minecraft", "ask_server")
	));

	nodes[packet->getRootIndex()].getChildren().push_back(acpNodeIdx);
	acpNode.setChildren({ acpArgsNodeIdx });

	return HandleResult::REWRITE;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::CloseContainer* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetContainerContent* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetContainerProperty* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetContainerSlot* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::CookieRequest* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetCooldown* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::ChatSuggestions* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::PluginMessage* packet)
{
	return connection->getMessenger().onPluginMessage(NetworkSide::CLIENT, packet);
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::DamageEvent* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::DebugSample* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::DeleteMessage* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::Disconnect* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::DisguisedChatMessage* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::EntityEvent* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::Explosion* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::UnloadChunk* packet)
{
	game::World& world = connection->getPlayer().getTrackedWorld();
	world.getChunks().erase({ packet->getX(), packet->getZ() });

	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::GameEvent* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::OpenHorseScreen* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::HurtAnimation* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::InitializeWorldBorder* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::KeepAlive* packet)
{
	connection->getPingTracker().onSend(packet->getKeepAliveId());

	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::ChunkDataAndUpdateLight* packet)
{
	const game::ChunkKey key(packet->getX(), packet->getZ());
	game::Chunk chunk(key);

	// TODO load blocks
	// connection->getLogger().info("chunk: {}", packet->toString());

	game::World& world = connection->getPlayer().getTrackedWorld();
	world.getChunks().insert_or_assign(key, chunk);

	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::WorldEvent* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::Particle* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::UpdateLight* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::Login* packet)
{
	connection->setPlayer({ connection, packet->getEntityId(), connection->getGameProfile(), packet->getDimensionName() });

	const bool exempt = AnticheatProxy::get()->getPermissionManager().hasPermission(connection->getGameProfile().username, Permission::EXEMPT);
	connection->getPlayer().getCheckManager().setExempt(exempt);

	connection->getLogger().info("{}{} ({}) logged in with id {} in {}",
								 exempt ? "[EXEMPT] " : "",
								 connection->getGameProfile().username,
								 connection->getGameProfile().uuid.toString(),
								 packet->getEntityId(),
								 packet->getDimensionName().toString()
	);

	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::MapData* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::MerchantOffers* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::UpdateEntityPosition* packet)
{
	if (game::Entity* entity = connection->getPlayer().getTrackedWorld().getEntity(packet->getEntityId()))
	{
		entity->setPosition({
			packet->getDelta().x == 0 ? entity->getPosition().x : (std::round(entity->getPosition().x * 4096.0) + packet->getDelta().x) / 4096.0,
			packet->getDelta().y == 0 ? entity->getPosition().y : (std::round(entity->getPosition().y * 4096.0) + packet->getDelta().y) / 4096.0,
			packet->getDelta().z == 0 ? entity->getPosition().z : (std::round(entity->getPosition().z * 4096.0) + packet->getDelta().z) / 4096.0
		});
		entity->setOnGround(packet->isOnGround());
	}

	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::UpdateEntityPositionRotation* packet)
{
	if (game::Entity* entity = connection->getPlayer().getTrackedWorld().getEntity(packet->getEntityId()))
	{
		entity->setPosition({
			packet->getDelta().x == 0 ? entity->getPosition().x : (std::round(entity->getPosition().x * 4096.0) + packet->getDelta().x) / 4096.0,
			packet->getDelta().y == 0 ? entity->getPosition().y : (std::round(entity->getPosition().y * 4096.0) + packet->getDelta().y) / 4096.0,
			packet->getDelta().z == 0 ? entity->getPosition().z : (std::round(entity->getPosition().z * 4096.0) + packet->getDelta().z) / 4096.0
		});
		entity->setYaw(packet->getYaw());
		entity->setPitch(packet->getPitch());
		entity->setOnGround(packet->isOnGround());
	}

	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::UpdateEntityRotation* packet)
{
	if (game::Entity* entity = connection->getPlayer().getTrackedWorld().getEntity(packet->getEntityId()))
	{
		entity->setYaw(packet->getYaw());
		entity->setPitch(packet->getPitch());
		entity->setOnGround(packet->isOnGround());
	}

	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::MoveVehicle* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::OpenBook* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::OpenScreen* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::OpenSignEditor* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::Ping* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::PingResponse* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::PlaceGhostRecipe* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::PlayerAbilities* packet)
{
	AcpPlayer& player = connection->getPlayer();
	player.setFlying(packet->getFlags() & 0x02);
	player.setCanFly(packet->getFlags() & 0x04);
	player.setInstantBreak(packet->getFlags() & 0x08);

	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::PlayerChatMessage* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::EndCombat* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::EnterCombat* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::CombatDeath* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::PlayerInfoRemove* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::PlayerInfoUpdate* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::LookAt* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SynchronizePlayerPosition* packet)
{
	pendingTeleports[packet->getTeleportId()] = *packet;

	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::UpdateRecipeBook* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::RemoveEntities* packet)
{
	auto& entities = connection->getPlayer().getTrackedWorld().getEntities();

	for (int id : packet->getIds())
		entities.erase(id);

	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::RemoveEntityEffect* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::ResetScore* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::RemoveResourcePack* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::AddResourcePack* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::Respawn* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetHeadRotation* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::UpdateSectionBlocks* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SelectAdvancementsTab* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::ServerData* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetActionBarText* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetBorderCenter* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetBorderLerpSize* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetBorderSize* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetBorderWarningDelay* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetBorderWarningDistance* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetCamera* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetHeldItem* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetCenterChunk* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetRenderDistance* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetDefaultSpawnPosition* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::DisplayObjective* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetEntityMetadata* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::LinkEntities* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetEntityVelocity* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetEquipment* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetExperience* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetHealth* packet)
{
	AcpPlayer& player = connection->getPlayer();
	player.setHealth(packet->getHealth());
	player.setFood(packet->getFood());

	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::UpdateObjectives* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetPassengers* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::UpdateTeams* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::UpdateScore* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetSimulationDistance* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetSubtitleText* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::UpdateTime* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetTitleText* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetTitleAnimationTimes* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::EntitySoundEffect* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SoundEffect* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::StartConfiguration* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::StopSound* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::StoreCookie* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SystemChatMessage* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetTabListHeaderAndFooter* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::TagQueryResponse* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::PickupItem* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::TeleportEntity* packet)
{
	if (game::Entity* entity = connection->getPlayer().getTrackedWorld().getEntity(packet->getEntityId()))
	{
		entity->setPosition(packet->getPosition());
		entity->setYaw(packet->getYaw());
		entity->setPitch(packet->getPitch());
	}

	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::SetTickingState* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::StepTick* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::Transfer* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::UpdateAdvancements* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::UpdateAttributes* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::EntityEffect* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::UpdateRecipes* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::UpdateTags* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::ProjectilePower* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::CustomReportDetails* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::ServerLinks* packet)
{
	return HandleResult::FORWARD;
}


void acp::PlayHandler::sendPluginMessage(NetworkSide to, const Identifier& channel, const ByteBuf& data)
{
	if (to == NetworkSide::DEST) // server
	{
		auto packet = std::make_unique<packet::play::c2s::PluginMessage>();
		packet->setChannel(channel);
		packet->setData(data);

		connection->sendPacket(to, std::move(packet));
	}
	else // client
	{
		auto packet = std::make_unique<packet::play::s2c::PluginMessage>();
		packet->setChannel(channel);
		packet->setData(data);

		connection->sendPacket(to, std::move(packet));
	}
}

void acp::PlayHandler::disconnect(const std::unique_ptr<text::Component>& reason)
{
	auto packet = std::make_unique<packet::play::s2c::Disconnect>();
	packet->setReason(reason->copy());

	connection->sendPacket(NetworkSide::CLIENT, std::move(packet));
}
