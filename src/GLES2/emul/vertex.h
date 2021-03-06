
#ifndef _HW_GLES2_VERTEX_H_
#define _HW_GLES2_VERTEX_H_

#include "include.h"
#include "../../GLES1/emul/vertex.h"

namespace gles2
{
	class VertexSetup : public gles1::VertexSetup
	{
	public:
		VertexSetup();
		
		void SetPointer(
			GLint          size,
			GLenum         type,
			GLsizei        stride,
			const GLvoid*  pointer
		);
	private:
	
		class Pointer : public GLPart
		{
		public:
			Pointer();
			void Set(
				GLint          size,
				GLenum         type,
				GLsizei        stride,
				const GLvoid*  pointer
			);
			
			virtual void ApplyTo(IRenderState*);
		private:
	
			GLint         size;
			GLenum        type;
			GLsizei       stride;
			const GLvoid* pointer;
		} pointer;
	};

};

#endif //_HW_GLES2_VERTEX_H_

