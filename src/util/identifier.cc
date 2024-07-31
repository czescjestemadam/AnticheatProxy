#include "identifier.hh"

acp::Identifier::Identifier(const std::string& ns, const std::string& key) : ns(ns), key(key)
{
}

std::string acp::Identifier::getNs() const
{
	return ns;
}

void acp::Identifier::setNs(const std::string& ns)
{
	this->ns = ns;
}

std::string acp::Identifier::getKey() const
{
	return key;
}

void acp::Identifier::setKey(const std::string& key)
{
	this->key = key;
}

std::string acp::Identifier::toString() const
{
	return ns + ':' + key;
}

bool acp::Identifier::operator==(const Identifier& rhs) const
{
	return ns == rhs.ns && key == rhs.key;
}

bool acp::Identifier::operator!=(const Identifier& rhs) const
{
	return !(*this == rhs);
}


acp::Identifier acp::Identifier::parse(const std::string& str)
{
	const size_t colonPos = str.find(':');
	if (colonPos == std::string::npos)
		return { "", "" };

	return { str.substr(0, colonPos), str.substr(colonPos + 1) };
}
