#include "mosync_gl1.h"

void glBegin(GLenum mode) {
}

void glEnd(void) {
}

void glColor3f(GLfloat red, GLfloat green, GLfloat blue) {
}

void glColor3ub(GLubyte red, GLubyte green, GLubyte blue) {
}


void glDrawArraysEx(GLenum mode, GLint first, GLsizei count) {
	glDrawArrays(mode, first, count);
}

void glNormal3fv(const GLfloat* v) {
	glNormal3f(v[0], v[1], v[2]);
}

void glTexCoord2f(GLfloat s, GLfloat t) {
}

void glVertex2f(GLfloat x, GLfloat y) {
}

void glVertex3f(GLfloat x, GLfloat y, GLfloat z) {
}

void glVertex3fv(const GLfloat* v) {
}

void glRasterPos2f(GLfloat x, GLfloat y) {
}

void glDrawPixels(GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* data) {
}
