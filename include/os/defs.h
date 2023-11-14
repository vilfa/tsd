#pragma once

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    #define OS_IS_WINDOWS
#endif

#if defined(unix) || defined(__unix) || defined(__unix__)
    #define OS_IS_UNIX
#endif

#if defined(linux) || defined(__linux) || defined(__linux__)
    #define OS_IS_LINUX
    #ifndef OS_IS_UNIX
        #define OS_IS_UNIX
    #endif
#endif

#if defined(__APPLE__) || defined(__MACH__)
    #define OS_IS_MACOS
    #ifndef OS_IS_UNIX
        #define OS_IS_UNIX
    #endif
    #ifndef OS_IS_BSD
        #define OS_IS_BSD
    #endif
#endif
