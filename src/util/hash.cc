#include "hash.hh"

#include <openssl/md5.h>
#include <openssl/sha.h>

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


std::array<byte_t, acp::hash::SHA1_SIZE> acp::hash::sha1(const byte_t* bytes, size_t len)
{
	byte_t out[SHA1_SIZE];
	SHA1(bytes, len, out);
	return std::to_array(out);
}

std::array<byte_t, acp::hash::SHA1_SIZE> acp::hash::sha1(const ByteBuf& buf)
{
	return sha1(buf.data(), buf.size());
}


std::array<byte_t, acp::hash::SHA256_SIZE> acp::hash::sha256(const byte_t* bytes, size_t len)
{
	byte_t out[SHA256_SIZE];
	SHA256(bytes, len, out);
	return std::to_array(out);
}

std::array<byte_t, acp::hash::SHA256_SIZE> acp::hash::sha256(const ByteBuf& buf)
{
	return sha256(buf.data(), buf.size());
}
