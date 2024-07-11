#pragma once
#include "io/byte_buf.hh"

#include <array>

namespace acp::hash
{
	constexpr size_t MD5_SIZE = 16;

	std::array<byte_t, MD5_SIZE> md5(const byte_t* bytes, size_t len);
	std::array<byte_t, MD5_SIZE> md5(const ByteBuf& buf);
}
