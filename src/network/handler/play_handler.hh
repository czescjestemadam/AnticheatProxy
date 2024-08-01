#pragma once
#include "i_network_handler.hh"
#include "network/protocol/packet/play/c2s/acknowledge_configuration.hh"
#include "network/protocol/packet/play/c2s/acknowledge_message.hh"
#include "network/protocol/packet/play/c2s/change_container_slot_state.hh"
#include "network/protocol/packet/play/c2s/change_difficulty.hh"
#include "network/protocol/packet/play/c2s/change_recipe_book_settings.hh"
#include "network/protocol/packet/play/c2s/chat_command.hh"
#include "network/protocol/packet/play/c2s/chat_message.hh"
#include "network/protocol/packet/play/c2s/chunk_batch_received.hh"
#include "network/protocol/packet/play/c2s/click_container.hh"
#include "network/protocol/packet/play/c2s/click_container_button.hh"
#include "network/protocol/packet/play/c2s/client_information.hh"
#include "network/protocol/packet/play/c2s/client_status.hh"
#include "network/protocol/packet/play/c2s/close_container.hh"
#include "network/protocol/packet/play/c2s/command_suggestions_request.hh"
#include "network/protocol/packet/play/c2s/confirm_teleportation.hh"
#include "network/protocol/packet/play/c2s/cookie_response.hh"
#include "network/protocol/packet/play/c2s/debug_sample_subscription.hh"
#include "network/protocol/packet/play/c2s/edit_book.hh"
#include "network/protocol/packet/play/c2s/interact.hh"
#include "network/protocol/packet/play/c2s/jigsaw_generate.hh"
#include "network/protocol/packet/play/c2s/keep_alive.hh"
#include "network/protocol/packet/play/c2s/lock_difficulty.hh"
#include "network/protocol/packet/play/c2s/move_vehicle.hh"
#include "network/protocol/packet/play/c2s/paddle_boat.hh"
#include "network/protocol/packet/play/c2s/pick_item.hh"
#include "network/protocol/packet/play/c2s/ping_request.hh"
#include "network/protocol/packet/play/c2s/place_recipe.hh"
#include "network/protocol/packet/play/c2s/player_abilities.hh"
#include "network/protocol/packet/play/c2s/player_action.hh"
#include "network/protocol/packet/play/c2s/player_command.hh"
#include "network/protocol/packet/play/c2s/player_input.hh"
#include "network/protocol/packet/play/c2s/player_session.hh"
#include "network/protocol/packet/play/c2s/plugin_message.hh"
#include "network/protocol/packet/play/c2s/pong.hh"
#include "network/protocol/packet/play/c2s/program_command_block.hh"
#include "network/protocol/packet/play/c2s/program_command_block_minecart.hh"
#include "network/protocol/packet/play/c2s/program_jigsaw_block.hh"
#include "network/protocol/packet/play/c2s/program_structure_block.hh"
#include "network/protocol/packet/play/c2s/query_block_entity_tag.hh"
#include "network/protocol/packet/play/c2s/query_entity_tag.hh"
#include "network/protocol/packet/play/c2s/rename_item.hh"
#include "network/protocol/packet/play/c2s/resource_pack_response.hh"
#include "network/protocol/packet/play/c2s/seen_advancements.hh"
#include "network/protocol/packet/play/c2s/select_trade.hh"
#include "network/protocol/packet/play/c2s/set_beacon_effect.hh"
#include "network/protocol/packet/play/c2s/set_creative_mode_slot.hh"
#include "network/protocol/packet/play/c2s/set_held_item.hh"
#include "network/protocol/packet/play/c2s/set_player_on_ground.hh"
#include "network/protocol/packet/play/c2s/set_player_position.hh"
#include "network/protocol/packet/play/c2s/set_player_position_rotation.hh"
#include "network/protocol/packet/play/c2s/set_player_rotation.hh"
#include "network/protocol/packet/play/c2s/set_seen_recipe.hh"
#include "network/protocol/packet/play/c2s/signed_chat_command.hh"
#include "network/protocol/packet/play/c2s/swing_arm.hh"
#include "network/protocol/packet/play/c2s/teleport_to_entity.hh"
#include "network/protocol/packet/play/c2s/update_sign.hh"
#include "network/protocol/packet/play/c2s/use_item.hh"
#include "network/protocol/packet/play/c2s/use_item_on.hh"
#include "network/protocol/packet/play/s2c/acknowledge_block_change.hh"
#include "network/protocol/packet/play/s2c/add_resource_pack.hh"
#include "network/protocol/packet/play/s2c/award_statistics.hh"
#include "network/protocol/packet/play/s2c/block_action.hh"
#include "network/protocol/packet/play/s2c/block_entity_data.hh"
#include "network/protocol/packet/play/s2c/block_update.hh"
#include "network/protocol/packet/play/s2c/boss_bar.hh"
#include "network/protocol/packet/play/s2c/bundle_delimiter.hh"
#include "network/protocol/packet/play/s2c/change_difficulty.hh"
#include "network/protocol/packet/play/s2c/chat_suggestions.hh"
#include "network/protocol/packet/play/s2c/chunk_batch_finished.hh"
#include "network/protocol/packet/play/s2c/chunk_batch_start.hh"
#include "network/protocol/packet/play/s2c/chunk_biomes.hh"
#include "network/protocol/packet/play/s2c/chunk_data_and_update_light.hh"
#include "network/protocol/packet/play/s2c/clear_titles.hh"
#include "network/protocol/packet/play/s2c/close_container.hh"
#include "network/protocol/packet/play/s2c/combat_death.hh"
#include "network/protocol/packet/play/s2c/commands.hh"
#include "network/protocol/packet/play/s2c/command_suggestions_response.hh"
#include "network/protocol/packet/play/s2c/cookie_request.hh"
#include "network/protocol/packet/play/s2c/custom_report_details.hh"
#include "network/protocol/packet/play/s2c/damage_event.hh"
#include "network/protocol/packet/play/s2c/debug_sample.hh"
#include "network/protocol/packet/play/s2c/delete_message.hh"
#include "network/protocol/packet/play/s2c/disconnect.hh"
#include "network/protocol/packet/play/s2c/disguised_chat_message.hh"
#include "network/protocol/packet/play/s2c/display_objective.hh"
#include "network/protocol/packet/play/s2c/end_combat.hh"
#include "network/protocol/packet/play/s2c/enter_combat.hh"
#include "network/protocol/packet/play/s2c/entity_animation.hh"
#include "network/protocol/packet/play/s2c/entity_effect.hh"
#include "network/protocol/packet/play/s2c/entity_event.hh"
#include "network/protocol/packet/play/s2c/entity_sound_effect.hh"
#include "network/protocol/packet/play/s2c/explosion.hh"
#include "network/protocol/packet/play/s2c/game_event.hh"
#include "network/protocol/packet/play/s2c/hurt_animation.hh"
#include "network/protocol/packet/play/s2c/initialize_world_border.hh"
#include "network/protocol/packet/play/s2c/keep_alive.hh"
#include "network/protocol/packet/play/s2c/link_entities.hh"
#include "network/protocol/packet/play/s2c/login.hh"
#include "network/protocol/packet/play/s2c/look_at.hh"
#include "network/protocol/packet/play/s2c/map_data.hh"
#include "network/protocol/packet/play/s2c/merchant_offers.hh"
#include "network/protocol/packet/play/s2c/move_vehicle.hh"
#include "network/protocol/packet/play/s2c/open_book.hh"
#include "network/protocol/packet/play/s2c/open_horse_screen.hh"
#include "network/protocol/packet/play/s2c/open_screen.hh"
#include "network/protocol/packet/play/s2c/open_sign_editor.hh"
#include "network/protocol/packet/play/s2c/particle.hh"
#include "network/protocol/packet/play/s2c/pickup_item.hh"
#include "network/protocol/packet/play/s2c/ping.hh"
#include "network/protocol/packet/play/s2c/ping_response.hh"
#include "network/protocol/packet/play/s2c/place_ghost_recipe.hh"
#include "network/protocol/packet/play/s2c/player_abilities.hh"
#include "network/protocol/packet/play/s2c/player_chat_message.hh"
#include "network/protocol/packet/play/s2c/player_info_remove.hh"
#include "network/protocol/packet/play/s2c/player_info_update.hh"
#include "network/protocol/packet/play/s2c/plugin_message.hh"
#include "network/protocol/packet/play/s2c/projectile_power.hh"
#include "network/protocol/packet/play/s2c/remove_entities.hh"
#include "network/protocol/packet/play/s2c/remove_entity_effect.hh"
#include "network/protocol/packet/play/s2c/remove_resource_pack.hh"
#include "network/protocol/packet/play/s2c/reset_score.hh"
#include "network/protocol/packet/play/s2c/respawn.hh"
#include "network/protocol/packet/play/s2c/select_advancements_tab.hh"
#include "network/protocol/packet/play/s2c/server_data.hh"
#include "network/protocol/packet/play/s2c/server_links.hh"
#include "network/protocol/packet/play/s2c/set_action_bar_text.hh"
#include "network/protocol/packet/play/s2c/set_block_destroy_stage.hh"
#include "network/protocol/packet/play/s2c/set_border_center.hh"
#include "network/protocol/packet/play/s2c/set_border_lerp_size.hh"
#include "network/protocol/packet/play/s2c/set_border_size.hh"
#include "network/protocol/packet/play/s2c/set_border_warning_delay.hh"
#include "network/protocol/packet/play/s2c/set_border_warning_distance.hh"
#include "network/protocol/packet/play/s2c/set_camera.hh"
#include "network/protocol/packet/play/s2c/set_center_chunk.hh"
#include "network/protocol/packet/play/s2c/set_container_content.hh"
#include "network/protocol/packet/play/s2c/set_container_property.hh"
#include "network/protocol/packet/play/s2c/set_container_slot.hh"
#include "network/protocol/packet/play/s2c/set_cooldown.hh"
#include "network/protocol/packet/play/s2c/set_default_spawn_position.hh"
#include "network/protocol/packet/play/s2c/set_entity_metadata.hh"
#include "network/protocol/packet/play/s2c/set_entity_velocity.hh"
#include "network/protocol/packet/play/s2c/set_equipment.hh"
#include "network/protocol/packet/play/s2c/set_experience.hh"
#include "network/protocol/packet/play/s2c/set_head_rotation.hh"
#include "network/protocol/packet/play/s2c/set_health.hh"
#include "network/protocol/packet/play/s2c/set_held_item.hh"
#include "network/protocol/packet/play/s2c/set_passengers.hh"
#include "network/protocol/packet/play/s2c/set_render_distance.hh"
#include "network/protocol/packet/play/s2c/set_simulation_distance.hh"
#include "network/protocol/packet/play/s2c/set_subtitle_text.hh"
#include "network/protocol/packet/play/s2c/set_tab_list_header_and_footer.hh"
#include "network/protocol/packet/play/s2c/set_ticking_state.hh"
#include "network/protocol/packet/play/s2c/set_title_animation_times.hh"
#include "network/protocol/packet/play/s2c/set_title_text.hh"
#include "network/protocol/packet/play/s2c/sound_effect.hh"
#include "network/protocol/packet/play/s2c/spawn_entity.hh"
#include "network/protocol/packet/play/s2c/spawn_experience_orb.hh"
#include "network/protocol/packet/play/s2c/start_configuration.hh"
#include "network/protocol/packet/play/s2c/step_tick.hh"
#include "network/protocol/packet/play/s2c/stop_sound.hh"
#include "network/protocol/packet/play/s2c/store_cookie.hh"
#include "network/protocol/packet/play/s2c/synchronize_player_position.hh"
#include "network/protocol/packet/play/s2c/system_chat_message.hh"
#include "network/protocol/packet/play/s2c/tag_query_response.hh"
#include "network/protocol/packet/play/s2c/teleport_entity.hh"
#include "network/protocol/packet/play/s2c/transfer.hh"
#include "network/protocol/packet/play/s2c/unload_chunk.hh"
#include "network/protocol/packet/play/s2c/update_advancements.hh"
#include "network/protocol/packet/play/s2c/update_attributes.hh"
#include "network/protocol/packet/play/s2c/update_entity_position.hh"
#include "network/protocol/packet/play/s2c/update_entity_position_rotation.hh"
#include "network/protocol/packet/play/s2c/update_entity_rotation.hh"
#include "network/protocol/packet/play/s2c/update_light.hh"
#include "network/protocol/packet/play/s2c/update_objectives.hh"
#include "network/protocol/packet/play/s2c/update_recipes.hh"
#include "network/protocol/packet/play/s2c/update_recipe_book.hh"
#include "network/protocol/packet/play/s2c/update_score.hh"
#include "network/protocol/packet/play/s2c/update_section_blocks.hh"
#include "network/protocol/packet/play/s2c/update_tags.hh"
#include "network/protocol/packet/play/s2c/update_teams.hh"
#include "network/protocol/packet/play/s2c/update_time.hh"
#include "network/protocol/packet/play/s2c/world_event.hh"

namespace acp
{
	class PlayHandler : public INetworkHandler
	{
	public:
		using INetworkHandler::INetworkHandler;

		HandleResult handle(packet::play::c2s::ConfirmTeleportation* packet);
		HandleResult handle(packet::play::c2s::QueryBlockEntityTag* packet);
		HandleResult handle(packet::play::c2s::ChangeDifficulty* packet);
		HandleResult handle(packet::play::c2s::AcknowledgeMessage* packet);
		HandleResult handle(packet::play::c2s::ChatCommand* packet);
		HandleResult handle(packet::play::c2s::SignedChatCommand* packet);
		HandleResult handle(packet::play::c2s::ChatMessage* packet);
		HandleResult handle(packet::play::c2s::PlayerSession* packet);
		HandleResult handle(packet::play::c2s::ChunkBatchReceived* packet);
		HandleResult handle(packet::play::c2s::ClientStatus* packet);
		HandleResult handle(packet::play::c2s::ClientInformation* packet);
		HandleResult handle(packet::play::c2s::CommandSuggestionsRequest* packet);
		HandleResult handle(packet::play::c2s::AcknowledgeConfiguration* packet);
		HandleResult handle(packet::play::c2s::ClickContainerButton* packet);
		HandleResult handle(packet::play::c2s::ClickContainer* packet);
		HandleResult handle(packet::play::c2s::CloseContainer* packet);
		HandleResult handle(packet::play::c2s::ChangeContainerSlotState* packet);
		HandleResult handle(packet::play::c2s::CookieResponse* packet);
		HandleResult handle(packet::play::c2s::PluginMessage* packet);
		HandleResult handle(packet::play::c2s::DebugSampleSubscription* packet);
		HandleResult handle(packet::play::c2s::EditBook* packet);
		HandleResult handle(packet::play::c2s::QueryEntityTag* packet);
		HandleResult handle(packet::play::c2s::Interact* packet);
		HandleResult handle(packet::play::c2s::JigsawGenerate* packet);
		HandleResult handle(packet::play::c2s::KeepAlive* packet);
		HandleResult handle(packet::play::c2s::LockDifficulty* packet);
		HandleResult handle(packet::play::c2s::SetPlayerPosition* packet);
		HandleResult handle(packet::play::c2s::SetPlayerPositionRotation* packet);
		HandleResult handle(packet::play::c2s::SetPlayerRotation* packet);
		HandleResult handle(packet::play::c2s::SetPlayerOnGround* packet);
		HandleResult handle(packet::play::c2s::MoveVehicle* packet);
		HandleResult handle(packet::play::c2s::PaddleBoat* packet);
		HandleResult handle(packet::play::c2s::PickItem* packet);
		HandleResult handle(packet::play::c2s::PingRequest* packet);
		HandleResult handle(packet::play::c2s::PlaceRecipe* packet);
		HandleResult handle(packet::play::c2s::PlayerAbilities* packet);
		HandleResult handle(packet::play::c2s::PlayerAction* packet);
		HandleResult handle(packet::play::c2s::PlayerCommand* packet);
		HandleResult handle(packet::play::c2s::PlayerInput* packet);
		HandleResult handle(packet::play::c2s::Pong* packet);
		HandleResult handle(packet::play::c2s::ChangeRecipeBookSettings* packet);
		HandleResult handle(packet::play::c2s::SetSeenRecipe* packet);
		HandleResult handle(packet::play::c2s::RenameItem* packet);
		HandleResult handle(packet::play::c2s::ResourcePackResponse* packet);
		HandleResult handle(packet::play::c2s::SeenAdvancements* packet);
		HandleResult handle(packet::play::c2s::SelectTrade* packet);
		HandleResult handle(packet::play::c2s::SetBeaconEffect* packet);
		HandleResult handle(packet::play::c2s::SetHeldItem* packet);
		HandleResult handle(packet::play::c2s::ProgramCommandBlock* packet);
		HandleResult handle(packet::play::c2s::ProgramCommandBlockMinecart* packet);
		HandleResult handle(packet::play::c2s::SetCreativeModeSlot* packet);
		HandleResult handle(packet::play::c2s::ProgramJigsawBlock* packet);
		HandleResult handle(packet::play::c2s::ProgramStructureBlock* packet);
		HandleResult handle(packet::play::c2s::UpdateSign* packet);
		HandleResult handle(packet::play::c2s::SwingArm* packet);
		HandleResult handle(packet::play::c2s::TeleportToEntity* packet);
		HandleResult handle(packet::play::c2s::UseItemOn* packet);
		HandleResult handle(packet::play::c2s::UseItem* packet);

		HandleResult handle(packet::play::s2c::BundleDelimiter* packet);
		HandleResult handle(packet::play::s2c::SpawnEntity* packet);
		HandleResult handle(packet::play::s2c::SpawnExperienceOrb* packet);
		HandleResult handle(packet::play::s2c::EntityAnimation* packet);
		HandleResult handle(packet::play::s2c::AwardStatistics* packet);
		HandleResult handle(packet::play::s2c::AcknowledgeBlockChange* packet);
		HandleResult handle(packet::play::s2c::SetBlockDestroyStage* packet);
		HandleResult handle(packet::play::s2c::BlockEntityData* packet);
		HandleResult handle(packet::play::s2c::BlockAction* packet);
		HandleResult handle(packet::play::s2c::BlockUpdate* packet);
		HandleResult handle(packet::play::s2c::BossBar* packet);
		HandleResult handle(packet::play::s2c::ChangeDifficulty* packet);
		HandleResult handle(packet::play::s2c::ChunkBatchFinished* packet);
		HandleResult handle(packet::play::s2c::ChunkBatchStart* packet);
		HandleResult handle(packet::play::s2c::ChunkBiomes* packet);
		HandleResult handle(packet::play::s2c::ClearTitles* packet);
		HandleResult handle(packet::play::s2c::CommandSuggestionsResponse* packet);
		HandleResult handle(packet::play::s2c::Commands* packet);
		HandleResult handle(packet::play::s2c::CloseContainer* packet);
		HandleResult handle(packet::play::s2c::SetContainerContent* packet);
		HandleResult handle(packet::play::s2c::SetContainerProperty* packet);
		HandleResult handle(packet::play::s2c::SetContainerSlot* packet);
		HandleResult handle(packet::play::s2c::CookieRequest* packet);
		HandleResult handle(packet::play::s2c::SetCooldown* packet);
		HandleResult handle(packet::play::s2c::ChatSuggestions* packet);
		HandleResult handle(packet::play::s2c::PluginMessage* packet);
		HandleResult handle(packet::play::s2c::DamageEvent* packet);
		HandleResult handle(packet::play::s2c::DebugSample* packet);
		HandleResult handle(packet::play::s2c::DeleteMessage* packet);
		HandleResult handle(packet::play::s2c::Disconnect* packet);
		HandleResult handle(packet::play::s2c::DisguisedChatMessage* packet);
		HandleResult handle(packet::play::s2c::EntityEvent* packet);
		HandleResult handle(packet::play::s2c::Explosion* packet);
		HandleResult handle(packet::play::s2c::UnloadChunk* packet);
		HandleResult handle(packet::play::s2c::GameEvent* packet);
		HandleResult handle(packet::play::s2c::OpenHorseScreen* packet);
		HandleResult handle(packet::play::s2c::HurtAnimation* packet);
		HandleResult handle(packet::play::s2c::InitializeWorldBorder* packet);
		HandleResult handle(packet::play::s2c::KeepAlive* packet);
		HandleResult handle(packet::play::s2c::ChunkDataAndUpdateLight* packet);
		HandleResult handle(packet::play::s2c::WorldEvent* packet);
		HandleResult handle(packet::play::s2c::Particle* packet);
		HandleResult handle(packet::play::s2c::UpdateLight* packet);
		HandleResult handle(packet::play::s2c::Login* packet);
		HandleResult handle(packet::play::s2c::MapData* packet);
		HandleResult handle(packet::play::s2c::MerchantOffers* packet);
		HandleResult handle(packet::play::s2c::UpdateEntityPosition* packet);
		HandleResult handle(packet::play::s2c::UpdateEntityPositionRotation* packet);
		HandleResult handle(packet::play::s2c::UpdateEntityRotation* packet);
		HandleResult handle(packet::play::s2c::MoveVehicle* packet);
		HandleResult handle(packet::play::s2c::OpenBook* packet);
		HandleResult handle(packet::play::s2c::OpenScreen* packet);
		HandleResult handle(packet::play::s2c::OpenSignEditor* packet);
		HandleResult handle(packet::play::s2c::Ping* packet);
		HandleResult handle(packet::play::s2c::PingResponse* packet);
		HandleResult handle(packet::play::s2c::PlaceGhostRecipe* packet);
		HandleResult handle(packet::play::s2c::PlayerAbilities* packet);
		HandleResult handle(packet::play::s2c::PlayerChatMessage* packet);
		HandleResult handle(packet::play::s2c::EndCombat* packet);
		HandleResult handle(packet::play::s2c::EnterCombat* packet);
		HandleResult handle(packet::play::s2c::CombatDeath* packet);
		HandleResult handle(packet::play::s2c::PlayerInfoRemove* packet);
		HandleResult handle(packet::play::s2c::PlayerInfoUpdate* packet);
		HandleResult handle(packet::play::s2c::LookAt* packet);
		HandleResult handle(packet::play::s2c::SynchronizePlayerPosition* packet);
		HandleResult handle(packet::play::s2c::UpdateRecipeBook* packet);
		HandleResult handle(packet::play::s2c::RemoveEntities* packet);
		HandleResult handle(packet::play::s2c::RemoveEntityEffect* packet);
		HandleResult handle(packet::play::s2c::ResetScore* packet);
		HandleResult handle(packet::play::s2c::RemoveResourcePack* packet);
		HandleResult handle(packet::play::s2c::AddResourcePack* packet);
		HandleResult handle(packet::play::s2c::Respawn* packet);
		HandleResult handle(packet::play::s2c::SetHeadRotation* packet);
		HandleResult handle(packet::play::s2c::UpdateSectionBlocks* packet);
		HandleResult handle(packet::play::s2c::SelectAdvancementsTab* packet);
		HandleResult handle(packet::play::s2c::ServerData* packet);
		HandleResult handle(packet::play::s2c::SetActionBarText* packet);
		HandleResult handle(packet::play::s2c::SetBorderCenter* packet);
		HandleResult handle(packet::play::s2c::SetBorderLerpSize* packet);
		HandleResult handle(packet::play::s2c::SetBorderSize* packet);
		HandleResult handle(packet::play::s2c::SetBorderWarningDelay* packet);
		HandleResult handle(packet::play::s2c::SetBorderWarningDistance* packet);
		HandleResult handle(packet::play::s2c::SetCamera* packet);
		HandleResult handle(packet::play::s2c::SetHeldItem* packet);
		HandleResult handle(packet::play::s2c::SetCenterChunk* packet);
		HandleResult handle(packet::play::s2c::SetRenderDistance* packet);
		HandleResult handle(packet::play::s2c::SetDefaultSpawnPosition* packet);
		HandleResult handle(packet::play::s2c::DisplayObjective* packet);
		HandleResult handle(packet::play::s2c::SetEntityMetadata* packet);
		HandleResult handle(packet::play::s2c::LinkEntities* packet);
		HandleResult handle(packet::play::s2c::SetEntityVelocity* packet);
		HandleResult handle(packet::play::s2c::SetEquipment* packet);
		HandleResult handle(packet::play::s2c::SetExperience* packet);
		HandleResult handle(packet::play::s2c::SetHealth* packet);
		HandleResult handle(packet::play::s2c::UpdateObjectives* packet);
		HandleResult handle(packet::play::s2c::SetPassengers* packet);
		HandleResult handle(packet::play::s2c::UpdateTeams* packet);
		HandleResult handle(packet::play::s2c::UpdateScore* packet);
		HandleResult handle(packet::play::s2c::SetSimulationDistance* packet);
		HandleResult handle(packet::play::s2c::SetSubtitleText* packet);
		HandleResult handle(packet::play::s2c::UpdateTime* packet);
		HandleResult handle(packet::play::s2c::SetTitleText* packet);
		HandleResult handle(packet::play::s2c::SetTitleAnimationTimes* packet);
		HandleResult handle(packet::play::s2c::EntitySoundEffect* packet);
		HandleResult handle(packet::play::s2c::SoundEffect* packet);
		HandleResult handle(packet::play::s2c::StartConfiguration* packet);
		HandleResult handle(packet::play::s2c::StopSound* packet);
		HandleResult handle(packet::play::s2c::StoreCookie* packet);
		HandleResult handle(packet::play::s2c::SystemChatMessage* packet);
		HandleResult handle(packet::play::s2c::SetTabListHeaderAndFooter* packet);
		HandleResult handle(packet::play::s2c::TagQueryResponse* packet);
		HandleResult handle(packet::play::s2c::PickupItem* packet);
		HandleResult handle(packet::play::s2c::TeleportEntity* packet);
		HandleResult handle(packet::play::s2c::SetTickingState* packet);
		HandleResult handle(packet::play::s2c::StepTick* packet);
		HandleResult handle(packet::play::s2c::Transfer* packet);
		HandleResult handle(packet::play::s2c::UpdateAdvancements* packet);
		HandleResult handle(packet::play::s2c::UpdateAttributes* packet);
		HandleResult handle(packet::play::s2c::EntityEffect* packet);
		HandleResult handle(packet::play::s2c::UpdateRecipes* packet);
		HandleResult handle(packet::play::s2c::UpdateTags* packet);
		HandleResult handle(packet::play::s2c::ProjectilePower* packet);
		HandleResult handle(packet::play::s2c::CustomReportDetails* packet);
		HandleResult handle(packet::play::s2c::ServerLinks* packet);

		void disconnect(const std::unique_ptr<text::Component>& reason) override;
	};
}
