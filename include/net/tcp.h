#pragma once

#include "sock.h"

namespace tsd {
namespace net {
class TCPSocket : public Socket {
    TCPSocket();
    ~TCPSocket();
};
}  // namespace net
}  // namespace tsd
