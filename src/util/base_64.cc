#include "base_64.hh"

constexpr const char* CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static size_t encodedLen(size_t len)
{
	return (len + 2) / 3 * 4;
}


std::string acp::base64::encode(const byte_t* bytes, size_t len)
{
	const size_t outLen = encodedLen(len);

	std::string out;
	out.reserve(outLen);

	size_t idx = 0;
	while (idx < len)
	{
		out += CHARS[(bytes[idx] & 0xfc) >> 2];

		if (idx + 1 < len)
		{
			out += CHARS[((bytes[idx] & 0x03) << 4) + ((bytes[idx + 1] & 0xf0) >> 4)];

			if (idx + 2 < len)
			{
				out += CHARS[((bytes[idx + 1] & 0x0f) << 2) + ((bytes[idx + 2] & 0xc0) >> 6)];
				out += CHARS[bytes[idx + 2] & 0x3f];
			}
			else
			{
				out += CHARS[(bytes[idx + 1] & 0x0f) << 2];
				out += '=';
			}
		}
		else
		{
			out += CHARS[(bytes[idx] & 0x03) << 4];
			out += "==";
		}

		idx += 3;
	}

	return out;
}

std::string acp::base64::encode(const ByteBuf& buf)
{
	return encode(buf.data(), buf.size());
}

std::string acp::base64::encode(const std::string& str)
{
	return encode(reinterpret_cast<const byte_t*>(str.data()), str.size());
}


acp::ByteBuf acp::base64::decode(const std::string& base64)
{
	// TODO
	return {};
}
