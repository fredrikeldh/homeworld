
#include "gles.h"

static GLfloat gles_vertex[16384];
static unsigned int gles_vertex_count = 0;
static unsigned char gles_vertex_dimensions = 2;

static inline void gles_vertex_data(void) {
    if (!gles_normal_count) gles_normal_count = 3;
    while (gles_normal_count / 3 < gles_vertex_count / gles_vertex_dimensions) {
        gles_normals[gles_normal_count] = gles_normals[gles_normal_count - 3];
        gles_normal_count++;
        gles_normals[gles_normal_count] = gles_normals[gles_normal_count - 3];
        gles_normal_count++;
        gles_normals[gles_normal_count] = gles_normals[gles_normal_count - 3];
        gles_normal_count++;
    }
    if (!gles_color_count) gles_color_count = 4;
    while (gles_color_count / 4 < gles_vertex_count / gles_vertex_dimensions) {
        gles_colors[gles_color_count] = gles_colors[gles_color_count - 4];
        gles_color_count++;
        gles_colors[gles_color_count] = gles_colors[gles_color_count - 4];
        gles_color_count++;
        gles_colors[gles_color_count] = gles_colors[gles_color_count - 4];
        gles_color_count++;
        gles_colors[gles_color_count] = gles_colors[gles_color_count - 4];
        gles_color_count++;
    }
}

static inline void glVertex2f(GLfloat x, GLfloat y) {
    if (gles_mode == GL_QUADS && gles_vertex_dimensions && gles_vertex_count / gles_vertex_dimensions == 4) gles_render_current();
    gles_vertex_dimensions = 2;
    gles_vertex[gles_vertex_count++] = x;
    gles_vertex[gles_vertex_count++] = y;
    gles_vertex_data();
}

static inline void glVertex3f(GLfloat x, GLfloat y, GLfloat z) {
    if (gles_mode == GL_QUADS && gles_vertex_dimensions && gles_vertex_count / gles_vertex_dimensions == 4) gles_render_current();
    gles_vertex_dimensions = 3;
    gles_vertex[gles_vertex_count++] = x;
    gles_vertex[gles_vertex_count++] = y;
    gles_vertex[gles_vertex_count++] = z;
    gles_vertex_data();
}

static inline void glVertex3fv(const GLfloat *v) {
    glVertex3f(v[0], v[1], v[2]);
}
