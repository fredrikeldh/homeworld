#ifndef _HW_GLES2_DECLARATION_H_
#define _HW_GLES2_DECLARATION_H_

#include "../../GLES1/emul/declarations.h"

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

void glAlphaFunc(
	GLenum    func,
	GLclampf  ref);

void glClipPlanef(
	GLenum           plane,
	const GLfloat*  equation);

void glColor4ub(
	GLubyte  red,
	GLubyte  green,
	GLubyte  blue,
	GLubyte  alpha);

void glColorPointer(
	GLint          size,
	GLenum         type,
	GLsizei        stride,
	const GLvoid * pointer);

void glDisableClientState(GLenum cap);

void glDrawPixels(
	GLsizei         width,
	GLsizei         height,
	GLenum          format,
	GLenum          type,
	const GLvoid *  data);

void glEnableClientState(GLenum cap);

void glFogf(
	GLenum  	pname,
 	GLfloat  	param
);

void glFogfv(
	GLenum  	pname,
 	GLfloat*    params

void glFrustumf(
	GLfloat  left,
	GLfloat  right,
	GLfloat  bottom,
	GLfloat  top,
	GLfloat  nearVal,
	GLfloat  farVal
);

void glGetFloatv(GLenum pname, GLfloat* params);
void glGetIntegerv(GLenum pname, GLint* params);

void glLightfv(
	GLenum          light,
	GLenum          pname,
	const GLfloat*  params);

void glLightModelfv(
	GLenum          pname,
	const GLfloat*  params);

void glLightModelf(
	GLenum   pname,
	GLfloat  param);

void glLineStipple(
	GLint     factor,
	GLushort  pattern);

void glLoadIdentity();

void glLoadMatrixf(const GLfloat* m);

void glMaterialfv(
	GLenum         face,
	GLenum         pname,
	const GLfloat* params);

void glMatrixMode(GLenum mode);

void glMultMatrixf(const GLfloat* m);

void glNormalPointer(
	GLenum        type,
	GLsizei       stride,
	const GLvoid* pointer);

void glPointSize(GLfloat  size);

void glPushMatrix();

void glPopMatrix();

void glRasterPos2f (GLfloat x, GLfloat y);
void glRasterPos2fv (const GLfloat *v);

void glRotatef(
	GLfloat  angle,
	GLfloat  x,
	GLfloat  y,
	GLfloat  z);

void glScalef(
	GLfloat x,
	GLfloat y,
	GLfloat z);

void glShadeModel(GLenum mode);

void glTexCoordPointer(
	GLint          size,
	GLenum         type,
	GLsizei        stride,
	const GLvoid*  pointer);
	
void glTexEnvi(
	GLenum target,
	GLenum pname,
	GLint param
);

void glTranslatef(
	GLfloat  x,
	GLfloat  y,
	GLfloat  z);

void glVertexPointer(
	GLint          size,
 	GLenum         type,
 	GLsizei        stride,
 	const GLvoid*  pointer);

#ifdef __cplusplus
}
#endif //__cplusplus
#endif //_HW_GLES2_DECLARATION_H_
