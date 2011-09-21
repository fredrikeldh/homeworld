
#include "../gles2.h"

FogSetup::FogSetup() :
	mode(GL_EXP),
	density(1),
	start(0),
	end(1),
	index(0),
	color({0, 0, 0, 0})
{
}

template<typename T>
void FogSetup::Set(
	GLenum    pname,
 	const T*  params)
{
	GLfloat value = *params;

	switch( pname )
	{
	case GL_FOG_MODE:
		if( value == GL_LINEAR || value == GL_EXP || value == GL_EXP2 )
			mode = value;
		else
		{
			SetError(GL_INVALID_ENUM);
			return;
		}
		break;
	case GL_FOG_DENSITY:
		if( value < 0 )
		{
			SetError(GL_INVALID_VALUE);
			return;
		}
		density = value;
		break;
	case GL_FOG_START:
		start = value;
		break;
	case GL_FOG_END:
		end = value;
		break;
	case GL_FOG_INDEX:
		index = value;
		break;
	case GL_FOG_COLOR:
		Copy(params, color, sizeof(color) / sizeof(*color));
		break;
	case GL_FOG_COORD_SRC:
		if( value == GL_FOG_COORDINATE || value == GL_FRAGMENT_DEPTH )
		{
			coords = value;
		}
		break;
	default:
		SetError(GL_INVALID_ENUM);
		break;
	}
}

void glFogiv(
	GLenum        pname,
	const GLint * params
)
{
	Get<FogSetup>().Set<GLint>(pname, params);
}

void glFogi(
	GLenum        pname,
	GLint         param
)
{
	const GLint value = param;
	glFogiv(pname, &value);
}

void glFogfv(
	GLenum    pname,
 	const GLfloat*  params
)
{
	Get<FogSetup>().Set<GLfloat>(pname, params);
}

void glFogf(
	GLenum  	pname,
 	GLfloat  	param
)
{
	const GLfloat value = param;
	glFogfv(pname, &value);
}

/*
<
	GL_FOG_MODE,
	GL_FOG_DENSITY,
	GL_FOG_START,
	GL_FOG_END,
	GL_FOG_INDEX,
	GL_FOG_COLOR,
	GL_FOG_COORD_SRC>
*/
