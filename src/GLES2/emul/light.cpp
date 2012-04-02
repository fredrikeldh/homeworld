#include "../gles2.h"

#include "light.h"
#include <sstream>

GLfloat LightSetup::DARK[] = {0, 0, 0, 0};

LightSetup::LightSetup() :
	ambient(0.2f, 0.2f, 0.2f, 1.0f, "u_ambient"),
	color_control(GL_SINGLE_COLOR),
	local_viewer(false),
	two_sided(false),
	_lights()
{
	for( int i = 0; i != GL_MAX_LIGHTS; i++ )
	{
		_lights.push_back(Light(i));
		AddComponent(_lights[i]);
	}

	_lights[0].diffuse.Set(1, 1, 1, 1);
	_lights[0].specular.Set(1, 1, 1, 1);
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

	Light& light = _lights[lightEnum - GL_LIGHT0];

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

static std::string __buildString(const char* prefix, GLubyte index, const char* postfix)
{
	std::stringstream stream;
	stream << std::string(prefix) << index << postfix;
	return stream.str();
}

LightSetup::Light::Light(GLubyte index) :
	GLPart(),
	IRenderComponent(),
	_prefix(::__buildString("u_LightSource[", index, "].")),
	enabled             (false,                  _prefix + "enabled"),
	ambient             (0.0f, 0.0f, 0.0f, 1.0f, _prefix + "ambient"),
	diffuse             (0.0f, 0.0f, 0.0f, 1.0f, _prefix + "diffuse"),
	specular            (0.0f, 0.0f, 0.0f, 1.0f, _prefix + "specular"),
	position            (0.0f, 0.0f, 1.0f, 0.0f, _prefix + "position"),
	direction           (0.0f, 0.0f, -1.0f,      _prefix + "spotDirection"),
	spot_exponent       (0.0f,                   _prefix + "spotExponent"),
	spot_cutoff         (180.0f,                 _prefix + "spotCutoff"),
	constantAttenuation (1.0f,                   _prefix + "constantAttenuation"),
	linearAttenuation   (0.0f,                   _prefix + "linearAttenuation"),
	quadraticAttenuation(0.0f,                   _prefix + "quadraticAttenuation")
{
#define P(X) AddComponent(X)
	P(enabled);
	P(ambient);
	P(diffuse);
	P(specular);
	P(position);
	P(direction);
	P(spot_cutoff);
	P(constantAttenuation);
	P(linearAttenuation);
	P(quadraticAttenuation);
#undef P
}

#if HAS_MOVE_ASSIGN_BUG
LightSetup::Light& LightSetup::Light::operator=(LightSetup::Light&& other)
{
	GLPart::operator=(std::move(other));
	IRenderComponent::operator=(std::move(other));
	_prefix = std::move(other._prefix);
	enabled             = std::move(other.enabled);
	ambient             = std::move(other.ambient);
	diffuse             = std::move(other.diffuse);
	specular            = std::move(other.specular);
	position            = std::move(other.position);
	direction           = std::move(other.direction);
	spot_exponent       = std::move(other.spot_exponent);
	spot_cutoff         = std::move(other.spot_cutoff);
	constantAttenuation = std::move(other.constantAttenuation);
	linearAttenuation   = std::move(other.linearAttenuation);
	quadraticAttenuation= std::move(other.quadraticAttenuation);
	return *this;
}
#endif

void LightSetup::Light::ApplyTo(RENDER_PROCESSOR* renderer)
{
	// Check whether we have to process anything
	enabled.Set
	(
		ambient != LightSetup::DARK
		|| diffuse != LightSetup::DARK
		|| specular != LightSetup::DARK
	);

	IRenderComponent::ApplyTo(renderer);
}

void LightSetup::ApplyTo(RENDER_PROCESSOR* renderer)
{
	//todo
}
