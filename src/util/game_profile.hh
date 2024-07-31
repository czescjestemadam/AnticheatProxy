#pragma once
#include "uuid.hh"
#include "io/byte_buf.hh"
#include "io/i_serializable.hh"

namespace acp
{
	struct GameProfile : ISerializable<ByteBuf>
	{
		struct Property : ISerializable<ByteBuf>
		{
			std::string name;
			std::string value;
			std::string signature;

			ByteBuf serialize() override;
			void deserialize(ByteBuf& v) override;
		};

		UUID uuid;
		std::string username;
		std::vector<Property> properties;


		ByteBuf serialize() override;
		void deserialize(ByteBuf& v) override;
	};
}
