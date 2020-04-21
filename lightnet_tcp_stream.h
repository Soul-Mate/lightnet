#ifndef LIGHTNET_TCP_STREAM_H
#define LIGHTNET_TCP_STREAM_H

#include "lightnet_copyable.h"
#include "lightnet_socket.h"
#include <memory>
class TcpStream : nocopyable
{
public:
    explicit TcpStream(Socket &&socket); // move constructor

    explicit TcpStream(Socket &&socket, InetAddress &&peerInetAddr); // move constructor

    int receiveAll(void *buf, size_t len);

    int sendAll(const void *buf, size_t len);

    int receiveSome(void *buf, size_t len);

    void shutdownWrite();

private:
    Socket __sock;
};

std::unique_ptr<TcpStream> Connect(const InetAddress &serverAddr);

#endif /*LIGHTNET_TCP_STREAM_H*/