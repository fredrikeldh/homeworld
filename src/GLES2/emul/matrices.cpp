#include "../gles2.h"
#include "matrices.h"
#include <Matrix.h>
#include <math.h>

GLfloat IDENTITY[] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
/* TODO: reenable
#if N_ELEMENTS(IDENTITY) != MATRIX_SIZE
#error Matrix sizes are wrong!
#endif
*/

enum MatrixType { TEXTURE_MATRIX, MODELVIEW_MATRIX, PROJECTION_MATRIX, COLOR_MATRIX };

MatrixSetup::MatrixSetup():
	_activeMatrixIndex(MODELVIEW_MATRIX)
{
	for( GLubyte times = 4; times; times--)
	{
		_topMatrixEntries.push_back(MatrixEntry(nullptr));
	}
}

MatrixSetup::MatrixEntry::MatrixEntry(MatrixEntry* pPrevious):
	previous(pPrevious)
{
	// Duplicate matrix values

	GLfloat* previousMatrix;

	if( previous )
		previousMatrix = previous->matrix;
	else
		previousMatrix = IDENTITY;

	Copy(previousMatrix, matrix, MATRIX_SIZE);
}


GLubyte MatrixSetup::GetMatrixIndex(GLenum mode)
{
	switch( mode )
	{
	case GL_TEXTURE:
		return TEXTURE_MATRIX;
	case GL_MODELVIEW:
		return MODELVIEW_MATRIX;
	case GL_PROJECTION:
		return PROJECTION_MATRIX;
	case GL_COLOR:
		return COLOR_MATRIX;
	default:
		SetError(GL_INVALID_ENUM);
		return MODELVIEW_MATRIX;
	}
}

GLenum MatrixSetup::GetMatrixMode()
{
	auto type = _activeMatrixIndex;

	switch( type )
	{
	case TEXTURE_MATRIX:
		return GL_TEXTURE;
	case MODELVIEW_MATRIX:
		return GL_MODELVIEW;
	case PROJECTION_MATRIX:
		return GL_PROJECTION;
	case COLOR_MATRIX:
		return GL_COLOR;
	default:
		SetError(GL_INVALID_ENUM);
		return GL_MODELVIEW;
	}
}

void glMatrixMode(GLenum mode)
{
	Get<MatrixSetup>().SetActive(mode);
}

MatrixSetup::MatrixEntry& MatrixSetup::GetActiveMatrixEntry()
{
	return _topMatrixEntries[_activeMatrixIndex];
}

MatrixSetup::MatrixEntry& MatrixSetup::GetMatrixEntry(GLubyte type)
{
	return _topMatrixEntries[type];
}

MatrixSetup::MatrixEntry& MatrixSetup::GetMatrixEntry(GLenum type)
{
	return GetMatrixEntry(GetMatrixIndex(type));
}

void MatrixSetup::GetActiveMatrix(GLfloat* buffer)
{
	Copy(GetActiveMatrixEntry().matrix, buffer, MATRIX_SIZE);
}

void MatrixSetup::SetActiveMatrix(const GLfloat* buffer)
{
	Copy(buffer, GetActiveMatrixEntry().matrix, MATRIX_SIZE);
}

#ifndef MAPIP
void glGetIntegerv(GLenum pname, GLint* params)
{
	Get<MatrixSetup>().Get<GLint>(pname, params);
}

void glGetFloatv(GLenum pname, GLfloat* params)
{
	Get<MatrixSetup>().Get(pname, params);
}
#endif

void glLoadMatrixf(const GLfloat* m)
{
	Get<MatrixSetup>().SetActiveMatrix(m);
}

void glLoadIdentity()
{
	glLoadMatrixf(IDENTITY);
}

void glPushMatrix()
{
	Get<MatrixSetup>().Push();
}

void glPopMatrix()
{
	Get<MatrixSetup>().Pop();
}

void glMultMatrixf(const GLfloat* m)
{
	Get<MatrixSetup>().MultiplyActive(m);
}

void MatrixSetup::MultiplyActive(const GLfloat* m)
{
	auto& pStack = GetActiveMatrixEntry();

	GLfloat buffer[MATRIX_SIZE];
	Copy(pStack.matrix, buffer, N_ELEMENTS(buffer));

	MultiplyMatrix4fByMatrix4f(pStack.matrix, m, buffer);
}

void glScalef(
	GLfloat x,
	GLfloat y,
	GLfloat z)
{
	GLfloat matrix[] =
	{
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
	};
	glMultMatrixf(matrix);
}

void glTranslatef(
	GLfloat  x,
	GLfloat  y,
	GLfloat  z)
{
	GLfloat matrix[] =
	{
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	};
	glMultMatrixf(matrix);
}

void glRotatef(
	GLfloat  angle,
	GLfloat  x,
	GLfloat  y,
	GLfloat  z)
{
	GLfloat matrix[16];

  /* This function contributed by Erich Boleyn (erich@uruk.org) */
   GLfloat mag, s, c;
   GLfloat xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

   s = sin( angle * (M_PI / 180.0) );
   c = cos( angle * (M_PI / 180.0) );

   mag = sqrt( x*x + y*y + z*z );

   if (mag == 0.0) {
      /* generate an identity matrix and return */
      Buffer::Copy<GLfloat, N_ELEMENTS(matrix)>(matrix, IDENTITY);
      return;
   }

   x /= mag;
   y /= mag;
   z /= mag;

#define M(row,col)  matrix[col*4+row]

   /*
    *     Arbitrary axis rotation matrix.
    *
    *  This is composed of 5 matrices, Rz, Ry, T, Ry', Rz', multiplied
    *  like so:  Rz * Ry * T * Ry' * Rz'.  T is the final rotation
    *  (which is about the X-axis), and the two composite transforms
    *  Ry' * Rz' and Rz * Ry are (respectively) the rotations necessary
    *  from the arbitrary axis to the X-axis then back.  They are
    *  all elementary rotations.
    *
    *  Rz' is a rotation about the Z-axis, to bring the axis vector
    *  into the x-z plane.  Then Ry' is applied, rotating about the
    *  Y-axis to bring the axis vector parallel with the X-axis.  The
    *  rotation about the X-axis is then performed.  Ry and Rz are
    *  simply the respective inverse transforms to bring the arbitrary
    *  axis back to it's original orientation.  The first transforms
    *  Rz' and Ry' are considered inverses, since the data from the
    *  arbitrary axis gives you info on how to get to it, not how
    *  to get away from it, and an inverse must be applied.
    *
    *  The basic calculation used is to recognize that the arbitrary
    *  axis vector (x, y, z), since it is of unit length, actually
    *  represents the sines and cosines of the angles to rotate the
    *  X-axis to the same orientation, with theta being the angle about
    *  Z and phi the angle about Y (in the order described above)
    *  as follows:
    *
    *  cos ( theta ) = x / sqrt ( 1 - z^2 )
    *  sin ( theta ) = y / sqrt ( 1 - z^2 )
    *
    *  cos ( phi ) = sqrt ( 1 - z^2 )
    *  sin ( phi ) = z
    *
    *  Note that cos ( phi ) can further be inserted to the above
    *  formulas:
    *
    *  cos ( theta ) = x / cos ( phi )
    *  sin ( theta ) = y / sin ( phi )
    *
    *  ...etc.  Because of those relations and the standard trigonometric
    *  relations, it is pssible to reduce the transforms down to what
    *  is used below.  It may be that any primary axis chosen will give the
    *  same results (modulo a sign convention) using thie method.
    *
    *  Particularly nice is to notice that all divisions that might
    *  have caused trouble when parallel to certain planes or
    *  axis go away with care paid to reducing the expressions.
    *  After checking, it does perform correctly under all cases, since
    *  in all the cases of division where the denominator would have
    *  been zero, the numerator would have been zero as well, giving
    *  the expected result.
    */

   xx = x * x;
   yy = y * y;
   zz = z * z;
   xy = x * y;
   yz = y * z;
   zx = z * x;
   xs = x * s;
   ys = y * s;
   zs = z * s;
   one_c = 1.0F - c;

   M(0,0) = (one_c * xx) + c;
   M(0,1) = (one_c * xy) - zs;
   M(0,2) = (one_c * zx) + ys;
   M(0,3) = 0.0F;

   M(1,0) = (one_c * xy) + zs;
   M(1,1) = (one_c * yy) + c;
   M(1,2) = (one_c * yz) - xs;
   M(1,3) = 0.0F;

   M(2,0) = (one_c * zx) - ys;
   M(2,1) = (one_c * yz) + xs;
   M(2,2) = (one_c * zz) + c;
   M(2,3) = 0.0F;

   M(3,0) = 0.0F;
   M(3,1) = 0.0F;
   M(3,2) = 0.0F;
   M(3,3) = 1.0F;

#undef M

	glMultMatrixf(matrix);
}

void glFrustumf(
	GLfloat  left,
	GLfloat  right,
	GLfloat  bottom,
	GLfloat  top,
	GLfloat  nearVal,
	GLfloat  farVal
)
{
	if
	(
		farVal < 0
		|| nearVal < 0
		|| left == right
		|| bottom == top
		|| farVal == nearVal
	)
	{
		GLPart::SetError<GL_INVALID_VALUE>();
		return;
	}

	const GLfloat A = (right + left) / (right - left);
	const GLfloat B = (top + bottom) / (top - bottom);
	const GLfloat C = -(farVal + nearVal) / (farVal - nearVal);
	const GLfloat D = -2 * farVal * nearVal / (farVal - nearVal);

	const GLfloat matrix[] =
	{
		(2 * nearVal) / (right - left), 0, A, 0,
		0, 2  * nearVal / (top - bottom), B, 0,
		0, 0, C, D,
		0, 0, -1, 0
	};

	glMultMatrixf(matrix);
}

extern "C"
void glOrthof (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far)
{
	GLfloat m [16];
	GLfloat rml = right - left;
	GLfloat fmn = far - near;
	GLfloat tmb = top - bottom;
	GLfloat _1over_rml;
	GLfloat _1over_fmn;
	GLfloat _1over_tmb;

	if (rml == 0.0 || fmn == 0.0 || tmb == 0.0) {
		GLPart::SetError<GL_INVALID_VALUE>();
		return;
	}

	_1over_rml = 1.0 / rml;
	_1over_fmn = 1.0 / fmn;
	_1over_tmb = 1.0 / tmb;

	m[0] = 2.0 * _1over_rml;
	m[1] = 0.0;
	m[2] = 0.0;
	m[3] = 0.0;

	m[4] = 0.0;
	m[5] = 2.0 * _1over_tmb;
	m[6] = 0.0;
	m[7] = 0.0;

	m[8] = 0.0;
	m[9] = 0.0;
	m[10] = -2.0 * _1over_fmn;
	m[11] = 0.0;

	m[12] = -(right + left) *  _1over_rml;
	m[13] = -(top + bottom) *  _1over_tmb;
	m[14] = -(far + near) * _1over_fmn;
	m[15] = 1.0;

	glMultMatrixf(m);
}

void MatrixSetup::Push()
{
	// Save reference to previous stack entry
	auto& previous = GetActiveMatrixEntry();

	MatrixEntry* pNewStackHead = new MatrixEntry(&previous);

	_topMatrixEntries[_activeMatrixIndex] = pNewStackHead;
}

void MatrixSetup::Pop()
{
	auto& old = GetActiveMatrixEntry();

	_topMatrixEntries[_activeMatrixIndex] = old.previous;

	delete &old;
}

void MatrixSetup::SetActive(GLenum mode)
{
	auto index = GetMatrixIndex(mode);

	if( GetError() != GL_NO_ERROR )
		return; //failed

	_activeMatrixIndex = index;
}

