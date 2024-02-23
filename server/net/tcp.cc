#include "net/tcp.h"

#if defined(OS_WINDOWS)
    #include <WS2tcpip.h>
    #include <WinSock2.h>
#endif

#include <string>

#include "os/util.h"
#include "spdlog/spdlog.h"

using namespace tsd::net;

TCPSocket::TCPSocket(const uint16_t& port /*= 8080*/)
#if defined(OS_WINDOWS)
    : Socket(port), m_addr_info(nullptr), m_socket(INVALID_SOCKET) {
    struct addrinfo addr_hint = {0};
    addr_hint.ai_family = AF_INET;
    addr_hint.ai_socktype = SOCK_STREAM;
    addr_hint.ai_protocol = IPPROTO_TCP;
    addr_hint.ai_flags = AI_PASSIVE;
    if (int e_ = getaddrinfo(NULL, std::to_string(port).c_str(), &addr_hint,
                             &m_addr_info)) {
        spdlog::error("failed to init tcp socket: {}", os::error());
        std::exit(e_);
    }
    m_socket = socket(addr_hint.ai_family, addr_hint.ai_socktype,
                      addr_hint.ai_protocol);
    if (m_socket == INVALID_SOCKET) {
        spdlog::error("failed to init tcp socket: {}", os::error());
        std::exit(1);
    }
    spdlog::debug("initialized tcp socket: {}", m_id);
#elif defined(OS_UNIX)
#endif
}

TCPSocket::~TCPSocket() { shutdown(); }

void TCPSocket::start() {
    if (m_done) {
        spdlog::error("cannot start closed socket: {}", m_id);
        std::exit(1);
    }
    if (bind(m_socket, m_addr_info->ai_addr, (int)m_addr_info->ai_addrlen) ==
        SOCKET_ERROR) {
        m_done = true;
        closesocket(m_socket);
        spdlog::error("error starting socket: {}, {}", m_id, os::error());
    }
    spdlog::debug("started tcp socket: {}", m_id);
}

void TCPSocket::shutdown() {
    if (m_done) {
    
    }
    m_done = true;
    closesocket(m_socket);
    spdlog::info("shutdown tcp socket: {}", m_id);
}