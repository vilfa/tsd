#pragma once

#include <limits>
#include <memory>
#include <mutex>

#include "defs.h"
#if defined(OS_WINDOWS)
    #include <WinSock2.h>
    #undef min
    #undef max
#endif  // OS_WINDOWS

#include "os/util.h"

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
    WSADATA m_wsa_data;
};
#endif  // OS_WINDOWS

class Socket {
   public:
    Socket()
        : m_id(os::random<uint32_t>(std::numeric_limits<uint32_t>::min(),
                                    std::numeric_limits<uint32_t>::max())) {}

   protected:
    const uint32_t m_id;
    // virtual void poll() = 0;
    // virtual void shutdown() = 0;
};
}  // namespace net
}  // namespace tsd