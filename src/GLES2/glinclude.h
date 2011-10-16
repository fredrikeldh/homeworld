#ifndef _HW_GLES2_GLINCLUDE_H_
#define _HW_GLES2_GLINCLUDE_H_

#ifdef HW_USE_GLES2
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2platform.h>
#include <GLES2/gl2ext.h>
#else
#error WRONG INCLUDE
#endif //HW_USE_GLES2

#endif //_HW_GLES2_GLINCLUDE_H_

