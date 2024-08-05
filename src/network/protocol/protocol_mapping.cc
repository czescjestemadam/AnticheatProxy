#include "protocol_mapping.hh"

#include "packet/status/c2s/status_request.hh"
#include "packet/status/c2s/ping_request.hh"
#include "packet/status/s2c/status_response.hh"
#include "packet/status/s2c/ping_response.hh"

#include "packet/login/c2s/cookie_response.hh"
#include "packet/login/c2s/encryption_response.hh"
#include "packet/login/c2s/login_acknowledged.hh"
#include "packet/login/c2s/login_plugin_response.hh"
#include "packet/login/c2s/login_start.hh"
#include "packet/login/s2c/cookie_request.hh"
#include "packet/login/s2c/disconnect.hh"
#include "packet/login/s2c/encryption_request.hh"
#include "packet/login/s2c/login_plugin_request.hh"
#include "packet/login/s2c/login_success.hh"
#include "packet/login/s2c/set_compression.hh"

#include "packet/configuration/c2s/acknowledge_finish_configuration.hh"
#include "packet/configuration/c2s/client_information.hh"
#include "packet/configuration/c2s/cookie_response.hh"
#include "packet/configuration/c2s/keep_alive.hh"
#include "packet/configuration/c2s/known_packs.hh"
#include "packet/configuration/c2s/plugin_message.hh"
#include "packet/configuration/c2s/pong.hh"
#include "packet/configuration/c2s/resource_pack_response.hh"
#include "packet/configuration/s2c/add_resource_pack.hh"
#include "packet/configuration/s2c/cookie_request.hh"
#include "packet/configuration/s2c/custom_report_details.hh"
#include "packet/configuration/s2c/disconnect.hh"
#include "packet/configuration/s2c/feature_flags.hh"
#include "packet/configuration/s2c/finish_configuration.hh"
#include "packet/configuration/s2c/keep_alive.hh"
#include "packet/configuration/s2c/known_packs.hh"
#include "packet/configuration/s2c/ping.hh"
#include "packet/configuration/s2c/plugin_message.hh"
#include "packet/configuration/s2c/registry_data.hh"
#include "packet/configuration/s2c/remove_resource_pack.hh"
#include "packet/configuration/s2c/reset_chat.hh"
#include "packet/configuration/s2c/server_links.hh"
#include "packet/configuration/s2c/store_cookie.hh"
#include "packet/configuration/s2c/transfer.hh"
#include "packet/configuration/s2c/update_tags.hh"

#include "packet/play/c2s/acknowledge_configuration.hh"
#include "packet/play/c2s/acknowledge_message.hh"
#include "packet/play/c2s/change_container_slot_state.hh"
#include "packet/play/c2s/change_difficulty.hh"
#include "packet/play/c2s/change_recipe_book_settings.hh"
#include "packet/play/c2s/chat_command.hh"
#include "packet/play/c2s/chat_message.hh"
#include "packet/play/c2s/chunk_batch_received.hh"
#include "packet/play/c2s/click_container.hh"
#include "packet/play/c2s/click_container_button.hh"
#include "packet/play/c2s/client_information.hh"
#include "packet/play/c2s/client_status.hh"
#include "packet/play/c2s/close_container.hh"
#include "packet/play/c2s/command_suggestions_request.hh"
#include "packet/play/c2s/confirm_teleportation.hh"
#include "packet/play/c2s/cookie_response.hh"
#include "packet/play/c2s/debug_sample_subscription.hh"
#include "packet/play/c2s/edit_book.hh"
#include "packet/play/c2s/interact.hh"
#include "packet/play/c2s/jigsaw_generate.hh"
#include "packet/play/c2s/keep_alive.hh"
#include "packet/play/c2s/lock_difficulty.hh"
#include "packet/play/c2s/move_vehicle.hh"
#include "packet/play/c2s/paddle_boat.hh"
#include "packet/play/c2s/pick_item.hh"
#include "packet/play/c2s/ping_request.hh"
#include "packet/play/c2s/place_recipe.hh"
#include "packet/play/c2s/player_abilities.hh"
#include "packet/play/c2s/player_action.hh"
#include "packet/play/c2s/player_command.hh"
#include "packet/play/c2s/player_input.hh"
#include "packet/play/c2s/player_session.hh"
#include "packet/play/c2s/plugin_message.hh"
#include "packet/play/c2s/pong.hh"
#include "packet/play/c2s/program_command_block.hh"
#include "packet/play/c2s/program_command_block_minecart.hh"
#include "packet/play/c2s/program_jigsaw_block.hh"
#include "packet/play/c2s/program_structure_block.hh"
#include "packet/play/c2s/query_block_entity_tag.hh"
#include "packet/play/c2s/query_entity_tag.hh"
#include "packet/play/c2s/rename_item.hh"
#include "packet/play/c2s/resource_pack_response.hh"
#include "packet/play/c2s/seen_advancements.hh"
#include "packet/play/c2s/select_trade.hh"
#include "packet/play/c2s/set_beacon_effect.hh"
#include "packet/play/c2s/set_creative_mode_slot.hh"
#include "packet/play/c2s/set_held_item.hh"
#include "packet/play/c2s/set_player_on_ground.hh"
#include "packet/play/c2s/set_player_position.hh"
#include "packet/play/c2s/set_player_position_rotation.hh"
#include "packet/play/c2s/set_player_rotation.hh"
#include "packet/play/c2s/set_seen_recipe.hh"
#include "packet/play/c2s/signed_chat_command.hh"
#include "packet/play/c2s/swing_arm.hh"
#include "packet/play/c2s/teleport_to_entity.hh"
#include "packet/play/c2s/update_sign.hh"
#include "packet/play/c2s/use_item.hh"
#include "packet/play/c2s/use_item_on.hh"
#include "packet/play/s2c/acknowledge_block_change.hh"
#include "packet/play/s2c/add_resource_pack.hh"
#include "packet/play/s2c/award_statistics.hh"
#include "packet/play/s2c/block_action.hh"
#include "packet/play/s2c/block_entity_data.hh"
#include "packet/play/s2c/block_update.hh"
#include "packet/play/s2c/boss_bar.hh"
#include "packet/play/s2c/bundle_delimiter.hh"
#include "packet/play/s2c/change_difficulty.hh"
#include "packet/play/s2c/chat_suggestions.hh"
#include "packet/play/s2c/chunk_batch_finished.hh"
#include "packet/play/s2c/chunk_batch_start.hh"
#include "packet/play/s2c/chunk_biomes.hh"
#include "packet/play/s2c/chunk_data_and_update_light.hh"
#include "packet/play/s2c/clear_titles.hh"
#include "packet/play/s2c/close_container.hh"
#include "packet/play/s2c/combat_death.hh"
#include "packet/play/s2c/command_suggestions_response.hh"
#include "packet/play/s2c/commands.hh"
#include "packet/play/s2c/cookie_request.hh"
#include "packet/play/s2c/custom_report_details.hh"
#include "packet/play/s2c/damage_event.hh"
#include "packet/play/s2c/debug_sample.hh"
#include "packet/play/s2c/delete_message.hh"
#include "packet/play/s2c/disconnect.hh"
#include "packet/play/s2c/disguised_chat_message.hh"
#include "packet/play/s2c/display_objective.hh"
#include "packet/play/s2c/end_combat.hh"
#include "packet/play/s2c/enter_combat.hh"
#include "packet/play/s2c/entity_animation.hh"
#include "packet/play/s2c/entity_effect.hh"
#include "packet/play/s2c/entity_event.hh"
#include "packet/play/s2c/entity_sound_effect.hh"
#include "packet/play/s2c/explosion.hh"
#include "packet/play/s2c/game_event.hh"
#include "packet/play/s2c/hurt_animation.hh"
#include "packet/play/s2c/initialize_world_border.hh"
#include "packet/play/s2c/keep_alive.hh"
#include "packet/play/s2c/link_entities.hh"
#include "packet/play/s2c/login.hh"
#include "packet/play/s2c/look_at.hh"
#include "packet/play/s2c/map_data.hh"
#include "packet/play/s2c/merchant_offers.hh"
#include "packet/play/s2c/move_vehicle.hh"
#include "packet/play/s2c/open_book.hh"
#include "packet/play/s2c/open_horse_screen.hh"
#include "packet/play/s2c/open_screen.hh"
#include "packet/play/s2c/open_sign_editor.hh"
#include "packet/play/s2c/particle.hh"
#include "packet/play/s2c/pickup_item.hh"
#include "packet/play/s2c/ping.hh"
#include "packet/play/s2c/ping_response.hh"
#include "packet/play/s2c/place_ghost_recipe.hh"
#include "packet/play/s2c/player_abilities.hh"
#include "packet/play/s2c/player_chat_message.hh"
#include "packet/play/s2c/player_info_remove.hh"
#include "packet/play/s2c/player_info_update.hh"
#include "packet/play/s2c/plugin_message.hh"
#include "packet/play/s2c/projectile_power.hh"
#include "packet/play/s2c/remove_entities.hh"
#include "packet/play/s2c/remove_entity_effect.hh"
#include "packet/play/s2c/remove_resource_pack.hh"
#include "packet/play/s2c/reset_score.hh"
#include "packet/play/s2c/respawn.hh"
#include "packet/play/s2c/select_advancements_tab.hh"
#include "packet/play/s2c/server_data.hh"
#include "packet/play/s2c/server_links.hh"
#include "packet/play/s2c/set_action_bar_text.hh"
#include "packet/play/s2c/set_block_destroy_stage.hh"
#include "packet/play/s2c/set_border_center.hh"
#include "packet/play/s2c/set_border_lerp_size.hh"
#include "packet/play/s2c/set_border_size.hh"
#include "packet/play/s2c/set_border_warning_delay.hh"
#include "packet/play/s2c/set_border_warning_distance.hh"
#include "packet/play/s2c/set_camera.hh"
#include "packet/play/s2c/set_center_chunk.hh"
#include "packet/play/s2c/set_container_content.hh"
#include "packet/play/s2c/set_container_property.hh"
#include "packet/play/s2c/set_container_slot.hh"
#include "packet/play/s2c/set_cooldown.hh"
#include "packet/play/s2c/set_default_spawn_position.hh"
#include "packet/play/s2c/set_entity_metadata.hh"
#include "packet/play/s2c/set_entity_velocity.hh"
#include "packet/play/s2c/set_equipment.hh"
#include "packet/play/s2c/set_experience.hh"
#include "packet/play/s2c/set_head_rotation.hh"
#include "packet/play/s2c/set_health.hh"
#include "packet/play/s2c/set_held_item.hh"
#include "packet/play/s2c/set_passengers.hh"
#include "packet/play/s2c/set_render_distance.hh"
#include "packet/play/s2c/set_simulation_distance.hh"
#include "packet/play/s2c/set_subtitle_text.hh"
#include "packet/play/s2c/set_tab_list_header_and_footer.hh"
#include "packet/play/s2c/set_ticking_state.hh"
#include "packet/play/s2c/set_title_animation_times.hh"
#include "packet/play/s2c/set_title_text.hh"
#include "packet/play/s2c/sound_effect.hh"
#include "packet/play/s2c/spawn_entity.hh"
#include "packet/play/s2c/spawn_experience_orb.hh"
#include "packet/play/s2c/start_configuration.hh"
#include "packet/play/s2c/step_tick.hh"
#include "packet/play/s2c/stop_sound.hh"
#include "packet/play/s2c/store_cookie.hh"
#include "packet/play/s2c/synchronize_player_position.hh"
#include "packet/play/s2c/system_chat_message.hh"
#include "packet/play/s2c/tag_query_response.hh"
#include "packet/play/s2c/teleport_entity.hh"
#include "packet/play/s2c/transfer.hh"
#include "packet/play/s2c/unload_chunk.hh"
#include "packet/play/s2c/update_advancements.hh"
#include "packet/play/s2c/update_attributes.hh"
#include "packet/play/s2c/update_entity_position.hh"
#include "packet/play/s2c/update_entity_position_rotation.hh"
#include "packet/play/s2c/update_entity_rotation.hh"
#include "packet/play/s2c/update_light.hh"
#include "packet/play/s2c/update_objectives.hh"
#include "packet/play/s2c/update_recipe_book.hh"
#include "packet/play/s2c/update_recipes.hh"
#include "packet/play/s2c/update_score.hh"
#include "packet/play/s2c/update_section_blocks.hh"
#include "packet/play/s2c/update_tags.hh"
#include "packet/play/s2c/update_teams.hh"
#include "packet/play/s2c/update_time.hh"
#include "packet/play/s2c/world_event.hh"

#define PACKET_CONSTRUCTOR(packet) [] (const ByteBuf& buf) { return std::make_unique<packet>(buf); }

#define ADD_PACKET(state, side, packet) {							\
		packet p;													\
		int id = p.getId(version);									\
		if (id >= 0)												\
			mappings[state][side][id] = PACKET_CONSTRUCTOR(packet);	\
	}

acp::ProtocolMapping::ProtocolMapping(const ProtocolVersion* version)
{
	ADD_PACKET(NetworkState::STATUS, NetworkSide::CLIENT, packet::status::c2s::StatusRequest)
	ADD_PACKET(NetworkState::STATUS, NetworkSide::CLIENT, packet::status::c2s::PingRequest)
	ADD_PACKET(NetworkState::STATUS, NetworkSide::DEST, packet::status::s2c::StatusResponse)
	ADD_PACKET(NetworkState::STATUS, NetworkSide::DEST, packet::status::s2c::PingResponse)

	ADD_PACKET(NetworkState::LOGIN, NetworkSide::CLIENT, packet::login::c2s::LoginStart)
	ADD_PACKET(NetworkState::LOGIN, NetworkSide::CLIENT, packet::login::c2s::EncryptionResponse)
	ADD_PACKET(NetworkState::LOGIN, NetworkSide::CLIENT, packet::login::c2s::LoginPluginResponse)
	ADD_PACKET(NetworkState::LOGIN, NetworkSide::CLIENT, packet::login::c2s::LoginAcknowledged)
	ADD_PACKET(NetworkState::LOGIN, NetworkSide::CLIENT, packet::login::c2s::CookieResponse)
	ADD_PACKET(NetworkState::LOGIN, NetworkSide::DEST, packet::login::s2c::Disconnect)
	ADD_PACKET(NetworkState::LOGIN, NetworkSide::DEST, packet::login::s2c::EncryptionRequest)
	ADD_PACKET(NetworkState::LOGIN, NetworkSide::DEST, packet::login::s2c::LoginSuccess)
	ADD_PACKET(NetworkState::LOGIN, NetworkSide::DEST, packet::login::s2c::SetCompression)
	ADD_PACKET(NetworkState::LOGIN, NetworkSide::DEST, packet::login::s2c::LoginPluginRequest)
	ADD_PACKET(NetworkState::LOGIN, NetworkSide::DEST, packet::login::s2c::CookieRequest)

	ADD_PACKET(NetworkState::CONFIGURATION, NetworkSide::CLIENT, packet::configuration::c2s::ClientInformation)
	ADD_PACKET(NetworkState::CONFIGURATION, NetworkSide::CLIENT, packet::configuration::c2s::CookieResponse)
	ADD_PACKET(NetworkState::CONFIGURATION, NetworkSide::CLIENT, packet::configuration::c2s::PluginMessage)
	ADD_PACKET(NetworkState::CONFIGURATION, NetworkSide::CLIENT, packet::configuration::c2s::AcknowledgeFinishConfiguration)
	ADD_PACKET(NetworkState::CONFIGURATION, NetworkSide::CLIENT, packet::configuration::c2s::KeepAlive)
	ADD_PACKET(NetworkState::CONFIGURATION, NetworkSide::CLIENT, packet::configuration::c2s::Pong)
	// ADD_PACKET(NetworkState::CONFIGURATION, NetworkSide::CLIENT, packet::configuration::c2s::ResourcePackResponse)
	ADD_PACKET(NetworkState::CONFIGURATION, NetworkSide::CLIENT, packet::configuration::c2s::KnownPacks)
	// ADD_PACKET(NetworkState::CONFIGURATION, NetworkSide::DEST, packet::configuration::s2c::CookieRequest)
	// ADD_PACKET(NetworkState::CONFIGURATION, NetworkSide::DEST, packet::configuration::s2c::PluginMessage)
	ADD_PACKET(NetworkState::CONFIGURATION, NetworkSide::DEST, packet::configuration::s2c::Disconnect)
	ADD_PACKET(NetworkState::CONFIGURATION, NetworkSide::DEST, packet::configuration::s2c::FinishConfiguration)
	// ADD_PACKET(NetworkState::CONFIGURATION, NetworkSide::DEST, packet::configuration::s2c::KeepAlive)
	// ADD_PACKET(NetworkState::CONFIGURATION, NetworkSide::DEST, packet::configuration::s2c::Ping)
	ADD_PACKET(NetworkState::CONFIGURATION, NetworkSide::DEST, packet::configuration::s2c::ResetChat)
	ADD_PACKET(NetworkState::CONFIGURATION, NetworkSide::DEST, packet::configuration::s2c::RegistryData)
	// ADD_PACKET(NetworkState::CONFIGURATION, NetworkSide::DEST, packet::configuration::s2c::RemoveResourcePack)
	// ADD_PACKET(NetworkState::CONFIGURATION, NetworkSide::DEST, packet::configuration::s2c::AddResourcePack)
	// ADD_PACKET(NetworkState::CONFIGURATION, NetworkSide::DEST, packet::configuration::s2c::StoreCookie)
	// ADD_PACKET(NetworkState::CONFIGURATION, NetworkSide::DEST, packet::configuration::s2c::Transfer)
	ADD_PACKET(NetworkState::CONFIGURATION, NetworkSide::DEST, packet::configuration::s2c::FeatureFlags)
	// ADD_PACKET(NetworkState::CONFIGURATION, NetworkSide::DEST, packet::configuration::s2c::UpdateTags)
	// ADD_PACKET(NetworkState::CONFIGURATION, NetworkSide::DEST, packet::configuration::s2c::KnownPacks)
	// ADD_PACKET(NetworkState::CONFIGURATION, NetworkSide::DEST, packet::configuration::s2c::CustomReportDetails)
	// ADD_PACKET(NetworkState::CONFIGURATION, NetworkSide::DEST, packet::configuration::s2c::ServerLinks)

	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::ConfirmTeleportation)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::QueryBlockEntityTag)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::ChangeDifficulty)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::AcknowledgeMessage)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::ChatCommand)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::SignedChatCommand)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::ChatMessage)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::PlayerSession)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::ChunkBatchReceived)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::ClientStatus)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::ClientInformation)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::CommandSuggestionsRequest)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::AcknowledgeConfiguration)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::ClickContainerButton)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::ClickContainer)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::CloseContainer)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::ChangeContainerSlotState)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::CookieResponse)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::PluginMessage)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::DebugSampleSubscription)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::EditBook)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::QueryEntityTag)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::Interact)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::JigsawGenerate)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::KeepAlive)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::LockDifficulty)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::SetPlayerPosition)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::SetPlayerPositionRotation)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::SetPlayerRotation)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::SetPlayerOnGround)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::MoveVehicle)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::PaddleBoat)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::PickItem)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::PingRequest)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::PlaceRecipe)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::PlayerAbilities)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::PlayerAction)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::PlayerCommand)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::PlayerInput)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::Pong)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::ChangeRecipeBookSettings)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::SetSeenRecipe)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::RenameItem)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::ResourcePackResponse)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::SeenAdvancements)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::SelectTrade)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::SetBeaconEffect)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::SetHeldItem)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::ProgramCommandBlock)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::ProgramCommandBlockMinecart)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::SetCreativeModeSlot)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::ProgramJigsawBlock)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::ProgramStructureBlock)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::UpdateSign)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::SwingArm)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::TeleportToEntity)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::UseItemOn)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::CLIENT, packet::play::c2s::UseItem)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::BundleDelimiter)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SpawnEntity)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SpawnExperienceOrb)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::EntityAnimation)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::AwardStatistics)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::AcknowledgeBlockChange)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetBlockDestroyStage)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::BlockEntityData)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::BlockAction)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::BlockUpdate)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::BossBar)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::ChangeDifficulty)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::ChunkBatchFinished)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::ChunkBatchStart)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::ChunkBiomes)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::ClearTitles)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::CommandSuggestionsResponse)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::Commands)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::CloseContainer)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetContainerContent)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetContainerProperty)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetContainerSlot)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::CookieRequest)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetCooldown)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::ChatSuggestions)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::PluginMessage)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::DamageEvent)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::DebugSample)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::DeleteMessage)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::Disconnect)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::DisguisedChatMessage)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::EntityEvent)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::Explosion)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::UnloadChunk)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::GameEvent)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::OpenHorseScreen)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::HurtAnimation)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::InitializeWorldBorder)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::KeepAlive)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::ChunkDataAndUpdateLight)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::WorldEvent)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::Particle)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::UpdateLight)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::Login)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::MapData)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::MerchantOffers)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::UpdateEntityPosition)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::UpdateEntityPositionRotation)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::UpdateEntityRotation)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::MoveVehicle)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::OpenBook)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::OpenScreen)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::OpenSignEditor)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::Ping)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::PingResponse)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::PlaceGhostRecipe)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::PlayerAbilities)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::PlayerChatMessage)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::EndCombat)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::EnterCombat)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::CombatDeath)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::PlayerInfoRemove)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::PlayerInfoUpdate)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::LookAt)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SynchronizePlayerPosition)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::UpdateRecipeBook)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::RemoveEntities)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::RemoveEntityEffect)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::ResetScore)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::RemoveResourcePack)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::AddResourcePack)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::Respawn)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetHeadRotation)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::UpdateSectionBlocks)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SelectAdvancementsTab)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::ServerData)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetActionBarText)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetBorderCenter)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetBorderLerpSize)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetBorderSize)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetBorderWarningDelay)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetBorderWarningDistance)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetCamera)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetHeldItem)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetCenterChunk)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetRenderDistance)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetDefaultSpawnPosition)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::DisplayObjective)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetEntityMetadata)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::LinkEntities)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetEntityVelocity)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetEquipment)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetExperience)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetHealth)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::UpdateObjectives)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetPassengers)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::UpdateTeams)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::UpdateScore)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetSimulationDistance)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetSubtitleText)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::UpdateTime)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetTitleText)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetTitleAnimationTimes)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::EntitySoundEffect)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SoundEffect)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::StartConfiguration)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::StopSound)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::StoreCookie)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SystemChatMessage)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetTabListHeaderAndFooter)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::TagQueryResponse)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::PickupItem)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::TeleportEntity)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::SetTickingState)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::StepTick)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::Transfer)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::UpdateAdvancements)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::UpdateAttributes)
	ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::EntityEffect)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::UpdateRecipes)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::UpdateTags)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::ProjectilePower)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::CustomReportDetails)
	// ADD_PACKET(NetworkState::PLAY, NetworkSide::DEST, packet::play::s2c::ServerLinks)
}

std::unique_ptr<acp::packet::IPacket> acp::ProtocolMapping::create(NetworkState state, NetworkSide sourceSide, int id, const ByteBuf& buf) const
{
	if (!mappings.contains(state))
		return nullptr;
	const auto& stateMappings = mappings.at(state);

	if (!stateMappings.contains(sourceSide))
		return nullptr;
	const auto& sideMappings = stateMappings.at(sourceSide);

	if (!sideMappings.contains(id))
		return nullptr;
	return sideMappings.at(id)(buf);
}

size_t acp::ProtocolMapping::size() const
{
	size_t count = 0;

	for (const auto& [state, stateMappings] : mappings)
	{
		for (const auto& [side, sideMappings] : stateMappings)
			count += sideMappings.size();
	}

	return count;
}
