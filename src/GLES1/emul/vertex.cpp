
#include "vertex.h"

VertexSetup::VertexSetup() :
	GLPart()
{
}

/*
void VertexSetup::vertex_data()
{
	
    if (!normal_count) normal_count = 3;
    while (normal_count / 3 < count / dimensions) {
        normals[normal_count] = normals[normal_count - 3];
        normal_count++;
        normals[normal_count] = normals[normal_count - 3];
        normal_count++;
        normals[normal_count] = normals[normal_count - 3];
        normal_count++;
    }
    
    if (!color_count) color_count = 4;
    while (color_count / 4 < count / dimensions) {
        colors[color_count] = colors[color_count - 4];
        color_count++;
        colors[color_count] = colors[color_count - 4];
        color_count++;
        colors[color_count] = colors[color_count - 4];
        color_count++;
        colors[color_count] = colors[color_count - 4];
        color_count++;
    }
}
*/

void VertexSetup::Set(GLfloat x, GLfloat y, GLfloat z)
{
/*
	if (mode == GL_QUADS && dimensions && count / dimensions == 4)
		render_current();
*/
	GLfloat* target = _vertices[_count * VERTEX_ELEMENT_COUNT];
	Copy(x, target++);
	Copy(y, target++);
	Copy(z, target  );
	
	target = _colors[_count * COLOR_ELEMENT_COUNT];
	Get<ColorSetup>.GetCurrent(target);
	
	target = _normals[_count * NORMAL_ELEMENT_COUNT];
	Get<NormalSetup>.GetCurrent(target);

	_count++;
/*
	vertex_data();
*/
}

void glVertex2f(GLfloat x, GLfloat y)
{
	glVertex3f(x, y, 0);
}

void glVertex3f(GLfloat x, GLfloat y, GLfloat z) {
	Get<VertexSetup>.Set(x, y, z);
}

void glVertex3fv(const GLfloat *v) {
	glVertex3f(v[0], v[1], v[2]);
}

