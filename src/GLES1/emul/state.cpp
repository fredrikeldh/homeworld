
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
	if
	(
		!Evaluate
		<
			GL_POINTS      , GL_LINES    , GL_LINE_STRIP,
			GL_LINE_LOOP   , GL_TRIANGLES, GL_TRIANGLE_STRIP,
			GL_TRIANGLE_FAN, GL_QUADS    ,
			GL_POLYGON
		>(mode);
	)
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


