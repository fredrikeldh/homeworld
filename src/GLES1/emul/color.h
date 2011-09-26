#ifndef _HW_GLES1_COLOR_H_
#define _HW_GLES1_COLOR_H_

#include "include.h"
#include "array.h"

namespace gles1
{
	class ColorSetup : public GLPart
	{
	public:
		ColorSetup();
		
		void SetCurrent(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
		void GetCurrent(GLfloat* buffer);
	private:
		Array<GLfloat, 4> _current;
	};
};

#endif //_HW_GLES1_COLOR_H_

