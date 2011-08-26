
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
		const T*  params
	);
		
	void Set(
		GLenum          light,
		GLenum          pname,
		const GLfloat*  params
	);
	GLfloat ambient[4];
	GLenum color_control;
	bool local_viewer;
	bool two_sided;
	
	class Light
	{
	public:
		Light();
		GLfloat ambient[4];
		GLfloat diffuse[4];
		GLfloat specular[4];
		GLfloat position[4];
		GLfloat direction[3];
		GLfloat spot_exponent;
		GLfloat spot_cutoff;
		GLfloat attenuations[3];
	};
	Light lights[GL_MAX_LIGHTS];
};

#endif //_HW_GLES2_LIGHT_H_

