#include <stdlib.h>
#include <z_/types/dynt.h>
#include "impl.h"

void zsf_ObjArr_new(zsf_ObjArr *objarr, z__size sz)
{
    z__Arr_new(objarr, sz);
}

z__Dynt* zsf_ObjArr_push(zsf_ObjArr *objarr, z__u32 typeID, z__size unitsize, z__size len, void *data, int commentLen, const char *comment)
{
    z__Arr_pushInc(objarr);
    z__Arr_getTop((*objarr)) = z__Dynt_new(unitsize, len, typeID, comment, commentLen);
    z__Dynt_push(&z__Arr_getTop((*objarr)), data);
    return &z__Arr_getTop((*objarr));
}

void zsf_ObjArr_pop(zsf_ObjArr *objarr)
{
    if(objarr->lenUsed <= 0) return;
    z__Dynt_delete(&z__Arr_getTop((*objarr)));
    objarr->lenUsed -= 1;
}

void zsf_ObjArr_delete(zsf_ObjArr *objarr)
{
    size_t len = z__Arr_getUsed((*objarr));
    if(objarr->len <= 0) return;
    for (size_t i = 0; i < len; i++) {
        z__Dynt *_tmp = &z__Arr_getVal((*objarr), i);
        if(_tmp->len > 0) {
            z__Dynt_delete(_tmp);
        }
    }
    z__Arr_delete(objarr);
}

