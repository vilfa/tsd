#pragma once

#include <memory>
#include <mutex>

#include "defs.h"
#if defined(OS_WINDOWS)
    #include <winsock.h>
#endif  // OS_WINDOWS

namespace tsd {
namespace net {
#if defined(OS_WINDOWS)
class WinSock {
   public:
    static const WinSock& instance();

    WinSock(const WinSock&) = delete;
    WinSock& operator=(const WinSock&) = delete;
    WinSock(WinSock&&) = delete;
    WinSock& operator=(WinSock&&) = delete;

   protected:
    WinSock();
    ~WinSock();

   private:
    static std::mutex m_mutex;
    WSADATA m_wsaData;
};
#endif  // OS_WINDOWS

class Socket {
    virtual ~Socket() {}

    virtual void poll() = 0;
    virtual void shutdown() = 0;
};
}  // namespace net
}  // namespace tsd