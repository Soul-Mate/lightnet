#ifndef LIBNET_SOCKET_H
#define LIBNET_SOCKET_H

#include <sys/socket.h>
#include <errno.h>
#include "lightnet_copyable.h"
#include "lightnet_inet_address.h"

class SocketCreateException : public std::exception
{
    virtual const char *what() noexcept
    {
        return strerror(errno);
    }
};

class Socket : nocopyable
{

public:
    Socket(int domain, int type, int protocol);

    explicit Socket(int sockfd) noexcept : sockFd_(sockfd){};

    Socket(Socket &&that); // move constructor

    Socket &operator=(Socket &&that); // move assign constructor

    ~Socket();

    inline const int &get_sockfd() const { return sockFd_; };

    int setRefuse();

    int bind(const InetAddress &addr);

    int listen(int backlog);

    int connect(const InetAddress &serverAddr);

    int recv(void *buf, size_t len);

    int send(const void *buf, size_t len);

    int recvFrom(void *buf, size_t len, InetAddress &addr);

    int sendTo(const void *buf, size_t len, const InetAddress &addr);

    int shutdownWrite();

    static Socket TCP(); // ipv4 only

    static Socket UDP(); // ipv4 only

private:
    int sockFd_;
};

#endif /* LIBNET_SOCKET_H */