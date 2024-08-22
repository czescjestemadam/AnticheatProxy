#include "i_text_io.hh"

#include "legacy/legacy_io.hh"
#include "minimessage/minimessage_io.hh"
#include "plaintext/plaintext_io.hh"

acp::text::PlaintextIO& acp::text::ITextIO::plaintext()
{
	static PlaintextIO plaintext;
	return plaintext;
}

acp::text::LegacyIO& acp::text::ITextIO::legacy()
{
	static LegacyIO legacy;
	return legacy;
}

acp::text::MinimessageIO& acp::text::ITextIO::minimessage()
{
	static MinimessageIO minimessage;
	return minimessage;
}
