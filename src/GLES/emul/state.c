
#include "gles.h"

static unsigned int gles_immediate = 0;
static GLenum gles_mode;

static inline void glBegin(GLenum mode) {
    gles_immediate = 1;
    gles_mode = mode;
}

static inline void glEnd(void) {
    if (gles_vertex_count) gles_render_current();
    gles_immediate = 0;
}
