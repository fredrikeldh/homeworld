
#include "light.h"

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
			SetError<GL_INVALID_ENUM>();
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

void glLightfv(
	GLenum          light,
	GLenum          pname,
	const GLfloat*  params)
{
	Get<LightSetup>().Set(light, pname, params);
}

void LightSetup::Set(
	GLenum          lightEnum,
	GLenum          pname,
	const GLfloat*  params
)
{
	if(
		!Evaluate<
			GL_LIGHT0,
			GL_LIGHT1,
			GL_LIGHT2,
			GL_LIGHT3,
			GL_LIGHT4,
			GL_LIGHT5,
			GL_LIGHT6,
			GL_LIGHT7
		>(lightEnum)
	)
		return;
	
	Light& light = lights[lightEnum - GL_LIGHT0];
		
	switch( pname )
	{
	case GL_AMBIENT:
		Copy(params, light.ambient, 4);
		break;
	case GL_DIFFUSE:
		Copy(params, light.diffuse, 4);
		break;
	case GL_SPECULAR:
		Copy(params, light.specular, 4);
		break;
	case GL_POSITION:
		Copy(params, light.position, 4);
		break;
	case GL_SPOT_DIRECTION:
		Copy(params, light.direction, 3);
		break;
	case GL_SPOT_EXPONENT:
	{
		const GLfloat value = *params;
		if( value < 0 || value > 128 )
		{
			SetError(GL_INVALID_VALUE);
			break;
		}
		
		light.spot_exponent = value;
		break;
	}
	case GL_SPOT_CUTOFF:
	{
		const GLfloat value = *params;
		if( (value < 0 || value > 90) && (value != 180) )
		{
			SetError(GL_INVALID_VALUE);
			break;
		}
		
		light.spot_cutoff = value;
		break;
	}
	case GL_CONSTANT_ATTENUATION:
	{
		const GLfloat value = *params;
		if( value < 0 )
		{
			SetError(GL_INVALID_VALUE);
			break;
		}
		
		light.attenuations[0] = value;
		break;
	}
	case GL_LINEAR_ATTENUATION:
	{
		const GLfloat value = *params;
		if( value < 0 )
		{
			SetError(GL_INVALID_VALUE);
			break;
		}
		
		light.attenuations[1] = value;
		break;
	}
	case GL_QUADRATIC_ATTENUATION:
	{
		const GLfloat value = *params;
		if( value < 0 )
		{
			SetError(GL_INVALID_VALUE);
			break;
		}
		
		light.attenuations[2] = value;
		break;
	}
	default:
		SetError(GL_INVALID_ENUM);
		break;
	}
}

LightSetup::Light::Light() :
	ambient({0, 0, 0, 1}),
	diffuse({0, 0, 0, 1}),//The initial value for GL_LIGHT0 is (1, 1, 1, 1); 
	specular({0, 0, 0, 1}),//The initial value for GL_LIGHT0 is (1, 1, 1, 1);
	position({0, 0, 1, 0}),
	direction({0, 0, -1}),
	spot_exponent(0),
	spot_cutoff(180),
	attenuations({1, 0, 0})
{
}



