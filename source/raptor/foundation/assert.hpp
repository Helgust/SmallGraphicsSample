#pragma once

#include "foundation/log.hpp"

namespace raptor {

    #define RASSERT( condition )      if (!(condition)) { rprint(RAPTOR_FILELINE("FALSE\n")); RAPTOR_DEBUG_BREAK }
    #define RASSERTM(condition, message, ...) \
        if (!(condition)) { \
            char buf[512]; \
            rprint(buf, sizeof(buf), "%s%s", RAPTOR_FILELINE(""), message); \
            rprint(buf, ##__VA_ARGS__); \
            RAPTOR_DEBUG_BREAK \
        }

} // namespace raptor
