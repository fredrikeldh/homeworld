
#ifndef _HW_GLES2_COLOR_H_
#define _HW_GLES2_COLOR_H_

#include "include.h"

class ColorSetup : public GLPart
{
public:
	ColorSetup();
private:
	friend class RENDER_PROCESSOR;
	GLint size;
	GLenum type;
	GLsizei stride;
	const GLvoid* pointer;
};

#endif //_HW_GLES2_COLOR_H_

