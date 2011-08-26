
#include "vertex.h"

VertexSetup::VertexSetup() :
	GLPart(),
	count(0),
	dimensions(2)
{
}

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

void VertexSetup::Set(GLfloat x, GLfloat y)
{
	if (mode == GL_QUADS && dimensions && count / dimensions == 4)
		render_current();

	dimensions = 2;
	vertex[count++] = x;
	vertex[count++] = y;
	vertex_data();
}

void VertexSetup::Set(GLfloat x, GLfloat y, GLfloat z)
{
	if (mode == GL_QUADS && dimensions && count / dimensions == 4)
		render_current();
		
	vertex_dimensions = 3;
	vertex[count++] = x;
	vertex[count++] = y;
	vertex[count++] = z;
	vertex_data();
}

void glVertex2f(GLfloat x, GLfloat y)
{
	Get<VertexSetup>.Set(x, y);
}

void glVertex3f(GLfloat x, GLfloat y, GLfloat z) {
	Get<VertexSetup>.Set(x, y, z);
}

void glVertex3fv(const GLfloat *v) {
	glVertex3f(v[0], v[1], v[2]);
}

