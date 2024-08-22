#include "legacy_io.hh"

std::unique_ptr<acp::text::Component> acp::text::LegacyIO::parse(const std::string& str) const
{
	return nullptr;
}

std::string acp::text::LegacyIO::write(const std::unique_ptr<Component>& component) const
{
	return "";
}
