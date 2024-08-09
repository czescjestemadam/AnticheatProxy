#include "command_node.hh"

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

acp::ByteBuf acp::command::Node::serialize()
{
	ByteBuf buf;

	buf.writeByte(flags);

	buf.writeVarint(static_cast<int>(children.size()));
	for (const int child : children)
		buf.writeVarint(child);

	if (flags & 0x08)
		buf.writeVarint(redirectNode.value());

	const byte_t type = flags & 0x03;
	if (type > 0)
		buf.writeStr(name);

	if (type == 2)
	{
		buf.writeVarint(parserId.value());
		buf.writeBuf(properties->serialize());
	}

	if (flags & 0x10)
		buf.writeIdentifier(suggestionsType.value());

	return buf;
}

void acp::command::Node::deserialize(ByteBuf& v)
{
	flags = v.readByte();

	const int len = v.readVarint();
	for (int i = 0; i < len; ++i)
		children.push_back(v.readVarint());

	if (flags & 0x08)
		redirectNode = v.readVarint();

	const byte_t type = flags & 0x03;
	if (type > 0)
		name = v.readStr();

	if (type == 2)
	{
		const int id = v.readVarint();
		parserId = id;
		properties = IProperties::fromParserId(id);
		properties->deserialize(v);
	}

	if (flags & 0x10)
		suggestionsType = v.readIdentifier();
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

	return std::format("Node[fl=0x{:02x}, child={}, redir={}, name={}, parser={}, prop={}, suggest={}]",
					   flags,
					   childStr,
					   redirectNode.value_or(-1),
					   name,
					   parserId.value_or(-1),
					   sizeof(*properties),
					   suggestionsType.value_or(Identifier{ "", "empty" }).toString()
	);
}
