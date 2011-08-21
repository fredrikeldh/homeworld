
#include "../gles2.h"

const GLubyte MaterialSetup::MFRONT = 1 << 0;
const GLubyte MaterialSetup::MBACK  = 1 << 1;

GLubyte MaterialSetup::getFaceBitMap(GLenum face)
{
	switch( face )
	{
	case GL_FRONT:
		return MaterialSetup::MFRONT;
	case GL_BACK:
		return MaterialSetup::MBACK;
	case GL_FRONT_AND_BACK:
		return MFRONT | MBACK;
	default:
		SetError(GL_INVALID_ENUM);
		return MFRONT;
	}
}

MaterialSetup::Side::Side():
	ambient  ({0.2, 0.2, 0.2, 1.0}),
	diffuse  ({0.8, 0.8, 0.8, 1.0}),
	specular ({0  , 0  , 0  , 1  }),
	emission ({0  , 0  , 0  , 1  }),
	shininess(0),
	color_indices({0, 0, 0})
{
}

template <typename T>
void MaterialSetup::setAmbient(const GLubyte cullBits, const T* params)
{
	if( cullBits & MFRONT )
		Copy(params, front.ambient, 4);
	
	if( cullBits & MBACK )
		Copy(params, back.ambient, 4);
}

template <typename T>
void MaterialSetup::setDiffuse(const GLubyte cullBits, const T* params)
{
	if( cullBits & MFRONT )
		Copy(params, front.diffuse, 4);
	
	if( cullBits & MBACK )
		Copy(params, back.diffuse, 4);
}

template<typename T>
void MaterialSetup::Set(
	GLenum         face,
	GLenum         pname,
	const T* params)
{
	GLubyte cullBits = getFaceBitMap(face);
	
	if( glGetErrorX() != GL_NO_ERROR )
		return;

	if( !Evaluate(pname) )
		return;
	
	switch( pname )
	{
	case GL_AMBIENT:
		setAmbient(cullBits, params);
			
		break;
	case GL_DIFFUSE:
		setDiffuse(cullBits, params);
		break;
	case GL_SPECULAR:
		if( cullBits & MFRONT )
			Copy(params, front.specular, 4);
		
		if( cullBits & MBACK )
			Copy(params, back.specular, 4);
			
		break;
	case GL_EMISSION:
		if( cullBits & MFRONT )
			Copy(params, front.emission, 4);
		
		if( cullBits & MBACK )
			Copy(params, back.emission, 4);
			
		break;
	case GL_SHININESS:
	{
		const T value = *params;
		if( value < 0 || value > 128 )
		{
			SetError(GL_INVALID_VALUE);
			break;
		}
		
		if( cullBits & MFRONT )
			front.shininess = value;
		
		if( cullBits & MBACK )
			back.shininess = value;
		
		break;
	}
	case GL_AMBIENT_AND_DIFFUSE:
		setAmbient(cullBits, params);
		setDiffuse(cullBits, params);
	case GL_COLOR_INDEX:
		if( cullBits & MFRONT )
			Copy(params, front.color_indices, 3);
		
		if( cullBits & MBACK )
			Copy(params, back.color_indices, 3);
	default:
		SetError(GL_INVALID_ENUM);
		break;
	}
}

void glMaterialfv(
	GLenum         face,
	GLenum         pname,
	const GLfloat* params)
{
	Get<MaterialSetup>().Set(face, pname, params);
}
