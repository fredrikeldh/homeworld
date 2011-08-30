
#ifndef _HW_GLES2_POINT_H_
#define _HW_GLES2_POINT_H_

#include "include.h"

class PointSetup : public GLPart<
>
{
public:
	PointSetup();
	void SetSize(GLfloat  size);
	GLfloat point_size;
};

#endif //_HW_GLES2_POINT_H_

