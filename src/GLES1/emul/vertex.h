
#ifndef _HW_GLES1_VERTEX_H_
#define _HW_GLES1_VERTEX_H_

#include "include.h"

namespace gles1
{
	class VertexSetup : public GLPart<>
	{
	public:
		VertexSetup();
		void Set(GLfloat x, GLfloat y, GLfloat z);
	private:
		
		unsigned int _count;
		// 3
		GLfloat _vertices[16384];
		// 4
		GLfloat _colors[16384];
		
		// 3
		GLfloat _normals[16384];
	};
};

#endif //_HW_GLES1_VERTEX_H_

