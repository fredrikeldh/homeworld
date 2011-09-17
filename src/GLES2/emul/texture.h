
#ifndef _HW_GLES2_TEXTURE_H_
#define _HW_GLES2_TEXTURE_H_

#include "include.h"
#include "../../GLES1/emul/texture.h"

class TextureSetup : public gles1::TextureSetup
{
public:
	TextureSetup();
	void Set(
		GLubyte        size,
		GLenum         type,
		GLsizei        stride,
		const GLvoid*  pointer
	);
	
	void SetCoords(
		GLubyte        size,
		GLenum         type,
		GLsizei        stride,
		const GLvoid*  pointer
	);
	
	void SetEnvironment(
		GLenum target,
		GLenum pname,
		GLint param
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
		
		virtual void ApplyTo(IRenderState* renderer);
	private:
		friend class TextureSetup;
		friend class RENDER_PROCESSOR;
		GLubyte        size;
		GLenum         type;
		GLsizei        stride;
		const GLvoid*  pointer;
	};
	
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
		
		virtual void ApplyTo(IRenderState* renderer);
	private:
		friend class TextureSetup;
		friend class RENDER_PROCESSOR;
		GLenum target;
		GLenum pname;
		GLint param;
	};
	
private:
	friend class RENDER_PROCESSOR;
	Pointer pointer;
	Environment environment;
};
#endif //_HW_GLES2_TEXTURE_H_

