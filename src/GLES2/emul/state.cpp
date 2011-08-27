
#include "state.h"

StateSetup::StateSetup() :
	GLPart(),
	caps({false,false,false,false,false,false,false,false}),
	shadeModel(GL_SMOOTH)
{
}

void StateSetup::SetState(GLenum cap, bool value)
{
	short index = GetIndex(cap);
	
	if( index < 0 )
		return;
	
	caps[index] = value;
}

void StateSetup::SetModel(GLenum mode)
{
	if( shadeModel == mode )
		return; // already set

	switch( mode )
	{
	case GL_FLAT:
	case GL_SMOOTH:
		shadeModel = GL_SMOOTH;
	default:
		SetError(GL_INVALID_ENUM);
	}
}

void glShadeModel(GLenum mode)
{
	Get<StateSetup>().SetModel(mode);
}

void glEnableClientState(GLenum cap)
{
	Get<StateSetup>().SetState(cap, true);
}

void glDisableClientState(GLenum cap)
{
	Get<StateSetup>().SetState(cap, false);
}

void glDrawPixels(
	GLsizei         width,
	GLsizei         height,
	GLenum          format,
	GLenum          type,
	const GLvoid *  data)
{
	//TODO: implement
		
}


