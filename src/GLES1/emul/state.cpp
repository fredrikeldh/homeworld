
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
	
	immediate  = true;
	this->mode = mode;
}

void StateSetup::End()
{
	if( vertex_count )
		gles_render_current();
	
	immediate = 0;
}

