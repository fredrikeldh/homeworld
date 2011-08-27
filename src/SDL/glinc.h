#ifndef ___GLINC_H
#define ___GLINC_H

#ifdef HW_ENABLE_GLES

#include "../GLES/gles.h"







static GLushort gles_quad_indices[4] = { 1, 2, 0, 3 };



static inline void gles_render_current(void) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(gles_vertex_dimensions, GL_FLOAT, 0, gles_vertex);
    if (gles_texcoord_count && gles_mode >= GL_TRIANGLES) {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_FLOAT, 0, gles_texcoord);
    }
    if (gles_color_count) {
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(4, GL_FLOAT, 0, gles_colors);
    }
    if (gles_normal_count && gles_mode >= GL_TRIANGLES) {
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT, 0, gles_normals);
    }
    switch (gles_mode) {
        case GL_POINTS:
        case GL_LINES:
        case GL_LINE_LOOP:
        case GL_LINE_STRIP:
        case GL_TRIANGLES:
        case GL_TRIANGLE_STRIP:
        case GL_TRIANGLE_FAN:
            glDrawArrays(gles_mode, 0, gles_vertex_count / gles_vertex_dimensions);
            break;
        case GL_QUADS:
            glDrawElements(GL_TRIANGLE_STRIP, gles_vertex_count / gles_vertex_dimensions, GL_UNSIGNED_SHORT, gles_quad_indices);
            break;
        case GL_POLYGON: {
            unsigned int i;
            GLfloat center_x = 0.0f, center_y = 0.0f;
            gles_vertex[gles_vertex_count++] = gles_vertex[0];
            gles_vertex[gles_vertex_count++] = gles_vertex[1];
            GLushort poly_indices[(gles_vertex_count / gles_vertex_dimensions) + 1];
            poly_indices[0] = gles_vertex_count / gles_vertex_dimensions;
            for (i = 0; i < gles_vertex_count / gles_vertex_dimensions; i++) {
                poly_indices[i + 1] = i;
                center_x += gles_vertex[i * 2] / (gles_vertex_count / gles_vertex_dimensions);
                center_y += gles_vertex[(i * 2) + 1] / (gles_vertex_count / gles_vertex_dimensions);
            }
            gles_vertex[gles_vertex_count++] = center_x;
            gles_vertex[gles_vertex_count++] = center_y;
            gles_vertex_data();
            glDrawElements(GL_TRIANGLE_FAN, gles_vertex_count / gles_vertex_dimensions, GL_UNSIGNED_SHORT, poly_indices);
            break;
        }
        default:
            printf("gles_render_current: unsupported mode: 0x%x\n", gles_mode);
            break;
    }
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    gles_vertex_count = 0;
    gles_texcoord_count = 0;
    if (gles_color_count) {
        gles_colors[0] = gles_colors[gles_color_count - 4];
        gles_colors[1] = gles_colors[gles_color_count - 3];
        gles_colors[2] = gles_colors[gles_color_count - 2];
        gles_colors[3] = gles_colors[gles_color_count - 1];
    }
    gles_color_count = 0;
    if (gles_normal_count) {
        gles_normals[0] = gles_normals[gles_normal_count - 3];
        gles_normals[1] = gles_normals[gles_normal_count - 2];
        gles_normals[2] = gles_normals[gles_normal_count - 1];
    }
    gles_normal_count = 0;
}

#elif defined HW_ENABLE_GLES2

#include "../GLES2/gles2.h"

#else

#include <SDL_opengl.h>

extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLBUFFERSUBDATAPROC glBufferSubData;

#endif

#ifdef HW_ENABLE_GLES2

#ifndef APIENTRY
#define APIENTRY
#endif
#ifndef APIENTRYP
#define APIENTRYP APIENTRY*
#endif

typedef void (APIENTRYP PFNGLDRAWTEXIOESPROC) (GLint x, GLint y, GLint z, GLint width, GLint height);
#else
typedef void (APIENTRYP PFNGLDRAWTEXIOESPROC) (GLint x, GLint y, GLint z, GLint width, GLint height);
#endif //HW_ENABLE_GLES2

extern PFNGLDRAWTEXIOESPROC glDrawTexiOES;

#ifndef GL_TEXTURE_CROP_RECT_OES
#define GL_TEXTURE_CROP_RECT_OES 0x8B9D
#endif

int glCheckExtension(const char *ext);

#endif
