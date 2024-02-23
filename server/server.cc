#include "server.h"

#include "net/sock.h"
#include "net/tcp.h"
#include "os/util.h"

int main(int argc, char** argv) {
    tsd::os::cmd_ = argv[0];
    spdlog::set_level(spdlog::level::trace);
    spdlog::info("{} is starting [{}/{}]", tsd::os::process(),
                 tsd::os::hostname(), tsd::os::pid());

    const tsd::net::WinSock& winsock = tsd::net::WinSock::instance();
    tsd::net::TCPSocket sock;
    sock.start();

    spdlog::info("{} is exiting [{}/{}]", tsd::os::process(),
                 tsd::os::hostname(), tsd::os::pid());
    return 0;
}
