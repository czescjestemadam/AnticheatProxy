#pragma once
#include "io/byte_buf.hh"

#include <string>

namespace acp::base64
{
	std::string encode(const byte_t* bytes, size_t len);

	std::string encode(const ByteBuf& buf);
	std::string encode(const std::string& str);


	ByteBuf decode(const std::string& base64);
}
