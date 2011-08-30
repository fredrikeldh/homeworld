
#ifndef _HW_GLES2_TEXTURE_H_
#define _HW_GLES2_TEXTURE_H_

#include "include.h"

class TextureSetup : public GLPart<
>
{
public:
	TextureSetup();
	void Set(
		GLubyte        size,
		GLenum         type,
		GLsizei        stride,
		const GLvoid*  pointer
	);
	
	class Pointer : public GLPart<
		GL_SHORT,
		GL_INT,
		GL_FLOAT,
		GL_DOUBLE
	>
	{
	public:
		Pointer();
		void Set(
			GLubyte        size,
			GLenum         type,
			GLsizei        stride,
			const GLvoid*  pointer
		);
		GLubyte        size;
		GLenum         type;
		GLsizei        stride;
		const GLvoid*  pointer;
	} pointer;
	
	class Environment : public GLPart<
		GL_TEXTURE_ENV,
		GL_TEXTURE_FILTER_CONTROL,
		GL_POINT_SPRITE
	>
	{
	public:
		Environment();
		void Set(
			GLenum target,
			GLenum pname,
			GLint param
		);
		
		GLenum target;
		GLenum pname;
		GLint param;
	} environment;
};
#endif //_HW_GLES2_TEXTURE_H_

