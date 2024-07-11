#include "hash.hh"

#include <openssl/md5.h>

std::array<byte_t, acp::hash::MD5_SIZE> acp::hash::md5(const byte_t* bytes, size_t len)
{
	byte_t out[MD5_SIZE];
	MD5(bytes, len, out);
	return std::to_array(out);
}

std::array<byte_t, acp::hash::MD5_SIZE> acp::hash::md5(const ByteBuf& buf)
{
	return md5(buf.data(), buf.size());
}
