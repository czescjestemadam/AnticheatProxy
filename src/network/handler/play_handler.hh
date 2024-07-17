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

		bool handle(packet::play::c2s::ConfirmTeleportation* packet);
		bool handle(packet::play::c2s::QueryBlockEntityTag* packet);
		bool handle(packet::play::c2s::ChangeDifficulty* packet);
		bool handle(packet::play::c2s::AcknowledgeMessage* packet);
		bool handle(packet::play::c2s::ChatCommand* packet);
		bool handle(packet::play::c2s::SignedChatCommand* packet);
		bool handle(packet::play::c2s::ChatMessage* packet);
		bool handle(packet::play::c2s::PlayerSession* packet);
		bool handle(packet::play::c2s::ChunkBatchReceived* packet);
		bool handle(packet::play::c2s::ClientStatus* packet);
		bool handle(packet::play::c2s::ClientInformation* packet);
		bool handle(packet::play::c2s::CommandSuggestionsRequest* packet);
		bool handle(packet::play::c2s::AcknowledgeConfiguration* packet);
		bool handle(packet::play::c2s::ClickContainerButton* packet);
		bool handle(packet::play::c2s::ClickContainer* packet);
		bool handle(packet::play::c2s::CloseContainer* packet);
		bool handle(packet::play::c2s::ChangeContainerSlotState* packet);
		bool handle(packet::play::c2s::CookieResponse* packet);
		bool handle(packet::play::c2s::PluginMessage* packet);
		bool handle(packet::play::c2s::DebugSampleSubscription* packet);
		bool handle(packet::play::c2s::EditBook* packet);
		bool handle(packet::play::c2s::QueryEntityTag* packet);
		bool handle(packet::play::c2s::Interact* packet);
		bool handle(packet::play::c2s::JigsawGenerate* packet);
		bool handle(packet::play::c2s::KeepAlive* packet);
		bool handle(packet::play::c2s::LockDifficulty* packet);
		bool handle(packet::play::c2s::SetPlayerPosition* packet);
		bool handle(packet::play::c2s::SetPlayerPositionRotation* packet);
		bool handle(packet::play::c2s::SetPlayerRotation* packet);
		bool handle(packet::play::c2s::SetPlayerOnGround* packet);
		bool handle(packet::play::c2s::MoveVehicle* packet);
		bool handle(packet::play::c2s::PaddleBoat* packet);
		bool handle(packet::play::c2s::PickItem* packet);
		bool handle(packet::play::c2s::PingRequest* packet);
		bool handle(packet::play::c2s::PlaceRecipe* packet);
		bool handle(packet::play::c2s::PlayerAbilities* packet);
		bool handle(packet::play::c2s::PlayerAction* packet);
		bool handle(packet::play::c2s::PlayerCommand* packet);
		bool handle(packet::play::c2s::PlayerInput* packet);
		bool handle(packet::play::c2s::Pong* packet);
		bool handle(packet::play::c2s::ChangeRecipeBookSettings* packet);
		bool handle(packet::play::c2s::SetSeenRecipe* packet);
		bool handle(packet::play::c2s::RenameItem* packet);
		bool handle(packet::play::c2s::ResourcePackResponse* packet);
		bool handle(packet::play::c2s::SeenAdvancements* packet);
		bool handle(packet::play::c2s::SelectTrade* packet);
		bool handle(packet::play::c2s::SetBeaconEffect* packet);
		bool handle(packet::play::c2s::SetHeldItem* packet);
		bool handle(packet::play::c2s::ProgramCommandBlock* packet);
		bool handle(packet::play::c2s::ProgramCommandBlockMinecart* packet);
		bool handle(packet::play::c2s::SetCreativeModeSlot* packet);
		bool handle(packet::play::c2s::ProgramJigsawBlock* packet);
		bool handle(packet::play::c2s::ProgramStructureBlock* packet);
		bool handle(packet::play::c2s::UpdateSign* packet);
		bool handle(packet::play::c2s::SwingArm* packet);
		bool handle(packet::play::c2s::TeleportToEntity* packet);
		bool handle(packet::play::c2s::UseItemOn* packet);
		bool handle(packet::play::c2s::UseItem* packet);

		bool handle(packet::play::s2c::BundleDelimiter* packet);
		bool handle(packet::play::s2c::SpawnEntity* packet);
		bool handle(packet::play::s2c::SpawnExperienceOrb* packet);
		bool handle(packet::play::s2c::EntityAnimation* packet);
		bool handle(packet::play::s2c::AwardStatistics* packet);
		bool handle(packet::play::s2c::AcknowledgeBlockChange* packet);
		bool handle(packet::play::s2c::SetBlockDestroyStage* packet);
		bool handle(packet::play::s2c::BlockEntityData* packet);
		bool handle(packet::play::s2c::BlockAction* packet);
		bool handle(packet::play::s2c::BlockUpdate* packet);
		bool handle(packet::play::s2c::BossBar* packet);
		bool handle(packet::play::s2c::ChangeDifficulty* packet);
		bool handle(packet::play::s2c::ChunkBatchFinished* packet);
		bool handle(packet::play::s2c::ChunkBatchStart* packet);
		bool handle(packet::play::s2c::ChunkBiomes* packet);
		bool handle(packet::play::s2c::ClearTitles* packet);
		bool handle(packet::play::s2c::CommandSuggestionsResponse* packet);
		bool handle(packet::play::s2c::Commands* packet);
		bool handle(packet::play::s2c::CloseContainer* packet);
		bool handle(packet::play::s2c::SetContainerContent* packet);
		bool handle(packet::play::s2c::SetContainerProperty* packet);
		bool handle(packet::play::s2c::SetContainerSlot* packet);
		bool handle(packet::play::s2c::CookieRequest* packet);
		bool handle(packet::play::s2c::SetCooldown* packet);
		bool handle(packet::play::s2c::ChatSuggestions* packet);
		bool handle(packet::play::s2c::PluginMessage* packet);
		bool handle(packet::play::s2c::DamageEvent* packet);
		bool handle(packet::play::s2c::DebugSample* packet);
		bool handle(packet::play::s2c::DeleteMessage* packet);
		bool handle(packet::play::s2c::Disconnect* packet);
		bool handle(packet::play::s2c::DisguisedChatMessage* packet);
		bool handle(packet::play::s2c::EntityEvent* packet);
		bool handle(packet::play::s2c::Explosion* packet);
		bool handle(packet::play::s2c::UnloadChunk* packet);
		bool handle(packet::play::s2c::GameEvent* packet);
		bool handle(packet::play::s2c::OpenHorseScreen* packet);
		bool handle(packet::play::s2c::HurtAnimation* packet);
		bool handle(packet::play::s2c::InitializeWorldBorder* packet);
		bool handle(packet::play::s2c::KeepAlive* packet);
		bool handle(packet::play::s2c::ChunkDataAndUpdateLight* packet);
		bool handle(packet::play::s2c::WorldEvent* packet);
		bool handle(packet::play::s2c::Particle* packet);
		bool handle(packet::play::s2c::UpdateLight* packet);
		bool handle(packet::play::s2c::Login* packet);
		bool handle(packet::play::s2c::MapData* packet);
		bool handle(packet::play::s2c::MerchantOffers* packet);
		bool handle(packet::play::s2c::UpdateEntityPosition* packet);
		bool handle(packet::play::s2c::UpdateEntityPositionRotation* packet);
		bool handle(packet::play::s2c::UpdateEntityRotation* packet);
		bool handle(packet::play::s2c::MoveVehicle* packet);
		bool handle(packet::play::s2c::OpenBook* packet);
		bool handle(packet::play::s2c::OpenScreen* packet);
		bool handle(packet::play::s2c::OpenSignEditor* packet);
		bool handle(packet::play::s2c::Ping* packet);
		bool handle(packet::play::s2c::PingResponse* packet);
		bool handle(packet::play::s2c::PlaceGhostRecipe* packet);
		bool handle(packet::play::s2c::PlayerAbilities* packet);
		bool handle(packet::play::s2c::PlayerChatMessage* packet);
		bool handle(packet::play::s2c::EndCombat* packet);
		bool handle(packet::play::s2c::EnterCombat* packet);
		bool handle(packet::play::s2c::CombatDeath* packet);
		bool handle(packet::play::s2c::PlayerInfoRemove* packet);
		bool handle(packet::play::s2c::PlayerInfoUpdate* packet);
		bool handle(packet::play::s2c::LookAt* packet);
		bool handle(packet::play::s2c::SynchronizePlayerPosition* packet);
		bool handle(packet::play::s2c::UpdateRecipeBook* packet);
		bool handle(packet::play::s2c::RemoveEntities* packet);
		bool handle(packet::play::s2c::RemoveEntityEffect* packet);
		bool handle(packet::play::s2c::ResetScore* packet);
		bool handle(packet::play::s2c::RemoveResourcePack* packet);
		bool handle(packet::play::s2c::AddResourcePack* packet);
		bool handle(packet::play::s2c::Respawn* packet);
		bool handle(packet::play::s2c::SetHeadRotation* packet);
		bool handle(packet::play::s2c::UpdateSectionBlocks* packet);
		bool handle(packet::play::s2c::SelectAdvancementsTab* packet);
		bool handle(packet::play::s2c::ServerData* packet);
		bool handle(packet::play::s2c::SetActionBarText* packet);
		bool handle(packet::play::s2c::SetBorderCenter* packet);
		bool handle(packet::play::s2c::SetBorderLerpSize* packet);
		bool handle(packet::play::s2c::SetBorderSize* packet);
		bool handle(packet::play::s2c::SetBorderWarningDelay* packet);
		bool handle(packet::play::s2c::SetBorderWarningDistance* packet);
		bool handle(packet::play::s2c::SetCamera* packet);
		bool handle(packet::play::s2c::SetHeldItem* packet);
		bool handle(packet::play::s2c::SetCenterChunk* packet);
		bool handle(packet::play::s2c::SetRenderDistance* packet);
		bool handle(packet::play::s2c::SetDefaultSpawnPosition* packet);
		bool handle(packet::play::s2c::DisplayObjective* packet);
		bool handle(packet::play::s2c::SetEntityMetadata* packet);
		bool handle(packet::play::s2c::LinkEntities* packet);
		bool handle(packet::play::s2c::SetEntityVelocity* packet);
		bool handle(packet::play::s2c::SetEquipment* packet);
		bool handle(packet::play::s2c::SetExperience* packet);
		bool handle(packet::play::s2c::SetHealth* packet);
		bool handle(packet::play::s2c::UpdateObjectives* packet);
		bool handle(packet::play::s2c::SetPassengers* packet);
		bool handle(packet::play::s2c::UpdateTeams* packet);
		bool handle(packet::play::s2c::UpdateScore* packet);
		bool handle(packet::play::s2c::SetSimulationDistance* packet);
		bool handle(packet::play::s2c::SetSubtitleText* packet);
		bool handle(packet::play::s2c::UpdateTime* packet);
		bool handle(packet::play::s2c::SetTitleText* packet);
		bool handle(packet::play::s2c::SetTitleAnimationTimes* packet);
		bool handle(packet::play::s2c::EntitySoundEffect* packet);
		bool handle(packet::play::s2c::SoundEffect* packet);
		bool handle(packet::play::s2c::StartConfiguration* packet);
		bool handle(packet::play::s2c::StopSound* packet);
		bool handle(packet::play::s2c::StoreCookie* packet);
		bool handle(packet::play::s2c::SystemChatMessage* packet);
		bool handle(packet::play::s2c::SetTabListHeaderAndFooter* packet);
		bool handle(packet::play::s2c::TagQueryResponse* packet);
		bool handle(packet::play::s2c::PickupItem* packet);
		bool handle(packet::play::s2c::TeleportEntity* packet);
		bool handle(packet::play::s2c::SetTickingState* packet);
		bool handle(packet::play::s2c::StepTick* packet);
		bool handle(packet::play::s2c::Transfer* packet);
		bool handle(packet::play::s2c::UpdateAdvancements* packet);
		bool handle(packet::play::s2c::UpdateAttributes* packet);
		bool handle(packet::play::s2c::EntityEffect* packet);
		bool handle(packet::play::s2c::UpdateRecipes* packet);
		bool handle(packet::play::s2c::UpdateTags* packet);
		bool handle(packet::play::s2c::ProjectilePower* packet);
		bool handle(packet::play::s2c::CustomReportDetails* packet);
		bool handle(packet::play::s2c::ServerLinks* packet);
	};
}
