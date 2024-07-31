#pragma once
#include "forwarding_version.hh"
#include "util/game_profile.hh"
#include "util/io/byte_buf.hh"
#include "util/io/i_serializable.hh"

namespace acp::velocity
{
	/// supports only @c ForwardingVersion::MODER_LAZY_SESSION
	struct ForwardingInfo : ISerializable<ByteBuf>
	{
		ByteBuf signature;
		ForwardingVersion version;
		std::string address;
		GameProfile profile;

		ForwardingInfo() = default;
		ForwardingInfo(ForwardingVersion version, const std::string& address, const GameProfile& profile);

		ByteBuf serialize() override;
		void deserialize(ByteBuf& v) override;
	};
}
