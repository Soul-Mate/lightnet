#ifndef LIBNET_INET_ADDRESS_H
#define LIBNET_INET_ADDRESS_H

#include "lightnet_copyable.h"
#include <netdb.h> // gethostbyname_r
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <exception>
#include <string>
#include <vector>
#include <errno.h>
#include <cstring>

class InetAddressException : public std::exception
{
    virtual char const *what() const noexcept { return strerror(errno); };
};

class InetAddress : copyable
{
public:
    InetAddress();

    ~InetAddress() = default;

    explicit InetAddress(const std::string &ip, in_port_t port) throw();

    explicit InetAddress(in_port_t port, bool loopback);

    explicit InetAddress(const sockaddr_in &addr);

    InetAddress(const InetAddress &rhs); // copy constructor

    InetAddress &operator=(const InetAddress &rhs); // assign copy constructor

    InetAddress(InetAddress &&rhs); // move constructor

    InetAddress &operator=(InetAddress &&rhs); // assign move constructor

    bool reslove(const std::string &host);

    std::string toIP() const;

    std::string toEndpoint() const;

    inline const sockaddr_in &getSockAddr() const { return sockAddr_; };

    inline sockaddr_in *getSockAddrPtr() { return &sockAddr_; }

private:
    bool resloveERANGE(const std::string &host);

private:
    sockaddr_in sockAddr_;
};

#endif /* LIBNET_INET_ADDRESS_H */