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

WinSock::WinSock() : m_wsa_data() {
    if (int e_ = WSAStartup(MAKEWORD(2, 2), &m_wsa_data)) {
        spdlog::error("failed to initialize winsock: {}", os::error());
        exit(e_);
    }
    spdlog::info("initialized winsock");
}

WinSock::~WinSock() {
    if (int e_ = WSACleanup()) {
        spdlog::error("failed to clean up winsock: {}", os::error());
    }
    spdlog::info("cleaned up winsock");
}
#endif  // OS_WINDOWS
