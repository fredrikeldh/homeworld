
#ifndef _HW_GLES_IUNIFORMVALUE_H_
#define _HW_GLES_IUNIFORMVALUE_H_

#include "include.h"
#include <vector>

template<typename T, GLubyte SIZE>
class IUniformValue
{
protected:
	GLint location;

	IUniformValue(GLint location):
		location(location)
	{
	}
public:
	virtual void Set(const T* values) = 0;
	virtual void Set(const std::vector<T>& values) = 0;
};
	
#endif //_HW_GLES_IUNIFORMVALUE_H_

