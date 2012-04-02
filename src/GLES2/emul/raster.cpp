#include "../gles2.h"
#include "raster.h"

void glRasterPos2f (GLfloat x, GLfloat y)
{
	Get<RasterSetup>().Set(x, y);
}

void glRasterPos2fv (const GLfloat *v)
{
	glRasterPos2f(*v, *(v + 1));
}

RasterSetup::RasterSetup() :
	GLPart()
{
}

void RasterSetup::Set(GLfloat x, GLfloat y)
{
	position[0] = x;
	position[1] = y;
}

