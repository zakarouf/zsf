#ifndef ZAKAROUF_ZSF__MAP_CHUNKTYPE_DEFINATIONS_H
#define ZAKAROUF_ZSF__MAP_CHUNKTYPE_DEFINATIONS_H

#include "../../obj/def.h"
#include <z_/types/vector.h>

/* Main Header For Chunk Defination. */

/* Pre-requisite:
 * 1. We Are Assuming that the Chunks Are always laid in Square Formation, No Circle or Renctangle
 * 2. The Player Chunk; The Chunk the player is on, is always in the middle in the formation
 * 3. Side of our square formation is always a odd number.
 * 4. The Total Count of the Chunks will be determined by a `Radius` from the Player going outwards in each direction.
 */

/*  . . . . . 
 *  . . . . . <- Each . is a chunk of (ChunkSizeXY * ChunkSizeXY) * ChunkSizeZ
 *  . . @ . .  - @ is the chunk inhabitate by the player
 *  . . . . .  - Chunk Size is 2 here
 *  . . . . . 
 *
 *   /---------/
 *      . . .
 *      . @ . <- Chunk No. Size = 1 (DEFAULT) _MaxChunk
 *      . . .
 *
 *   /---------/
 *
 *    . . . . . . .
 *    . . . . . . .
 *    . . . . . . .
 *    . . . @ . . . 	<- Radius Set to 3, Side = 7, Total = 7*7 = 49
 *    . . . . . . .
 *    . . . . . . .
 *    . . . . . . .
 *
 */

/*
 *    Chunk Side Length Increase by 2 per Radius :-
 *        3, 5, 7, 9
 *        ^  ^  ^  ^
 *        1, 2, 3, 4 
 *        
 *        Chunkside(r) = (1 + 2*r)
 *
 *    And The Total Number of Chunk Will Always be square of side:
 *
 *		Chunks(r) = Chunkside(r)^2 
 *
 *    /-----------------------------------------/
 *  Chunk Mid Point :-
 *      1 5 13 
 *
 *      ChunksMid(r) = (int)( (float)(Chunks(r)/2) + 0.5f )
 *
 *  Chunk lastline First Point :-
 *
 */

/*    Chunks File Naming Scheme :-
 *		Cx,Cy,Cz.bin
 *		|  |  |
 *		|  |  |- `z` Chunk z cordinate
 *		|  |- `y` Chunk y cordinate
 *		|- `x` Chunk x cordinate
 *
 *      #EXECUTABLE DIR
 *        |- maps
 *          |- #MAP NAME
 *            |- MAP_COMMON_DATA  <== Stores Map size, attributes et cetera.
 *            |- CHUNK CORD (eg. 1,1,1.bin
 *                               -1,1,0.bin)
 *
 *
 */

/*------------------------------------------------------------------------------*/
/*---------------------------------------Types----------------------------------*/


/*----------MapType------------*/

/**
 * zsf_MapCh()
 * Tileset Oriented Map Type with layers or z-dimention. and Multiple Chunks.
 * size: Dimention of Each Chunk.
 * chunkCount: Total no. of chunks allocated.
 * chunkRadius: Radius of square-grid layout of chunks.
 */
#define zsf_MapCh(T, ...)\
    struct {                                                            \
        /* Map Size in x, y, z  */                                      \
        z__Vint3 size;                                                  \
                                                                        \
        /* Total no. chunks allocated */                                \
        z__size chunkAndObjCount;                                       \
        /*Radius of square-grid layout of chunks. f(n) = ceil(2/n) - 1*/\
        z__u16 chunkRadius;                                             \
                                                                        \
        /**
         * Main Data Stream
         * * Of each point of 4D array normalized to 2D array (3D each)
         * * The actual way it is being internalized is Described obove although
         *   anyone is free change it.
         */                                                             \
        T **chunks;                                                     \
                                                                        \
        /**
         * Misc Map Objects.
         * Can Contain: 
         *  * Entities,
         *  * Non Static Tile Objects,
         *  * Anything Else.
         * NOTE: This does not parse any any data, Only stores them for later use.
         * NOTE: objectSet[chunk][obj];
         * NOTE: Objects of the same type are stored side-by-side.
         */                                                                 \
        zsf_ObjArr *objectSetArrs;                                          \
                                                                            \
        /**
         * Extra Stuff Declared later on (Optional)
         * NOTE Initialization & Deletion of any heap data of the vars declared
         *      here is upto the one who declared it in the first place as this module
         *      can't predict the declaration beforehand.
         */                                                         \
        __VA_ARGS__;                                                \
    }

#define zsf_xyz1D(x, y, z, X, Y)\
    ((x) + ((y) * (X)) + ((z) * (X) * (Y)))

#define zsf_MapCh_getc(map, ix, iy, iz, cx, cy, cz)\
    (map)->chunks[\
        zsf_xyz1D(cx, cy, cy, (map)->chunkRadius, (map)->chunkCount)]\
            [zsf_xyz1D(ix, iy, iz, (map)->size.x, (map)->size.y)]

#define zsf_MapCh_getcr(map, ix, iy, iz, c)\
    (map)->chunks[c]\
            [zsf_xyz1D(ix, iy, iz, (map)->size.x, (map)->size.y)]

#define zsf_MapCh_get_chunk_side_fromRad(map) (1 + (2 * (map)->chunkRadius))

#define zsf_MapCh_get_chunk_count_fromRad(map)\
      zsf_MapCh_get_chunk_side_fromRad(map)\
    * zsf_MapCh_get_chunk_side_fromRad(map)

#define zsf_MapCh_get_chunk_mid_fromRad(map)\
    (z__u32)(\
        ((z__float)zsf_MapCh_get_chunk_count_fromRad(map) /2.0f) - 0.5f\
    )

#define zsf_square_side_from_rad(rad) (1 + (2 * (rad)))

#define zsf_square_area_from_rad(rad)\
      zsf_square_side_from_rad(rad)\
    * zsf_square_side_from_rad(rad)

#define zsf_square_mid_from_rad(rad)\
    (z__u32)(\
        ((z__float)zsf_square_area_from_rad(rad) /2.0f) - 0.5f\
    )


#endif // ZAKAROUF_ZSF__MAP_CHUNKTYPE_DEFINATIONS_H

