#ifndef _HW_GLES2_ALPHA_H_
#define _HW_GLES2_ALPHA_H_

#include "include.h"

class AlphaSetup : public GLPart<GL_NEVER,
	GL_LESS,
	GL_EQUAL,
	GL_LEQUAL,
	GL_GREATER,
	GL_NOTEQUAL,
	GL_GEQUAL,
	GL_ALWAYS>
{
private:
	AlphaSetup();
public:
	void SetFunc(
		GLenum    func,
		GLclampf  ref);
	GLenum   func;
	GLclampf ref;
};

#endif //_HW_GLES2_ALPHA_H_
