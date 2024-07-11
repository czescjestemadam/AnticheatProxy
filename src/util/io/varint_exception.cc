#include "varint_exception.hh"

const char* acp::VarintException::what() const noexcept
{
	return "Varint too big";
}
