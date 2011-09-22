
#ifndef _HW_GLES1_TEXTURE_H_
#define _HW_GLES1_TEXTURE_H_

#include "include.h"
#include "array.h"

namespace gles1
{
	class TextureSetup : public GLPart
	{
	public:
		TextureSetup();
		void SetCoord(GLfloat s, GLfloat t);
		void GetCoord(GLfloat*);
	private:
		Array<GLfloat, 2> _current;
	};
}

#endif //_HW_GLES1_TEXTURE_H_

