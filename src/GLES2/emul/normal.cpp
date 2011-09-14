
#include "normal.h"

NormalSetup::NormalSetup() :
	gles1::NormalSetup(),
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
		SetError<GL_INVALID_VALUE>();
		return;
	}

	if
	(
		!Evaluate<
			GL_BYTE,
			GL_SHORT,
			GL_INT,
			GL_FLOAT,
			GL_DOUBLE
		>(type)
	)
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

