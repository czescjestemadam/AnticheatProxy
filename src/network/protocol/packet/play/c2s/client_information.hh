#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::c2s
{
	class ClientInformation : public IPacket
	{
		std::string locale;
		byte_t viewDistance;
		int chatMode;
		bool chatColors;
		byte_t skinParts;
		int mainHand;
		std::optional<bool> textFiltering;
		std::optional<bool> allowServerListing;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		const std::string& getLocale() const;
		void setLocale(const std::string& locale);

		byte_t getViewDistance() const;
		void setViewDistance(byte_t view_distance);

		int getChatMode() const;
		void setChatMode(int chat_mode);

		bool isChatColors() const;
		void setChatColors(bool chat_colors);

		byte_t getSkinParts() const;
		void setSkinParts(byte_t skin_parts);

		int getMainHand() const;
		void setMainHand(int main_hand);

		const std::optional<bool>& getTextFiltering() const;
		void setTextFiltering(const std::optional<bool>& text_filtering);

		const std::optional<bool>& getAllowServerListing() const;
		void setAllowServerListing(const std::optional<bool>& allow_server_listing);

		std::string toString() const override;
	};
}
