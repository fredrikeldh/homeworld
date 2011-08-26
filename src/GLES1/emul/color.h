#ifndef _HW_GLES1_COLOR_H_
#define _HW_GLES1_COLOR_H_

#include "include.h"

namespace glew1
{
	class ColorSetup : public GLPart<
	>
	{
	public:
		ColorSetup();
		GLfloat colors[16384];
		GLuint color_count;
	};
};

#endif //_HW_GLES1_COLOR_H_
