#pragma once
#include "util/io/byte_buf.hh"
#include "util/io/i_serializable.hh"

namespace acp::command
{
	struct IProperties : ISerializable<ByteBuf>
	{
	};
}
