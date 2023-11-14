#pragma once

#include <stdint.h>

#include "defs.h"

#if defined(OS_WINDOWS)
namespace tsd {
namespace os {
using pid_t = int32_t;
}  // namespace os
}  // namespace tsd
#endif
