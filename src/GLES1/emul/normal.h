#ifndef _HW_GLES1_NORMAL_H_
#define _HW_GLES1_NORMAL_H_

#include "include.h"
#include "array.h"

namespace gles1
{
	class NormalSetup : public GLPart
	{
	public:
		NormalSetup();
		void GetCurrent(GLfloat*);
		void SetCurrent(GLfloat x, GLfloat y, GLfloat z);
	private:
		Array<GLfloat,3> _current;
	};
};

#endif //_HW_GLES1_NORMAL_H_

