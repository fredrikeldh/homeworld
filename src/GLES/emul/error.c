
#include <errno.h>
#include "error.h"

GLenum glGetErrorX()
{
	GLenum error = glGetError();

	if( error != GL_NO_ERROR )
		return error;

	return errno;
}

void glSetError(GlEnum error)
{
	errno = error;
}
