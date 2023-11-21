#pragma once

#include "os/defs.h"

#if defined(OS_WINDOWS)
    #include <WinSock2.h>
#endif

#include "sock.h"

namespace tsd {
namespace net {
class TCPSocket : public Socket {
   public:
    TCPSocket(const uint16_t& port = 8080);
    ~TCPSocket();

   private:
    uint16_t m_port;
    struct addrinfo* m_addr_info;
    SOCKET m_socket;
};
}  // namespace net
}  // namespace tsd
