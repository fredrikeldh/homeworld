
#include "normal.h"

NormalSetup::NormalSetup() :
	GLPart(),
	type(GL_FLOAT),
	stride(0),
	pointer(nullptr)
{
}

void NormalSetup::SetPointer(
	GLenum        type,
	GLsizei       stride,
	const GLvoid* pointer)
{
	if( stride < 0 )
	{
		glSetError(GL_INVALID_VALUE);
		return;
	}

	if( !Evaluate(type) )
		return;

	this->type    = type;
	this->stride  = stride;
	this->pointer = pointer;
}

void glNormalPointer(
	GLenum        type,
	GLsizei       stride,
	const GLvoid* pointer)
{
	Get<NormalSetup>().SetPointer(type, stride, pointer);
}

