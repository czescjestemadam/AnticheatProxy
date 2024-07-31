#pragma once
#include "io/byte_buf.hh"

#include <array>

namespace acp::hash
{
	constexpr size_t MD5_SIZE = 16;

	std::array<byte_t, MD5_SIZE> md5(const byte_t* bytes, size_t len);
	std::array<byte_t, MD5_SIZE> md5(const ByteBuf& buf);


	constexpr size_t SHA1_SIZE = 40;

	std::array<byte_t, SHA1_SIZE> sha1(const byte_t* bytes, size_t len);
	std::array<byte_t, SHA1_SIZE> sha1(const ByteBuf& buf);


	constexpr size_t SHA256_SIZE = 64;

	std::array<byte_t, SHA256_SIZE> sha256(const byte_t* bytes, size_t len);
	std::array<byte_t, SHA256_SIZE> sha256(const ByteBuf& buf);
}
