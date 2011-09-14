
#include "light.h"

GLfloat LightSetup::DARK[] = {0, 0, 0, 0};

LightSetup::LightSetup() : 
	ambient(0.2f, 0.2f, 0.2f, 1.0f, "u_ambient"),
	color_control(GL_SINGLE_COLOR),
	local_viewer(false),
	two_sided(false)
{
	lights[0].diffuse.Set(1, 1, 1, 1);
	lights[0].specular.Set(1, 1, 1, 1);
}

template<typename T>
void LightSetup::Set(
	GLenum    pname,
	const T*  params)
{
	switch( pname )
	{
	case GL_LIGHT_MODEL_AMBIENT:
		ambient.Set(params);
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
	default:
		SetError<GL_INVALID_ENUM>();
		return;
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
	
	const GLfloat value = *params;
#define INVALID_BREAK {SetError<GL_INVALID_VALUE>(); break;}
		
	switch( pname )
	{
	case GL_AMBIENT:
		light.ambient.Set(params);
		break;
	case GL_DIFFUSE:
		light.diffuse.Set(params);
		break;
	case GL_SPECULAR:
		light.specular.Set(params);
		break;
	case GL_POSITION:
		light.position.Set(params);
		break;
	case GL_SPOT_DIRECTION:
		light.direction.Set(params);
		break;
	case GL_SPOT_EXPONENT:
	{
		if( value < 0 || value > 128 )
			INVALID_BREAK
		
		light.spot_exponent.Set(value);
		break;
	}
	case GL_SPOT_CUTOFF:
	{
		if( (value < 0 || value > 90) && (value != 180) )
			INVALID_BREAK
		
		light.spot_cutoff.Set(value);
		break;
	}
	case GL_CONSTANT_ATTENUATION:
	{
		if( value < 0 )
			INVALID_BREAK
		
		light.constantAttenuation.Set(value);
		break;
	}
	case GL_LINEAR_ATTENUATION:
	{
		if( value < 0 )
			INVALID_BREAK
		
		light.linearAttenuation.Set(value);
		break;
	}
	case GL_QUADRATIC_ATTENUATION:
	{
		if( value < 0 )
			INVALID_BREAK
		
		light.quadraticAttenuation.Set(value);
		break;
	}
	default:
		INVALID_BREAK
	}
#undef INVALID_BREAK
}

LightSetup::Light::Light() :
	ambient(0.0f, 0.0f, 0.0f, 1.0f,   "u_LightSource.ambient"),
	diffuse(0.0f, 0.0f, 0.0f, 1.0f,   "u_LightSource.diffuse"),
	specular(0.0f, 0.0f, 0.0f, 1.0f,  "u_LightSource.diffuse"),
	position(0.0f, 0.0f, 1.0f, 0.0f,  "u_LightSource.position"),
	direction(0.0f, 0.0f, -1.0f,   "u_LightSource.spotDirection"),
	spot_exponent(0.0f,        "u_LightSource.spotExponent"),
	spot_cutoff(180.0f,        "u_LightSource.spotCutoff"),
	constantAttenuation(1.0f,  "u_LightSource.constantAttenuation"),
	linearAttenuation(0.0f,    "u_LightSource.linearAttenuation"),
	quadraticAttenuation(0.0f, "u_LightSource.quadraticAttenuation")
{
}

void LightSetup::Apply(RENDER_PROCESSOR* pRenderer)
{
/*
	ApplyTo
	(
		pRenderer,
		ambient,
		diffuse,
		specular,
		position,
		spot_exponent,
		spot_cutoff,
		constantAttenuation,
		linearAttenuation,
		quadraticAttenuation
	);
*/
}

