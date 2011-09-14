
#include "state.h"

void glBegin(GLenum mode) {
	Get<StateSetup>.Start(mode);
}

void glEnd(void) {
	Get<StateSetup>.End();
}

StateSetup::StateSetup() :
	GLPart(),
	immediate(false),
	mode(GL_TRIANGLES)
{
}

void StateSetup::Start(GLenum mode)
{
	if( !Evaluate(mode) )
		return;
	
	if( immediate )
	{
		SetError<GL_INVALID_OPERATION>();
		return;
	}
	
	immediate  = true;
	this->mode = mode;
}

void StateSetup::End()
{
	if( !immediate )
	{
		SetError<GL_INVALID_OPERATION>();
		return;
	}
	
	if( vertex_count )
		GetRenderer().Render(this->mode);
	
	immediate = false;
}

RenderPipe& StateSetup::GetRenderer()
{
	return Get<RenderPipe>();
}


