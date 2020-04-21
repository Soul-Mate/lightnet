#include "lightnet_listen.h"

Listen::Listen(Socket &&socket)
    : sock_(std::move(socket))
{
}

int Listen::listenTCP(const InetAddress &serverAddr)
{
    int ret = sock_.setRefuse();
    if (ret == -1)
    {
        return ret;
    }

    ret = sock_.bind(serverAddr);
    if (ret == -1)
    {
        return ret;
    }

    return sock_.listen(128);
}

std::unique_ptr<TcpStream> Listen::acceptTCP()
{
    InetAddress peer;
    socklen_t peerLen;
    int peerfd = ::accept(sock_.get_sockfd(), (sockaddr *)peer.getSockAddrPtr(), &peerLen);
    if (peerfd == -1)
    {
        return nullptr;
    }

    return std::unique_ptr<TcpStream>(new TcpStream(Socket(peerfd), std::move(peer)));
}

int Listen::listenUDP(const InetAddress &serverAddr)
{
    int ret = sock_.setRefuse();
    if (ret == -1)
    {
        return ret;
    }

    return sock_.bind(serverAddr);
}

int Listen::readFrom(void *buf, size_t len, InetAddress &remoteAddrRet)
{
    return sock_.recvFrom(buf, len, remoteAddrRet);
}

int Listen::writeTo(void *buf, size_t len, const InetAddress &remoteAddr)
{
    return sock_.sendTo(buf, len, remoteAddr);
}
