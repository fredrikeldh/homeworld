
#ifndef _HW_GLES2_COLOR_H_
#define _HW_GLES2_COLOR_H_

#include "include.h"

class ColorSetup : public GLPart<
	GL_BYTE,
	GL_UNSIGNED_BYTE,
	GL_SHORT,
	GL_UNSIGNED_SHORT,
	GL_INT,
	GL_UNSIGNED_INT,
	GL_FLOAT,
	GL_DOUBLE>
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
	GLint size;
	GLenum type;
	GLsizei stride;
	const GLvoid* pointer;
	GLfloat current[4];
};

#endif //_HW_GLES2_COLOR_H_

