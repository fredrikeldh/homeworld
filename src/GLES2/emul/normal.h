
#include "include.h"

class NormalSetup : public GLPart<
	GL_BYTE,
	GL_SHORT,
	GL_INT,
	GL_FLOAT,
	GL_DOUBLE
>
{
public:
	NormalSetup();
	void SetPointer(
		GLenum        type,
		GLsizei       stride,
		const GLvoid* pointer);
	GLenum        type;
	GLsizei       stride;
	const GLvoid* pointer;
};

