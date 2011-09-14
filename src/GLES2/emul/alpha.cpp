
#include "alpha.h"

void AlphaSetup::SetFunc(
	GLenum    func,
	GLclampf  ref)
{
	if
	(
		!Evaluate<
			GL_NEVER,
			GL_LESS,
			GL_EQUAL,
			GL_LEQUAL,
			GL_GREATER,
			GL_NOTEQUAL,
			GL_GEQUAL,
			GL_ALWAYS
		>(func)
	)
		return;
	
	this->func = func;
	this->ref  = clamp(ref, 0.0f, 1.0f);
}

void glAlphaFunc(
	GLenum    func,
	GLclampf  ref)
{
	Get<AlphaSetup>().SetFunc(func, ref);
}

AlphaSetup::AlphaSetup() : GLPart(), func(GL_ALWAYS), ref(0)
{
}




