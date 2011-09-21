
#ifndef _HW_GLES1_TEXTURE_H_
#define _HW_GLES1_TEXTURE_H_

#include "include.h"

namespace gles1
{
	class TextureSetup : public GLPart
	{
	public:
		TextureSetup();
	private:
		friend class RENDER_PROCESSOR;
		GLfloat texcoord[16384];
		GLuint texcoord_count;
	};
}

#endif //_HW_GLES1_TEXTURE_H_

