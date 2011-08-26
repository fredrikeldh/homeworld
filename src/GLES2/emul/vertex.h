
#include "include.h"
#include "../../GLES1/emul/vertex.h"

namespace gles2
{
	class VertexSetup : public gles1::VertexSetup
	{
	public:
		VertexSetup();
	
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
				GLint          size,
				GLenum         type,
				GLsizei        stride,
				const GLvoid*  pointer
			);
	
			GLint         size;
			GLenum        type;
			GLsizei       stride;
			const GLvoid* pointer;
		} pointer;
	};

};

