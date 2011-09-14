#ifndef _HW_GLES1_DECLARATIONS_H_
#define _HW_GLES1_DECLARATIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

void glBegin(GLenum mode);
void glEnd(void);

void glColor3f(GLfloat red, GLfloat green, GLfloat blue);
void glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
void glColor3ub(GLubyte red, GLubyte green, GLubyte blue);
void glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);

void glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz);
void glNormal3fv(const GLfloat *v);

void glTexCoord2f(GLfloat s, GLfloat t);

void glVertex2f(GLfloat x, GLfloat y);
void glVertex3f(GLfloat x, GLfloat y, GLfloat z);
void glVertex3fv(const GLfloat *v);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //_HW_GLES1_DECLARATIONS_H_
