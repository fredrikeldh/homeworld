
#include "../gles2.h"

LightSetup::LightSetup() : 
	ambient({0.2, 0.2, 0.2, 1.0}),
	color_control(GL_SINGLE_COLOR),
	local_viewer(false),
	two_sided(false)
{
}

template<typename T>
void LightSetup::Set(
	GLenum          pname,
	const T*  params)
{
	if( !Evaluate(pname) )
		return;
		
	switch( pname )
	{
	case GL_LIGHT_MODEL_AMBIENT:
		Copy(params, ambient, 4);
		break;
	case GL_LIGHT_MODEL_COLOR_CONTROL:
	{
		GLint value = *params;
		if( value != GL_SINGLE_COLOR && value != GL_SEPARATE_SPECULAR_COLOR )
		{
			glSetError(GL_INVALID_ENUM);
			break;
		}
		color_control = value;
		break;
	}
	case GL_LIGHT_MODEL_LOCAL_VIEWER:
		local_viewer = (*params != 0.0);
		break;
	case GL_LIGHT_MODEL_TWO_SIDE:
		two_sided = (*params != 0.0);
		break;
	}
}

void glLightModelfv(
	GLenum          pname,
	const GLfloat*  params)
{
	Get<LightSetup>().Set(pname, params);

}

void glLightModelf(
	GLenum   pname,
	GLfloat  param)
{
	const GLfloat value = param;
	glLightModelfv(pname, &value);
}



