
#ifndef _HW_GLES1_VERTEX_H_
#define _HW_GLES1_VERTEX_H_

#include "include.h"
#include "array.h"

namespace gles1
{
	class VertexSetup : public GLPart
	{
	public:
		VertexSetup();
		void Set(GLfloat x, GLfloat y, GLfloat z);
	private:
		friend class RenderPipe;
		unsigned int _count;
		unsigned int _vertex_dimensions;
		
		// 3
		Array<GLfloat, 16384> _vertices;
		// 4
		Array<GLfloat, 16384> _colors;
		
		// 3
		Array<GLfloat, 16384> _normals;
		
		Array<GLfloat, 16384> _texCoords;
		
		Array<GLfloat, 16384> _fogCoords;
	};
};

#endif //_HW_GLES1_VERTEX_H_

