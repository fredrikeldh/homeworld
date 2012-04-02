#include <GLES/gl.h>
#include "../GLES1/emul/defines.h"

void glBegin(GLenum mode);
void glEnd(void);

void glColor3f(GLfloat red, GLfloat green, GLfloat blue);
void glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
void glColor3ub(GLubyte red, GLubyte green, GLubyte blue);
void glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);

void glDrawArraysEx(GLenum mode, GLint first, GLsizei count);

void glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz);
void glNormal3fv(const GLfloat *v);

void glTexCoord2f(GLfloat s, GLfloat t);

void glVertex2f(GLfloat x, GLfloat y);
void glVertex3f(GLfloat x, GLfloat y, GLfloat z);
void glVertex3fv(const GLfloat *v);

void glRasterPos2f (GLfloat x, GLfloat y);
void glDrawPixels(
	GLsizei         width,
	GLsizei         height,
	GLenum          format,
	GLenum          type,
	const GLvoid *  data);
