
#ifndef _HW_GLES2_LIGHT_H_
#define _HW_GLES2_LIGHT_H_

#include "include.h"

class LightSetup : public GLPart<
	GL_LIGHT_MODEL_AMBIENT,
	GL_LIGHT_MODEL_COLOR_CONTROL,
	GL_LIGHT_MODEL_LOCAL_VIEWER,
	GL_LIGHT_MODEL_TWO_SIDE>
{
public:
	LightSetup();
	template<typename T>
	void Set(
		GLenum    pname,
		const T*  params);
	GLfloat ambient[4];
	GLenum color_control;
	bool local_viewer;
	bool two_sided;
};

#endif //_HW_GLES2_LIGHT_H_

