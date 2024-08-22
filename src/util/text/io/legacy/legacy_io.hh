#pragma once
#include "util/text/io/i_text_io.hh"

namespace acp::text
{
	class LegacyIO : public ITextIO
	{
	public:
		std::unique_ptr<Component> parse(const std::string& str, char prefix) const;
		std::unique_ptr<Component> parse(const std::string& str) const override;

		std::string write(const std::unique_ptr<Component>& component, char prefix) const;
		std::string write(const std::unique_ptr<Component>& component) const override;
	};
}
