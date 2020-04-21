#include "lightnet_socket.h"
#include <iostream>
#include <algorithm>
Socket::Socket(int domain, int type, int protocol)
{
    sockFd_ = ::socket(domain, type, protocol);
    if (sockFd_ == -1)
    {
        throw SocketCreateException();
    }
}

Socket::Socket(Socket &&that)
{
#ifdef DEBUG
    std::cout << "move constructor for Socket" << std::endl;
#endif
    sockFd_ = that.sockFd_;
    that.sockFd_ = -1;
}

Socket &Socket::operator=(Socket &&that)
{
#ifdef DEBUG
    std::cout << "move assign operator for Socket" << std::endl;
#endif
    if (this == &that)
    {
        return *this;
    }

    this->sockFd_ = that.sockFd_;
    that.sockFd_ = -1;
    return *this;
}

Socket::~Socket()
{
#ifdef DEBUG
    std::cout << "Socket::~Socket closed sockfd" << std::endl;
#endif
    close(sockFd_);
}

int Socket::setRefuse()
{
#ifdef DEBUG
    std::cout << "set SO_REFUSEADDR with Socket" << std::endl;
#endif
    int refuse = 1;
    return ::setsockopt(sockFd_, SOL_SOCKET, SO_REUSEADDR, &refuse, sizeof refuse);
}

int Socket::bind(const InetAddress &addr)
{
#ifdef DEBUG
    std::cout << "Socket::bind" << std::endl;
#endif
    auto saddr = addr.getSockAddr();
    return ::bind(sockFd_, (const sockaddr *)&saddr, sizeof saddr);
}

int Socket::listen(int backlog)
{
#ifdef DEBUG
    std::cout << "Socket::listen" << std::endl;
#endif
    return ::listen(sockFd_, backlog);
}

int Socket::connect(const InetAddress &serverAddr)
{
    return ::connect(sockFd_, (const struct sockaddr *)&serverAddr.getSockAddr(), sizeof serverAddr.getSockAddr());
}

Socket Socket::TCP()
{
#ifdef DEBUG
    std::cout << "Socket::createTCP" << std::endl;
#endif
    return Socket(AF_INET, SOCK_STREAM, 0);
}

Socket Socket::UDP()
{
#ifdef DEBUG
    std::cout << "Socket::createUDP" << std::endl;
#endif
    return Socket(AF_INET, SOCK_DGRAM, 0);
}

int Socket::recv(void *buf, size_t len)
{
    return ::recv(sockFd_, buf, len, 0);
}

int Socket::send(const void *buf, size_t len)
{
    return ::send(sockFd_, buf, len, 0);
}

int Socket::recvFrom(void *buf, size_t len, InetAddress &addr)
{
    struct sockaddr_in *addrPtr = addr.getSockAddrPtr();
    socklen_t addrLen = sizeof *addrPtr;
    return recvfrom(sockFd_, buf, len, 0,
                    (struct sockaddr *)addrPtr, &addrLen);
}

int Socket::sendTo(const void *buf, size_t len, const InetAddress &addr)
{
    return sendto(sockFd_, buf, len, 0,
                  (const struct sockaddr *)(&addr.getSockAddr()), sizeof addr.getSockAddr());
}

int Socket::shutdownWrite()
{
    return shutdown(sockFd_, SHUT_WR);
}
