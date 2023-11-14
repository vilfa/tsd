#pragma once

#include <string>

#include "defs.h"
#include "types.h"

#if defined(OS_IS_WINDOWS)
    #include <process.h>
    #include <windows.h>
#elif defined(OS_IS_UNIX)
    #include <unistd.h>
#endif

namespace tsd {
namespace os {

extern const char* cmd_;

static inline std::string
hostname()
{
#if defined(OS_IS_WINDOWS)
    DWORD siz = MAX_COMPUTERNAME_LENGTH + 1;
    char buf[MAX_COMPUTERNAME_LENGTH + 1];
    if (!GetComputerNameA(buf, &siz)) {
        return std::string();
    }
    return std::string(buf);
#elif defined(OS_IS_UNIX)
    constexpr size_t siz = 255;
    char buf[siz];
    if (gethostname(buf, siz)) {
        return std::string();
    }
    buf[siz - 1] = '\0';
    return std::string(buf);
#endif
}

static inline std::string
process()
{
    return std::string(cmd_);
}

static inline pid_t
pid()
{
#if defined(OS_IS_WINDOWS)
    return _getpid();
#elif defined(OS_IS_UNIX)
    return getpid();
#endif
}

}
}
