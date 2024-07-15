#include "z_lib_exception.hh"

#include <zlib.h>

acp::ZLibException::ZLibException(int code) : code(code)
{
}

const char* acp::ZLibException::what() const noexcept
{
	switch (code)
	{
		case Z_MEM_ERROR: return "not enough memory";
		case Z_BUF_ERROR: return "output buffer too small";
		case Z_STREAM_ERROR: return "invalid compression level";
		case Z_DATA_ERROR: return "invalid input buffer";
		default: return "";
	}
}
