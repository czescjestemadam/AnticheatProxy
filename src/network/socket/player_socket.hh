#pragma once
#include "i_socket.hh"
#include "network/network_side.hh"
#include "util/io/byte_buf.hh"

namespace acp
{
	class PlayerSocket : public ISocket
	{
		NetworkSide side;

	public:
		PlayerSocket(int fd, const sockaddr_in& address, NetworkSide side);
		PlayerSocket(PlayerSocket&&) = default;

		void connect();

		ByteBuf read();
		void write(const ByteBuf& buf);

		ssize_t readBytes(byte_t* buf, size_t size);
		void writeBytes(const byte_t* buf, size_t size);

		byte_t readByte();
		void writeByte(byte_t byte);

		int readVarint();
		void writeVarint(int v);

		NetworkSide getSide() const;

		static PlayerSocket create(const std::string& address, ushort port);

	private:
		ssize_t checkReturnCode(ssize_t ret, const std::string& msg);
	};
}
