#include <stdio.h>
#include <stdlib.h>
#include <z_/types/mem.h>
#include <z_/imp/ansi.h>
#include <z_/types/string.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#include "impl.h"

zsf_Term *zsf_Term_newDefault(z__u32 width, z__u32 height)
{
    zsf_Term *t = z__MALLOC(sizeof(*t));

    t->pixels = z__MALLOC(sizeof(*t->pixels) * width * height);
    t->height = height;
    t->width = width;
        
    char tmp[32] = {0};
    t->colors_fg = z__StringList_new(1);
    t->colors_bg = z__StringList_new(1);
    for (size_t i = 0; i < 256; i++) {
        sprintf(tmp, z__ansi_fmt((cl256_fg, %li)), i-1l);
        z__StringList_push(&t->colors_fg, tmp, 32);

        sprintf(tmp, z__ansi_fmt((cl256_bg, %li)), i-1l);
        z__StringList_push(&t->colors_bg, tmp, 32);
    }

    t->outbuffer_size = (t->height * t->width * sizeof(tmp)) * 2;
    t->outbuffer = z__MALLOC(sizeof(*t->outbuffer) * t->outbuffer_size);

    zsf_TermPixel *p = t->pixels;
    for (size_t i = 0; i < t->width * (t->height); i++) {
        p->ch = ' ';
        p->color_fg = 0;
        p->color_bg = 0;
        p += 1;
    }

    return t;
}

void zsf_Term_resetScr(void)
{
    fputs(z__ansi_fmt((plain)), stdout);
    fputs(z__ansi_scr((jump), (clear)), stdout);
}

void zsf_Term_jumpBack(void)
{
    fputs(z__ansi_scr((jump)), stdout);
}

void zsf_Term_flush(zsf_Term *t)
{
//    setvbuf(stdout, t->outbuffer, _IOFBF, t->outbuffer_size);
    char **cof = t->colors_fg.str_list;
    char **cob = t->colors_bg.str_list;
    zsf_TermPixel *p = t->pixels;
    for (size_t i = 0; i < t->height; i++) {
        for (size_t j = 0; j < t->width; j++, p += 1) {
            fputs(cob[p->color_bg], stdout);
            fputs(cof[p->color_fg], stdout);
            fputc(p->ch, stdout);
        }
        fputc('\n', stdout);
    }
    fflush(stdout);
}

void zsf_Term_draw_line_sth(zsf_Term *t, z__u32 y, z__u32 x0, z__u32 x1, zsf_TermPixel pixel)
{
    if(y > t->height) return;
    
    zsf_TermPixel *i   = &zsf_Term_getPixel(t, MAX(MIN(x0, x1), 0), y)
                , *end = &zsf_Term_getPixel(t, MIN(MAX(x1, x0), t->width), y);

    for (; i < end; i++) *i = pixel;
}

void zsf_Term_draw_line_stv(zsf_Term *t, z__u32 x, z__u32 y0, z__u32 y1, zsf_TermPixel pixel)
{
    if(x > t->width) return;

    zsf_TermPixel *i   = &zsf_Term_getPixel(t, x, MAX(MIN(y0, y1), 0))
                , *end = &zsf_Term_getPixel(t, x, MIN(MAX(y1, y0), t->width));

    for (; i < end; i += t->width) *i = pixel;
}


void zsf_Term_draw_rec(zsf_Term *t, z__u32 x0, z__u32 y0, z__u32 x1, z__u32 y1, zsf_TermPixel pixel)
{
    if(y0 > t->height || x0 > t->width) return;

    z__u32 tmp_x1 = x1;
    x1 = MIN(x1, t->width);

    zsf_TermPixel *i = &zsf_Term_getPixel(t, x0, y0),
                  *endi = &zsf_Term_getPixel(t, x1, y0);
    
    // draw top horizontal line
    for (; i < endi; i += 1) *i = pixel;

    /* draw bottom horizontal line */
    if(y1 > t->width) {
        y1 = t->width-1;
    } else {
        i = &zsf_Term_getPixel(t, x0, y1);
        endi = &zsf_Term_getPixel(t, x1, y1);
        for(; i < endi; i++) *i = pixel;
    }

    // draw vertical lines
    i = &zsf_Term_getPixel(t, x0, y0+1);
    endi = &zsf_Term_getPixel(t, x0, y1);
    for(; i < endi; i += t->width) *i = pixel;

    if(tmp_x1 < t->width) {
        i = &zsf_Term_getPixel(t, x1, y0);
        endi = &zsf_Term_getPixel(t, x1, y1+1);
        for(; i < endi; i += t->width) *i = pixel;
    }
}

void zsf_Term_draw_text(zsf_Term *t, z__u32 x, z__u32 y,  const char *txt, z__size len)
{
    if(y > t->height || x > t->width) return;
    if(len > t->width) len = t->width;

    zsf_TermPixel *i = &zsf_Term_getPixel(t, x, y)
                , *end = i + len;

    for(; i < end; i++, txt++) i->ch = *txt;
}

void zsf_Term_draw_fill(zsf_Term *t, zsf_TermPixel pixel)
{
    zsf_TermPixel *i = &zsf_Term_getPixel(t, 0, 0)
                , *end = i + (t->width * t->height);
    for(; i < end; i++) *i = pixel;
         
}

void zsf_Term_draw_fill_char(zsf_Term *t, char c)
{
    z__u8 *i = &zsf_Term_getPixel(t, 0, 0).ch;
    z__u8 *end = (t->height * t->width * sizeof(*t->pixels)) + i;
    for (; i < end; i += sizeof(*t->pixels)) *i = c;
}

void zsf_Term_clear(zsf_Term *t)
{
    zsf_Term_draw_fill(t, (zsf_TermPixel){.ch = ' ', 0, 0, 0});
}

#if 0
void zsf_Term_draw_line(zsf_Term *t, z__u32 x0, z__u32 y0, z__u32 x1, z__u32 y1, zsf_TermPixel pixel)
{
    
}

#endif

