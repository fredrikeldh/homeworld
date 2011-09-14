#ifndef _HW_GLES1_GLINCLUDE_H_
#define _HW_GLES1_GLINCLUDE_H_

#ifndef HW_IGNORE_GL_INCLUDE
#include <GLES/egl.h>
#include <GLES/glext.h>

#ifdef __cplusplus
// Need to declare gles1 before using it
namespace gles1
{
}

using namespace gles1;
#endif //__cplusplus

#endif //HW_IGNORE_GL_INCLUDE

#endif //_HW_GLES1_GLINCLUDE_H_

