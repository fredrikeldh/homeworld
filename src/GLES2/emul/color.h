
#ifndef _HW_GLES2_COLOR_H_
#define _HW_GLES2_COLOR_H_

#include "include.h"

class ColorSetup : public GLPart
{
public:
	ColorSetup();
	void SetPointer(
		GLint          size,
		GLenum         type,
		GLsizei        stride,
		const GLvoid*  pointer
	);
	void Set(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void Set(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
private:
	friend class RENDER_PROCESSOR;
	GLint size;
	GLenum type;
	GLsizei stride;
	const GLvoid* pointer;
	GLfloat current[4];
};

#endif //_HW_GLES2_COLOR_H_

