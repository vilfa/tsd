#pragma once

#include <codecvt>
#include <string>

#include "defs.h"
#include "types.h"
#if defined(OS_WINDOWS)
    #include <process.h>
    #include <windows.h>
#elif defined(OS_UNIX)
    #include <unistd.h>
#endif

namespace tsd {
namespace os {

extern const char* cmd_;

static inline std::string hostname() {
#if defined(OS_WINDOWS)
    DWORD siz = MAX_COMPUTERNAME_LENGTH + 1;
    char buf[MAX_COMPUTERNAME_LENGTH + 1];
    if (!GetComputerNameA(buf, &siz)) {
        return std::string();
    }
    return std::string(buf);
#elif defined(OS_UNIX)
    constexpr size_t siz = 255;
    char buf[siz];
    if (gethostname(buf, siz)) {
        return std::string();
    }
    buf[siz - 1] = '\0';
    return std::string(buf);
#endif
}

static inline std::string process() { return std::string(cmd_); }

static inline pid_t pid() {
#if defined(OS_WINDOWS)
    return _getpid();
#elif defined(OS_UNIX)
    return getpid();
#endif
}

static inline std::wstring s2ws(const std::string& str) {
    using convert_t = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_t, wchar_t> conv;
    return conv.from_bytes(str);
}

static inline std::string ws2s(const std::wstring& wstr) {
    using convert_t = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_t, wchar_t> conv;
    return conv.to_bytes(wstr);
}

static inline std::string error() {
#if defined(OS_WINDOWS)
    wchar_t buf[256];
    FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                   NULL, GetLastError(),
                   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf,
                   (sizeof(buf) / sizeof(wchar_t)), NULL);
    return ws2s(std::wstring(buf));
#elif defined(OS_UNIX)
    // TODO
#endif  // OS_WINDOWS
}
}  // namespace os
}  // namespace tsd
