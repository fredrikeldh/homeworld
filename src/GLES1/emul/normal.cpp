
#include "normal.h"

NormalSetup::NormalSetup():
	GLPart(),
	_current({0, 0, 1})
{
}

void NormalSetup::GetCurrent(GLfloat* result)
{
	Copy(_current.data(), result, 3);
}

void NormalSetup::SetCurrent(GLfloat x, GLfloat y, GLfloat z)
{
	_current[0] = x;
	_current[1] = y;
	_current[2] = z;
}

void glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz) {
	Get<NormalSetup>().SetCurrent(nx, ny, nz);
/*
    if (gles_immediate) {
        if (gles_normal_count / 3 <= gles_vertex_count / gles_vertex_dimensions) {
            gles_normals[gles_normal_count++] = nx;
            gles_normals[gles_normal_count++] = ny;
            gles_normals[gles_normal_count++] = nz;
        } else {
            gles_normals[gles_normal_count - 3] = nx;
            gles_normals[gles_normal_count - 2] = ny;
            gles_normals[gles_normal_count - 1] = nz;
        }
    } else {
        gles_normals[0] = nx;
        gles_normals[1] = ny;
        gles_normals[2] = nz;
        glNormal3f(nx, ny, nz);
    }
*/
}


void glNormal3fv(const GLfloat *v) {
    glNormal3f(v[0], v[1], v[2]);
}

