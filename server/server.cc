#include "server.h"

#include "net/sock.h"
#include "os/util.h"

int main(int argc, char** argv) {
    tsd::os::cmd_ = argv[0];
    spdlog::info("{} is starting [{}/{}]", tsd::os::process(),
                 tsd::os::hostname(), tsd::os::pid());

    auto& sock = tsd::net::WinSock::instance();

    spdlog::info("{} is exiting [{}/{}]", tsd::os::process(),
                 tsd::os::hostname(), tsd::os::pid());
    return 0;
}
