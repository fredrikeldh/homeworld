#include "../gles2.h"
#include "texture.h"

void glTexCoordPointer(
	GLint          size,
	GLenum         type,
	GLsizei        stride,
	const GLvoid*  pointer
)
{
	Get<TextureSetup>().SetCoords(size, type, stride, pointer);
}

void glTexEnvi(
	GLenum target,
	GLenum pname,
	GLint param
)
{
	Get<TextureSetup>().SetEnvironment(target, pname, param);
}

TextureSetup::TextureSetup() :
	gles1::TextureSetup(),
	pointer()
{
}

TextureSetup::Pointer::Pointer() :
	GLPart(),
	size(4),
	type(GL_FLOAT),
	stride(0),
	pointer(nullptr)
{
}

void TextureSetup::Pointer::Set(
	GLubyte        size,
	GLenum         type,
	GLsizei        stride,
	const GLvoid*  pointer
)
{
	if( size < 1 || size > 4 )
	{
		SetError(GL_INVALID_VALUE);
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

void TextureSetup::Pointer::ApplyTo(IRenderState* renderer)
{
	//TODO: Implement
}

void TextureSetup::Environment::Set(
	GLenum target,
	GLenum pname,
	GLint param
)
{
	if
	(
		!Evaluate
		<
			GL_TEXTURE_ENV,
			GL_TEXTURE_FILTER_CONTROL,
			GL_POINT_SPRITE
		>(target)
	)
		return;

	if( !Evaluate<
		GL_TEXTURE_ENV_MODE, GL_TEXTURE_LOD_BIAS, GL_COMBINE_RGB,
		GL_COMBINE_ALPHA   , GL_SRC0_RGB        , GL_SRC1_RGB,
		GL_SRC2_RGB        , GL_SRC0_ALPHA      , GL_SRC1_ALPHA,
		GL_SRC2_ALPHA      , GL_OPERAND0_RGB    , GL_OPERAND1_RGB,
		GL_OPERAND2_RGB    , GL_OPERAND0_ALPHA  , GL_OPERAND1_ALPHA,
		GL_OPERAND2_ALPHA  , GL_RGB_SCALE       , GL_ALPHA_SCALE   ,
		GL_COORD_REPLACE
		>(pname) )
		return;


	//TODO: Evaluate
	this->target = target;
	this->pname = pname;
	this->param = param;
}

void TextureSetup::SetCoords(
	GLubyte        size,
	GLenum         type,
	GLsizei        stride,
	const GLvoid*  pointer
)
{
	//Set(size, type, stride, pointer);
	//TODO: Implement
}

TextureSetup::Environment::Environment()
{
}

void TextureSetup::Environment::ApplyTo(IRenderState* renderer)
{
	//TODO: Implement
}

void TextureSetup::SetEnvironment(
	GLenum target,
	GLenum pname,
	GLint param
)
{
	//TODO: Implement
}
