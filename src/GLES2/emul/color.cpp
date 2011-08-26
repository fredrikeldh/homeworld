
#include "color.h"

void glColorPointer(
	GLint          size,
	GLenum         type,
	GLsizei        stride,
	const GLvoid*  pointer)
{
	Get<ColorSetup>().SetPointer(size, type, stride, pointer);
}

void glColor4ub(
	GLubyte  red,
	GLubyte  green,
	GLubyte  blue,
	GLubyte  alpha)
{
	Get<ColorSetup>().Set(red, green, blue, alpha);
}

void ColorSetup::Set(
	GLubyte  red,
	GLubyte  green,
	GLubyte  blue,
	GLubyte  alpha)
{
	Set(red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f);
}

template<typename T, T V1>
void Copy(T* target)
{
	target = V1;
}

void ColorSetup::Set(
	GLfloat  red,
	GLfloat  green,
	GLfloat  blue,
	GLfloat  alpha)
{
	current[0] = red;
	current[1] = green;
	current[2] = blue;
	current[3] = alpha;
}

ColorSetup::ColorSetup() : GLPart(), size(4), type(GL_FLOAT), stride(0), pointer(nullptr), current({1, 1, 1, 1})
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
		SetError(GL_INVALID_VALUE);
		return;
	}

	if( !Evaluate(type) )
		return;

	this->size = size;
	this->type = type;
	this->stride = stride;
	this->pointer = pointer;
}
