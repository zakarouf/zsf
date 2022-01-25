#ifndef ZAKAROUF_ZSF__MAP_CHUNKTYPE_IMPL_H
#define ZAKAROUF_ZSF__MAP_CHUNKTYPE_IMPL_H

#include "def.h"
#include <stdio.h>

void zsf_map_ch_createEmpty(
      z__u32 const x, z__u32 const y, z__u32 const z
    , z__u32 const chunkRadius
    , z__size plotsize
    , void * **chunk
    , zsf_ObjArr * *objArrs
    , z__size *chunkAndObjCount);

void zsf_map_ch_delete(
      z__size chunkAndObjCount
    , void **chunks 
    , zsf_ObjArr *objArrs);

FILE* zsf_map_ch_export_commondata(
      char const mapname[]
    , z__Vint3 chunksize);

FILE* zsf_map_ch_export_chunk(
      char const *mapname
    , z__Vint3 const Chunk_cords
    , void const *chunk
    , z__size const plotsize
    , z__Vint3 const chunksize
    , zsf_ObjArr const objectSet
    , z__bool should_writeObjects);

FILE* zsf_map_ch_load_chunk(
      const char mapname[]
    , z__Vint3 const Chunk_cords
    , z__size const plotsize
    , z__Vint3 const chunksize
    , void **chunk
    , zsf_ObjArr *objectSet);

FILE* zsf_map_ch_load_commondata(
      const char mapname[]
    , z__Vint3 *chunksize);

int zsf_map_ch_load_st(
      char const *mapname
    , z__size const plotsize
    , void ***chunk
    , z__Vint3 *chunksize
    , zsf_ObjArr **objectSet
    , z__size *objCount
    , FILE **cd_fp
    , FILE **ch_fp);

void zsf_map_ch_export_st(
      char const *mapname
    , void const *chunk
    , z__size const plotsize
    , z__Vint3 const chunksize
    , zsf_ObjArr const objectSet
    , z__bool should_writeObjects
    , FILE **cd_fp
    , FILE **ch_fp);

#define zsf_MapCh_createEmpty(map, in_x, in_y, in_z, in_r)\
    {                                               \
        (map)->chunkRadius = in_r;                  \
        zsf_map_ch_createEmpty(                     \
            in_x, in_y, in_z, (map)->chunkRadius    \
          , sizeof(**(map)->chunks)                 \
          , (void***)&(map)->chunks                 \
          , &(map)->objectSetArrs                   \
          , &(map)->chunkAndObjCount);              \
        (map)->size.x = in_x;           \
        (map)->size.y = in_y;           \
        (map)->size.z = in_z;           \
    }

#define zsf_MapCh_delete(map)\
    zsf_map_ch_delete((map)->chunks, (map)->objectSetArrs, (map)->chunkAndObjCount)


#define zsf_MapCh_load_st(map, name)\
    {\
        FILE *_map_ch_lod_st_cd, *_map_ch_lod_st_ch;    \
        zsf_map_ch_load_st(                             \
                  name                                  \
                , sizeof(**(map)->chunks)               \
                , (void***)&(map)->chunks               \
                , &(map)->size                          \
                , &(map)->objectSetArrs                 \
                , &(map)->chunkAndObjCount              \
                , &_map_ch_lod_st_ch                    \
                , &_map_ch_lod_st_cd);                  \
        fclose(_map_ch_lod_st_ch); fclose(_map_ch_lod_st_cd); \
    }

#define zsf_MapCh_load_st_fp(map, name, ch, cd)\
    {\
        zsf_map_ch_load_st(                     \
                  name                          \
                , sizeof(**(map)->chunks)       \
                , (void***)&(map)->chunks       \
                , &(map)->size                  \
                , &(map)->objectSetArrs         \
                , &(map)->chunkAndObjCount      \
                , &cd                           \
                , &ch);                         \
    }


#define zsf_MapCh_export_st(map, name, chunkno, shouldwriteObjects)\
    {                                                    \
        FILE *_map_ch_exp_st_cd, *_map_ch_exp_st_ch;    \
        z__typeof(chunkno) _map_ch_exp_st_chN = chunkno;\
        if(_map_ch_exp_st_chN < (map)->chunkAndObjCount){   \
            zsf_map_ch_export_st(                           \
                  name                                      \
                , (map)->chunks[_map_ch_exp_st_chN]         \
                , sizeof(**(map)->chunks)                   \
                , (map)->size                               \
                , (map)->objectSetArrs[_map_ch_exp_st_chN]  \
                , shouldwriteObjects                        \
                , &_map_ch_exp_st_cd                        \
                , &_map_ch_exp_st_ch);                      \
            fclose(_map_ch_exp_st_cd);                      \
            fclose(_map_ch_exp_st_ch);                      \
        }                                                   \
    }

#define zsf_MapCh_export_st_fp(map, name, chunkno, shouldwriteObjects, ch, cd)\
    {                                                   \
        z__typeof(chunkno) _map_ch_exp_st = chunkno;    \
        if(chunkno < (map)->chunkCount{                 \
            zse_map_ch_export_st__raw(                  \
                  name                                  \
                , (map)->chunks[chunkno]                \
                , sizeof(**(map)->chunks)               \
                , (map)->size                           \
                , (map)->objectSetArrs[_map_ch_exp_st]  \
                , shouldwriteObjects                    \
                , &cd                                   \
                , &ch);                                 \
        }                                               \
    }

#define zsf_MapCh_export_commondata_fp(map, name, fp)\
    {                                                                                            \
        *(fp) = zsf_map_ch_export_commondata(name, (map)->size);    \
    }

#define zsf_MapCh_export_chunk_fp(name, cord, map, chnum, should_writeObjects, fp)\
    {                                           \
        *(fp) = zsf_map_ch_export_chunk(        \
                  name                          \
                , cord                          \
                , (map)->chunks[chnum]          \
                , sizeof(**(map)->chunks)       \
                , (map)->size                   \
                , (map)->objectSetArrs[chnum]   \
                , should_writeObjects);         \
    }


#define zsf_MapCh_export_commondata(name, map)\
    {                                                           \
        fclose(zsf_map_ch_export_commondata(name, (map)->size));\
    }

#define zsf_MapCh_export_chunk(name, cord, map, chnum, should_writeObjects)\
    {                                           \
        fclose(zsf_map_ch_export_chunk(         \
                  name                          \
                , cord                          \
                , (map)->chunks[chnum]          \
                , sizeof(**(map)->chunks)       \
                , (map)->size                   \
                , (map)->objectSetArrs[chnum]   \
                , should_writeObjects));        \
    }

#define zsf_MapCh_load_commondata_fp(name, map, fp)\
  {                                         \
        (*fp) = zsf_map_ch_load_commondata( \
                    name,                   \
                    &(map)->size            \
                );                          \
  }

#define zse_MapCh_load_chunk_fp(name, cords, map, chnum, fp)\
  {                                         \
      (*fp) = zsf_map_ch_load_chunk(        \
              name                          \
              , cords                       \
              , sizeof(**(map)->chunks)     \
              , (map)->size                 \
              , &(map)->chunks[chnum]       \
              , &(map)->objectSetArrs[chnum]);    \
  }


#endif // ZAKAROUF_ZSF__MAP_CHUNKTYPE_H

