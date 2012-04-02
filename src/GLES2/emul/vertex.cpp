
#include "../gles2.h"
#include "vertex.h"

void glVertexPointer(
	GLint          size,
	GLenum         type,
	GLsizei        stride,
	const GLvoid*  pointer)
{
	Get<VertexSetup>().SetPointer(size, type, stride, pointer);
}

VertexSetup::VertexSetup() :
	gles1::VertexSetup(),
	pointer()
{
}

void VertexSetup::SetPointer(
	GLint          size,
	GLenum         type,
	GLsizei        stride,
	const GLvoid*  pointer
)
{
	this->pointer.Set(size, type, stride, pointer);
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

	if
	(
		!Evaluate
		<
			GL_SHORT,
			GL_INT,
			GL_FLOAT,
			GL_DOUBLE
		>(type)
	)
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

void VertexSetup::Pointer::ApplyTo(IRenderState*) {
	//todo
}
