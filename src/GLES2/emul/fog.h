
#ifndef _HW_GLES2_FOG_H_
#define _HW_GLES2_FOG_H_

#include "include.h"

class FogSetup : public GLPart<
	GL_FOG_MODE,
	GL_FOG_DENSITY,
	GL_FOG_START,
	GL_FOG_END,
	GL_FOG_INDEX,
	GL_FOG_COLOR,
	GL_FOG_COORD_SRC>
{
public:
	FogSetup();
	template<typename T>
	void Set(
		GLenum    pname,
		const T*  params
	);
private:
	friend class RENDER_PROCESSOR;
	GLenum mode;
	GLfloat density;
	GLfloat start;
	GLfloat end;
	GLfloat index;
	GLfloat color[4];
	GLfloat coords;
};

#endif //_HW_GLES2_FOG_H_

