#include "play_handler.hh"

#include "network/connection.hh"

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::ConfirmTeleportation* packet)
{
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
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::SignedChatCommand* packet)
{
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
	return HandleResult::FORWARD;
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
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::LockDifficulty* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::SetPlayerPosition* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::SetPlayerPositionRotation* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::SetPlayerRotation* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::SetPlayerOnGround* packet)
{
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
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::PlayerAction* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::c2s::PlayerCommand* packet)
{
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
	return HandleResult::FORWARD;
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
	return HandleResult::FORWARD;
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
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::ChunkDataAndUpdateLight* packet)
{
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
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::UpdateEntityPositionRotation* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::UpdateEntityRotation* packet)
{
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
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::UpdateRecipeBook* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::PlayHandler::handle(packet::play::s2c::RemoveEntities* packet)
{
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
