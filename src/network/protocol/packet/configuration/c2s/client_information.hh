#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::configuration::c2s
{
	class ClientInformation : public IPacket
	{
		std::string locale;
		byte_t viewDistance;
		int chatMode;
		bool chatColors;
		byte_t skinParts;
		int mainHand;
		bool textFiltering;
		bool allowServerListing;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		bool apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		std::string& getLocale();
		void setLocale(const std::string& locale);

		byte_t& getViewDistance();
		void setViewDistance(byte_t view_distance);

		int& getChatMode();
		void setChatMode(int chat_mode);

		bool& isChatColors();
		void setChatColors(bool chat_colors);

		byte_t& getSkinParts();
		void setSkinParts(byte_t skin_parts);

		int& getMainHand();
		void setMainHand(int main_hand);

		bool& isTextFiltering();
		void setTextFiltering(bool text_filtering);

		bool& isAllowServerListing();
		void setAllowServerListing(bool allow_server_listing);

		std::string toString() const override;
	};
}
