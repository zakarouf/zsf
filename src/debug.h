#ifndef ZAKAROUF_ZSF__DEBUG_H
#define ZAKAROUF_ZSF__DEBUG_H

#include "log.h"

#if HW_DEBUG == 1
    #define zsf_DP(b, f, fmt, ...) zsf_logprint(b, f, "DEBUG:: " fmt "\n" ,##__VA_ARGS__)
    #define zsf_DEBUG_CHECK(...) __VA_ARGS__
#else 
    #define zsf_DP(b, f, fmt, ...)
    #define zsf_DEBUG_CHECK(...)
#endif

#endif

