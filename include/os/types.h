#pragma once

#include <stdint.h>

#include "defs.h"

#ifdef OS_IS_WINDOWS
namespace tsd {
namespace os {
using pid_t = int32_t;
}
}
#endif
