#ifndef _HW_GLES2_INCLUDE_H_
#define _HW_GLES2_INCLUDE_H_

#include "../../GLES/glinclude.h"
#include "../../GLES/include.h"

#ifndef _HW_NAMESPACE_
#define _HW_NAMESPACE_
#ifdef __cplusplus
// Need to declare gles2 before using it
namespace gles2
{
	enum dummy{};
}

using namespace gles2;
#endif //__cplusplus
#endif //_HW_NAMESPACE_

#ifdef __cplusplus
	#include "uniform.h"
#endif //__cplusplus

#endif //_HW_GLES2_INCLUDE_H_

