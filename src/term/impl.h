#ifndef ZAKAROUF_ZSF__TERM_IMPL_H
#define ZAKAROUF_ZSF__TERM_IMPL_H

#include "def.h"

zsf_Term *zsf_Term_newDefault(z__u32 width, z__u32 height);
void zsf_Term_flush(zsf_Term *t);

void zsf_Term_resetScr(void);
void zsf_Term_jumpBack(void);

void zsf_Term_draw_line_sth(zsf_Term *t, z__u32 y, z__u32 x0, z__u32 x1, zsf_TermPixel pixel);
void zsf_Term_draw_line_stv(zsf_Term *t, z__u32 x, z__u32 y0, z__u32 y1, zsf_TermPixel pixel);

void zsf_Term_draw_rec(zsf_Term *t, z__u32 x0, z__u32 y0, z__u32 x1, z__u32 y1, zsf_TermPixel pixel);

void zsf_Term_draw_text(zsf_Term *t, z__u32 x, z__u32 y,  const char *txt, z__size len);
void zsf_Term_draw_fill(zsf_Term *t, zsf_TermPixel pixel);
void zsf_Term_draw_fill_char(zsf_Term *t, char c);
void zsf_Term_clear(zsf_Term *t);

#endif

