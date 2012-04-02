#ifndef _HW_GLES1_INCLUDE_H_
#define _HW_GLES1_INCLUDE_H_


#include "../../GLES/include.h"

#ifndef _HW_NAMESPACE_
#define _HW_NAMESPACE_
#ifdef __cplusplus
// Need to declare gles1 before using it
namespace gles1
{
	enum dummy{};
}

template<typename T>
T& Get()
{
	return *new T();
}

using namespace gles1;
#endif //__cplusplus
#endif //_HW_NAMESPACE_

#endif //_HW_GLES1_INCLUDE_H_
