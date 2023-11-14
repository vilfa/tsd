#include "net/sock.h"

#include <cstdlib>

#include "os/util.h"
#include "spdlog/spdlog.h"

#if defined(OS_WINDOWS)
    #include <winsock.h>
#endif  // OS_WINDOWS

using namespace tsd::net;

std::mutex WinSock::m_mutex;

#if defined(OS_WINDOWS)
const WinSock& WinSock::instance() {
    std::lock_guard lock(m_mutex);
    static const WinSock instance_;
    return instance_;
}

WinSock::WinSock() : m_wsaData() {
    if (WSAStartup(MAKEWORD(2, 2), &m_wsaData)) {
        spdlog::error("failed to initialize winsock: {}", os::error());
    }
    spdlog::info("successfully initialized winsock");
}

WinSock::~WinSock() {}
#endif  // OS_WINDOWS
