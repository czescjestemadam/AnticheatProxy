#pragma once
#include <netinet/in.h>
#include <string>

namespace acp
{
	class ISocket
	{
	protected:
		int fd;
		sockaddr_in address;

	public:
		ISocket(int fd, const sockaddr_in& address);
		virtual ~ISocket() = default;

		void close();

		bool isValid() const;

		int getFd() const;
		const sockaddr_in& getAddr() const;

		std::string getAddrStr() const;


		bool operator==(const ISocket& rhs) const;
		bool operator!=(const ISocket& rhs) const;
	};
}
