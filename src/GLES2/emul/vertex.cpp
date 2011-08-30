
#include "vertex.h"

void glVertexPointer(
	GLint          size,
	GLenum         type,
	GLsizei        stride,
	const GLvoid*  pointer)
{
	Get<VertexSetup>().pointer.Set(size, type, stride, pointer);
}

VertexSetup::VertexSetup() :
	gles1::VertexSetup(),
	pointer()
{
}

void VertexSetup::Pointer::Set(
	GLint          size,
	GLenum         type,
	GLsizei        stride,
	const GLvoid*  pointer
)
{
	if( size < 2 || size > 4 || stride < 0)
	{
		SetError<GL_INVALID_VALUE>();
		return;
	}
	
	if( !Evaluate(type) )
		return;
	
	this->size = size;
	this->type = type;
	this->stride = stride;
	this->pointer = pointer;
}

VertexSetup::Pointer::Pointer() :
	GLPart(),
	size(4),
	type(GL_FLOAT),
	stride(0),
	pointer(nullptr)
{
}
