#pragma once
#include "properties/i_properties.hh"

namespace acp::command
{
	class Node : ISerializable<ByteBuf>
	{
		/// mask
		/// - @c 0x03: node type (0 - root, 1 - literal, 2 - argument)
		/// - @c 0x04: executable
		/// - @c 0x08: redirect
		/// - @c 0x10: has suggestions type (only for argument)
		byte_t flags;

		/// indices of child nodes
		std::vector<int> children;

		std::optional<int> redirectNode;
		std::string name;
		std::optional<int> parserId;
		std::unique_ptr<IProperties> properties;
		std::optional<Identifier> suggestionsType;

	public:
		Node() = default;
		Node(byte_t flags, const std::vector<int>& children, const std::optional<int>& redirect_node, const std::string& name,
			const std::optional<int>& parser_id, std::unique_ptr<IProperties>&& properties, const std::optional<Identifier>& suggestions_type);

		byte_t getFlags() const;
		void setFlags(byte_t flags);

		const std::vector<int>& getChildren() const;
		void setChildren(const std::vector<int>& children);

		const std::optional<int>& getRedirectNode() const;
		void setRedirectNode(const std::optional<int>& redirect_node);

		const std::string& getName() const;
		void setName(const std::string& name);

		const std::optional<int>& getParserId() const;
		void setParserId(const std::optional<int>& parser_id);

		const std::unique_ptr<IProperties>& getProperties() const;
		void setProperties(std::unique_ptr<IProperties>&& properties);

		const std::optional<Identifier>& getSuggestionsType() const;
		void setSuggestionsType(const std::optional<Identifier>& suggestions_type);

		ByteBuf serialize() override;
		void deserialize(ByteBuf& v) override;

		std::string toString() const;
	};
}
