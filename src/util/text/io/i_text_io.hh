#pragma once
#include "util/text/component.hh"

#include <memory>

namespace acp::text
{
	class PlaintextIO;
	class LegacyIO;
	class MinimessageIO;

	class ITextIO
	{
	public:
		virtual ~ITextIO() = default;

		virtual std::unique_ptr<Component> parse(const std::string& str) const = 0;
		virtual std::string write(const std::unique_ptr<Component>& component) const = 0;


		static PlaintextIO& plaintext();
		static LegacyIO& legacy();
		static MinimessageIO& minimessage();
	};
}
