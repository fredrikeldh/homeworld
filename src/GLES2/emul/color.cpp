
#include "color.h"

void glColorPointer(
	GLint          size,
	GLenum         type,
	GLsizei        stride,
	const GLvoid*  pointer)
{
	Get<ColorSetup>().SetPointer(size, type, stride, pointer);
}

template<typename T, T V1>
void Copy(T* target)
{
	target = V1;
}

ColorSetup::ColorSetup() : gles1::ColorSetup(), size(4), type(GL_FLOAT), stride(0), pointer(nullptr)
{
}

void ColorSetup::SetPointer(
	GLint          size,
	GLenum         type,
	GLsizei        stride,
	const GLvoid*  pointer
)
{
	if( (size != 3 && size != 4) || stride < 0 )
	{
		SetError<GL_INVALID_VALUE>();
		return;
	}

	if
	(
		!Evaluate
		<
			GL_BYTE,
			GL_UNSIGNED_BYTE,
			GL_SHORT,
			GL_UNSIGNED_SHORT,
			GL_INT,
			GL_UNSIGNED_INT,
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
