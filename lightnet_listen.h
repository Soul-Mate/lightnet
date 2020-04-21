#ifndef LIGHTNET_LISTEN_H
#define LIGHTNET_LISTEN_H

#include "lightnet_socket.h"
#include "lightnet_tcp_stream.h"
#include "lightnet_inet_address.h"
#include "lightnet_copyable.h"

class Listen : nocopyable
{
public:
    Listen(Socket &&socket);

    ~Listen() = default;

    int listenTCP(const InetAddress &serverAddr);

    std::unique_ptr<TcpStream> acceptTCP();

    int listenUDP(const InetAddress &serverAddr);

    int readFrom(void *buf, size_t len, InetAddress &remoteAddrRet);

    int writeTo(void *buf, size_t len, const InetAddress &remoteAddr);

private:
    Socket sock_;
};

#endif /*LIGHTNET_LISTEN_H*/