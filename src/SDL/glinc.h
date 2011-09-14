#ifndef ___GLINC_H
#define ___GLINC_H

#ifdef HW_ENABLE_GLES

#include "../GLES/gles.h"







static GLushort gles_quad_indices[4] = { 1, 2, 0, 3 };





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
