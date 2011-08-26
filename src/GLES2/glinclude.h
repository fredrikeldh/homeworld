#ifndef _HW_GLES2_GLINCLUDE_H_
#define _HW_GLES2_GLINCLUDE_H_

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2platform.h>
#include <GLES2/gl2ext.h>

#ifdef __cplusplus
// Need to declare gles2 before using it
namespace gles2
{
	int dummy;
}

using namespace gles2;
#endif //__cplusplus

#endif //_HW_GLES2_GLINCLUDE_H_

