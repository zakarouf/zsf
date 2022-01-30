#ifndef ZAKAROUF_ZSF__TERM_DEF_H
#define ZAKAROUF_ZSF__TERM_DEF_H

#include <z_/types/base.h>
#include <z_/types/string.h>

typedef union zsf_TermPixel {
    struct {
        z__u8 ch, color_fg, color_bg, attr;
    };
    z__u32 raw;
}zsf_TermPixel;

typedef struct zsf_Term {
    zsf_TermPixel *pixels; 
    char *outbuffer;
    z__size outbuffer_size;
    z__u32 width, height;
    z__StringList colors_bg;
    z__StringList colors_fg;
} zsf_Term;


#define zsf_xy1D(x, y, X) ((x) + ((y) * (X)))

#define zsf_Term_setchar(t, x, y, c)\
    (t)->pixels[zsf_xy1D(x, y, t->width)].ch = c

#define zsf_Term_setcolor(t, x, y, f, b){\
        (t)->pixels[zsf_xy1D(x, y, t->width)].color_fg = f;\
        (t)->pixels[zsf_xy1D(x, y, t->width)].color_bg = b;\
    }

#define zsf_Term_getPixel(t, x, y) (t->pixels[zsf_xy1D(x, y, t->width)])

#endif

