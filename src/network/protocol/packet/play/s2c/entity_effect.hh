#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::s2c
{
	class EntityEffect : public IPacket
	{
		int entityId;
		/// https://minecraft.wiki/w/Effect#Effect_list
		int effectId;
		/// starting at 0
		int amplifier;
		/// ticks
		int duration;
		/// mask
		/// - @c 0x01: ambient (from beacon)
		/// - @c 0x02: show particles
		/// - @c 0x04: show icon
		/// - @c 0x08: blend (only darkness) (pvn >= 1.20.5)
		byte_t flags;

		/// 1.19 - 1.20.3
		std::optional<std::unique_ptr<nbt::Tag>> factorCodec;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		int getEntityId() const;
		void setEntityId(int entity_id);

		int getEffectId() const;
		void setEffectId(int effect_id);

		int getAmplifier() const;
		void setAmplifier(int amplifier);

		int getDuration() const;
		void setDuration(int duration);

		byte_t getFlags() const;
		void setFlags(byte_t flags);

		const std::optional<std::unique_ptr<nbt::Tag>>& getFactorCodec() const;
		void setFactorCodec(std::optional<std::unique_ptr<nbt::Tag>>&& factor_codec);

		std::string toString() const override;
	};
}
