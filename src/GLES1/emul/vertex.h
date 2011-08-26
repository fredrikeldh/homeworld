
#ifndef _HW_GLES1_VERTEX_H_
#define _HW_GLES1_VERTEX_H_

#include "include.h"

namespace gles1
{
	class VertexSetup : public GLPart<
	>
	{
	public:
		VertexSetup();
		GLfloat vertex[16384];
		GLuint count;
		unsigned char dimensions;
	};
};

#endif //_HW_GLES1_VERTEX_H_

