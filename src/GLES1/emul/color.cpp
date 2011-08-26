
#include "color.h"

void glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
	Get<ColorSetup>().Set(read, green, blue, alpha);
}

void glColor3f(GLfloat red, GLfloat green, GLfloat blue) {
    glColor4f(red, green, blue, 1.0f);
}

void glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) {
    glColor4f((GLfloat)red / 255.0f, (GLfloat)green / 255.0f, (GLfloat)blue / 255.0f, (GLfloat)alpha / 255.0f);
}

static inline void glColor3ub(GLubyte red, GLubyte green, GLubyte blue) {
    glColor4ub(red, green, blue, 255);
}

ColorSetup::ColorSetup() :
	GLPart(),
	color_count(0)
{
}

void ColorSetup::Set(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	if (gles_immediate) {
		if (color_count / 4 <= gles_vertex_count / gles_vertex_dimensions) {
			colors[color_count++] = red;
			colors[color_count++] = green;
			colors[color_count++] = blue;
			colors[color_count++] = alpha;
		} else {
			colors[color_count - 4] = red;
			colors[color_count - 3] = green;
			colors[color_count - 2] = blue;
			colors[color_count - 1] = alpha;
		}
	} else {
		colors[0] = red;
		colors[1] = green;
		colors[2] = blue;
		colors[3] = alpha;
		glColor4f(red, green, blue, alpha);
	}
}


