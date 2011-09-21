#ifndef ___GLINC_H
#define ___GLINC_H

#ifdef HW_USE_GLES
#include "../GLES/glinclude.h"
#elif defined HW_USE_GL
#include <SDL_opengl.h>

extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLBUFFERSUBDATAPROC glBufferSubData;

#endif

//
// Make sure defines are present
//

#ifndef APIENTRY
#define APIENTRY
#endif

#ifndef APIENTRYP
#define APIENTRYP APIENTRY*
#endif

typedef void (APIENTRYP PFNGLDRAWTEXIOESPROC) (GLint x, GLint y, GLint z, GLint width, GLint height);

extern PFNGLDRAWTEXIOESPROC glDrawTexiOES;

#ifndef GL_TEXTURE_CROP_RECT_OES
#define GL_TEXTURE_CROP_RECT_OES 0x8B9D
#endif

int glCheckExtension(const char *ext);

#endif //___GLINC_H
