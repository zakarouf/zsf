#ifndef ZAKAROUF_ZSF__LOG_H
#define ZAKAROUF_ZSF__LOG_H

#include <z_/imp/sys.h>

#define zsf_logprint(b, f, fmt, ...) z__log_cl256_full(b, f, fmt "\n" ,##__VA_ARGS__)
#define zsf_logfprint(file, b, f, fmt, ...) z__logfile_cl256_full(file, b, f, fmt ,##__VA_ARGS__)


#endif

