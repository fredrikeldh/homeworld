#ifndef _HW_GLES2_INCLUDE_H_
#define _HW_GLES2_INCLUDE_H_

#include "../glinclude.h"

// Make sure to include this file before also including
// across GLES versions
#define HW_IGNORE_GL_INCLUDE

#include "defines.h"
#include "declarations.h"
#include "../../GLES/include.h"
#ifdef __cplusplus
#include "../../GLES/GLPart.h"
#include "../../GLES/uniform.h"
#endif //__cplusplus

#endif //_HW_GLES2_INCLUDE_H_

