#include "player_socket.hh"
#include "exception/socket_exception.hh"
#include "exception/socket_close_exception.hh"

#include <cstring>
#include <arpa/inet.h>
#include <netinet/tcp.h>

acp::PlayerSocket::PlayerSocket(int fd, const sockaddr_in& address, NetworkSide side) : ISocket(fd, address), side(side)
{
	constexpr int v = 1;
	setsockopt(fd, SOL_TCP, TCP_NODELAY, &v, sizeof(v));

	constexpr int v3 = 3;
	if (side == NetworkSide::CLIENT)
		setsockopt(fd, SOL_TCP, TCP_FASTOPEN, &v3, sizeof(v3));
	else
		setsockopt(fd, SOL_TCP, TCP_FASTOPEN_CONNECT, &v, sizeof(v));
}

void acp::PlayerSocket::connect()
{
	if (::connect(fd, reinterpret_cast<sockaddr*>(&address), sizeof(address)))
		throw SocketException(std::string("connect: ") + strerror(errno), this);
}

acp::ByteBuf acp::PlayerSocket::read()
{
	const size_t len = readVarint();
	byte_t buf[len];
	readBytes(buf, len);
	return { buf, len };
}

void acp::PlayerSocket::write(const ByteBuf& buf)
{
	writeVarint(static_cast<int>(buf.size()));
	writeBytes(buf.data(), buf.size());
}

ssize_t acp::PlayerSocket::readBytes(byte_t* buf, size_t size)
{
	return checkReturnCode(recv(fd, buf, size, MSG_WAITALL), "readBytes");
}

void acp::PlayerSocket::writeBytes(const byte_t* buf, size_t size)
{
	checkReturnCode(send(fd, buf, size, MSG_NOSIGNAL), "writeBytes");
}

byte_t acp::PlayerSocket::readByte()
{
	byte_t byte;
	readBytes(&byte, 1);
	return byte;
}

void acp::PlayerSocket::writeByte(byte_t byte)
{
	writeBytes(&byte, 1);
}

int acp::PlayerSocket::readVarint()
{
	int val = 0;
	int pos = 0;
	byte_t cur;

	while (true)
	{
		cur = readByte();
		val |= (cur & 0x7f) << pos;

		if ((cur & 0x80) == 0)
			break;

		pos += 7;

		if (pos >= 32)
			throw SocketException("Varint too big", this);
	}

	return val;
}

void acp::PlayerSocket::writeVarint(int v)
{
	while (true)
	{
		if ((v & ~0x7f) == 0)
		{
			writeByte(byte_t(v));
			return;
		}
		writeByte(byte_t((v & 0x7f) | 0x80));
		v = uint(v) >> 7;
	}
}

acp::NetworkSide acp::PlayerSocket::getSide() const
{
	return side;
}


acp::PlayerSocket acp::PlayerSocket::create(const std::string& address, ushort port)
{
	const int fd = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in addr{};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(address.c_str());
	addr.sin_port = htons(port);

	return { fd, addr, NetworkSide::DEST };
}


ssize_t acp::PlayerSocket::checkReturnCode(ssize_t ret, const std::string& msg)
{
	if (ret < 0)
		throw SocketException(msg + ": " + strerror(errno), this);
	if (ret == 0)
		throw SocketCloseException(this);

	return ret;
}
