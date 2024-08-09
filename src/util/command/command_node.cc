#include "command_node.hh"

#include "network/protocol/protocol_version.hh"

acp::command::Node::Node(byte_t flags, const std::vector<int>& children, const std::optional<int>& redirect_node, const std::string& name,
						 const std::optional<int>& parser_id, std::unique_ptr<IProperties>&& properties, const std::optional<Identifier>& suggestions_type)
	: flags(flags),
	  children(children),
	  redirectNode(redirect_node),
	  name(name),
	  parserId(parser_id),
	  properties(std::move(properties)),
	  suggestionsType(suggestions_type)
{
}

byte_t acp::command::Node::getFlags() const
{
	return flags;
}

void acp::command::Node::setFlags(const byte_t flags)
{
	this->flags = flags;
}

std::vector<int>& acp::command::Node::getChildren()
{
	return children;
}

const std::vector<int>& acp::command::Node::getChildren() const
{
	return children;
}

void acp::command::Node::setChildren(const std::vector<int>& children)
{
	this->children = children;
}

const std::optional<int>& acp::command::Node::getRedirectNode() const
{
	return redirectNode;
}

void acp::command::Node::setRedirectNode(const std::optional<int>& redirect_node)
{
	redirectNode = redirect_node;
}

const std::string& acp::command::Node::getName() const
{
	return name;
}

void acp::command::Node::setName(const std::string& name)
{
	this->name = name;
}

const std::optional<int>& acp::command::Node::getParserId() const
{
	return parserId;
}

void acp::command::Node::setParserId(const std::optional<int>& parser_id)
{
	parserId = parser_id;
}

const std::unique_ptr<acp::command::IProperties>& acp::command::Node::getProperties() const
{
	return properties;
}

void acp::command::Node::setProperties(std::unique_ptr<IProperties>&& properties)
{
	this->properties = std::move(properties);
}

const std::optional<acp::Identifier>& acp::command::Node::getSuggestionsType() const
{
	return suggestionsType;
}

void acp::command::Node::setSuggestionsType(const std::optional<Identifier>& suggestions_type)
{
	suggestionsType = suggestions_type;
}

void acp::command::Node::serialize(ByteBuf& buf, const ProtocolVersion* version)
{
	buf.writeByte(flags);

	buf.writeVarint(static_cast<int>(children.size()));
	for (const int child : children)
		buf.writeVarint(child);

	if (flags & REDIRECT)
		buf.writeVarint(redirectNode.value());

	const byte_t type = flags & 0x03;
	if (type > ROOT)
		buf.writeStr(name);

	if (type == ARGUMENT)
	{
		buf.writeVarint(parserId.value());
		if (properties)
			buf.writeBuf(properties->serialize());
	}

	if (flags & SUGGESTIONS)
		buf.writeIdentifier(suggestionsType.value());
}

void acp::command::Node::deserialize(ByteBuf& buf, const ProtocolVersion* version)
{
	flags = buf.readByte();

	const int len = buf.readVarint();
	for (int i = 0; i < len; ++i)
		children.push_back(buf.readVarint());

	if (flags & REDIRECT)
		redirectNode = buf.readVarint();

	const byte_t type = flags & 0x03;
	if (type > ROOT)
		name = buf.readStr();

	if (type == ARGUMENT)
	{
		parserId = buf.readVarint();
		if (const Parser* parser = version->getCommandParserMapping().get(parserId.value()))
		{
			properties = parser->createProperties();
			properties->deserialize(buf);
		}
	}

	if (flags & SUGGESTIONS)
		suggestionsType = buf.readIdentifier();
}

std::string acp::command::Node::toString() const
{
	std::string childStr;
	for (int i = 0; i < children.size(); ++i)
	{
		childStr += std::to_string(children[i]);

		if (i + 1 < children.size())
			childStr += ", ";
	}

	return std::format("Node[fl=0x{:02x}, child={}, redir={}, name={}, parser={}, suggest={}]",
					   flags,
					   childStr,
					   redirectNode.value_or(-1),
					   name,
					   parserId.value_or(-1),
					   suggestionsType.value_or(Identifier{ "", "empty" }).toString()
	);
}
