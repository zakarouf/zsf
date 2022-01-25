#ifndef ZAKAROUF_ZSF__MAP_RAWOBJECTS_IMPL_H
#define ZAKAROUF_ZSF__MAP_RAWOBJECTS_IMPL_H

#include "def.h"

void zsf_ObjArr_new(zsf_ObjArr *objarr, z__size sz);
void zsf_ObjArr_delete(zsf_ObjArr *objarr);

z__Dynt* zsf_ObjArr_push(zsf_ObjArr *objarr, z__u32 typeID, z__size unitsize, z__size len, void *data, int commentLen, const char *comment);
void zsf_ObjArr_pop(zsf_ObjArr *objarr);

#endif

