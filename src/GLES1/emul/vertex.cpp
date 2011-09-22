
#include "vertex.h"
#include "render.h"
#include "color.h"
#include "normal.h"

const unsigned int VERTEX_ELEMENT_COUNT = 4;
const unsigned int COLOR_ELEMENT_COUNT  = 4;
const unsigned int NORMAL_ELEMENT_COUNT = 3;

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
	RenderPipe::BeginRequirement requirement;
/*
	if (mode == GL_QUADS && dimensions && count / dimensions == 4)
		render_current();
*/
	_vertices.push_back(x, y, z);
	
	GLfloat target[4];
	Get<ColorSetup>().GetCurrent(target);
	_colors.push_back(target[0], target[1], target[2], target[3]);
	
	Get<NormalSetup>().GetCurrent(target);
	_normals.push_back(target[0], target[1], target[2]);
/*
	vertex_data();
*/
}

void glVertex2f(GLfloat x, GLfloat y)
{
	glVertex3f(x, y, 0);
}

void glVertex3f(GLfloat x, GLfloat y, GLfloat z) {
	Get<VertexSetup>().Set(x, y, z);
}

void glVertex3fv(const GLfloat *v) {
	glVertex3f(v[0], v[1], v[2]);
}

