
#include "clip.h"
#include "../gles2.h"

ClipSetup::ClipSetup() : GLPart()
{
}

void ClipSetup::SetClipPlane(
	GLenum          plane,
	const GLfloat*  equation)
{
	if( plane < GL_CLIP_PLANE0 || plane > GL_CLIP_PLANE5 )
	{
		SetError(GL_INVALID_ENUM );
		return;
	}

	GLubyte index = plane - GL_CLIP_PLANE0;

	Copy(equation, planes[index], 4);
}

void glClipPlanef(
	GLenum          plane,
	const GLfloat*  equation)
{
	::Get<ClipSetup>().SetClipPlane(plane, equation);
}

