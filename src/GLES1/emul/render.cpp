
#include "render.h"
#include <mutex>

// There can be only one - Renderer
static std::recursive_mutex _renderMutex;

RenderPipe::RenderPipe() :
	GLPart(),
	_immediate(false),
	_mode(GL_TRIANGLES)
{
}

template<GLenum STATE>
class ClientState
{
private:
	bool _enabled;
public:
	bool IsEnabled() const
	{
		return _enabled;
	}
protected:
	ClientState(bool enabled):
		_enabled(enabled)
	{
		if( IsEnabled() )
			glEnableClientState(STATE);
	}
public:
	~ClientState()
	{
		if( IsEnabled() )
			glDisableClientState(STATE);
	}
};

bool RenderPipe::is_texture_enabled(const VertexSetup& vertexData) const
{
	return vertexData._texCoords.size() && _mode >= GL_TRIANGLES;
}

bool RenderPipe::is_color_enabled(const VertexSetup& vertexData) const
{
	return vertexData._colors.size();
}

bool RenderPipe::is_normal_enabled(const VertexSetup& vertexData) const
{
	return vertexData._normals.size() && _mode >= GL_TRIANGLES;
}

class VertexClientState : public ClientState<GL_VERTEX_ARRAY>
{
public:
	VertexClientState(const VertexSetup&, const RenderPipe&) :
		ClientState<GL_VERTEX_ARRAY>(true)
	{
	}
};

class TextureClientState : public ClientState<GL_TEXTURE_COORD_ARRAY>
{
public:
	TextureClientState(const VertexSetup& vertexData, const RenderPipe& renderer) :
		ClientState<GL_TEXTURE_COORD_ARRAY>(renderer.is_texture_enabled(vertexData))
	{
	}
};

class ColorClientState : public ClientState<GL_COLOR_ARRAY>
{
public:
	ColorClientState(const VertexSetup& vertexData, const RenderPipe& renderer) :
		ClientState<GL_COLOR_ARRAY>(renderer.is_color_enabled(vertexData))
	{
	}
};

class NormalClientState : public ClientState<GL_NORMAL_ARRAY>
{
public:
	NormalClientState(const VertexSetup& vertexData, const RenderPipe& renderer) :
		ClientState<GL_NORMAL_ARRAY>(renderer.is_normal_enabled(vertexData))
	{
	}
};

static const GLushort gles_quad_indices[4] = { 1, 2, 0, 3 };

void RenderPipe::Render()
{
	VertexSetup& vertexData = Get<VertexSetup>();
	
	VertexSetup::Array<GLfloat, 16384>& vertices = vertexData._vertices;
	unsigned int vertex_dimensions = vertexData._vertex_dimensions;
	
	GLenum& mode = _mode;
	
	VertexClientState vertexState(vertexData, *this);
	glVertexPointer(vertex_dimensions, GL_FLOAT, 0, vertices);
	
	TextureClientState textureState(vertexData, *this);
	if( textureState.IsEnabled() )
		glTexCoordPointer(2, GL_FLOAT, 0, vertexData._texCoords);
	
	VertexSetup::Array<GLfloat, 16384>& colors = vertexData._colors;
	ColorClientState colorState(vertexData, *this);
	if( colorState.IsEnabled() )
		glColorPointer(4, GL_FLOAT, 0, colors);
	
	VertexSetup::Array<GLfloat, 16384>& normals = vertexData._normals;
	NormalClientState normalState(vertexData, *this);
	if( normalState.IsEnabled() )
		glNormalPointer(GL_FLOAT, 0, normals);

	GLuint vertex_count = vertices.size();

	switch( mode )
	{
		case GL_POINTS:
		case GL_LINES:
		case GL_LINE_LOOP:
		case GL_LINE_STRIP:
		case GL_TRIANGLES:
		case GL_TRIANGLE_STRIP:
		case GL_TRIANGLE_FAN:
			glDrawArraysEx(mode, 0, vertex_count / vertex_dimensions);
			break;
		case GL_QUADS:
			glDrawElements(GL_TRIANGLE_STRIP, vertex_count / vertex_dimensions, GL_UNSIGNED_SHORT, gles_quad_indices);
			break;
		case GL_POLYGON:
		{
			GLfloat center_x = 0.0f, center_y = 0.0f;
			vertices[vertex_count++] = vertices[0];
			vertices[vertex_count++] = vertices[1];

			GLushort poly_indices[(vertex_count / vertex_dimensions) + 1];
			poly_indices[0] = vertex_count / vertex_dimensions;
			
			for( GLuint i = 0; i < vertex_count / vertex_dimensions; i++ )
			{
				poly_indices[i + 1] = i;
				center_x += vertices[i * 2] / (vertex_count / vertex_dimensions);
				center_y += vertices[(i * 2) + 1] / (vertex_count / vertex_dimensions);
			}

			vertices[vertex_count++] = center_x;
			vertices[vertex_count++] = center_y;
			glDrawElements(GL_TRIANGLE_FAN, vertex_count / vertex_dimensions, GL_UNSIGNED_SHORT, poly_indices);
			break;
		}
		default:
			printf("gles_render_current: unsupported mode: 0x%x\n", mode);
			break;
	}

	vertices.clear();
	vertexData._texCoords.clear();
	
	unsigned int color_count = vertexData._colors.size();
	
	if( color_count )
	{
		colors[0] = colors[color_count - 4];
		colors[1] = colors[color_count - 3];
		colors[2] = colors[color_count - 2];
		colors[3] = colors[color_count - 1];
		vertexData._colors.clear();
	}
	
	unsigned int normal_count = vertexData._normals.size();

	if( normal_count )
	{
		normals[0] = normals[normal_count - 3];
		normals[1] = normals[normal_count - 2];
		normals[2] = normals[normal_count - 1];
		vertexData._normals.clear();
	}
}

void glBegin(GLenum mode)
{
	Get<RenderPipe>().Start(mode);
}

void glEnd(void)
{
	Get<RenderPipe>().End();
}

void RenderPipe::Start(GLenum mode)
{
	if
	(
		!Evaluate
		<
			GL_POINTS      , GL_LINES    , GL_LINE_STRIP,
			GL_LINE_LOOP   , GL_TRIANGLES, GL_TRIANGLE_STRIP,
			GL_TRIANGLE_FAN, GL_QUADS    ,
			GL_POLYGON
		>(mode)
	)
		return;
	
	_renderMutex.lock();

	if( _immediate )
	{ // Start was already called
		_renderMutex.unlock();
		SetError<GL_INVALID_OPERATION>();
		return;
	}
	
	_immediate = true;
	_mode = mode;
}

void RenderPipe::End()
{
	if( _immediate )
	{
		SetError<GL_INVALID_OPERATION>();
		return;
	}
	
	Render();
	
	_immediate = false;
	_renderMutex.unlock();
}

void RenderPipe::Render(GLenum  mode, GLint  first, GLsizei  count)
{
	if
	(
		!Evaluate
		<
			GL_POINTS,
			GL_LINE_STRIP,
			GL_TRIANGLE_STRIP,
			GL_LINES
		>(mode)
	)
		return;
	
	if( !_renderMutex.try_lock() )
	{
		SetError<GL_INVALID_OPERATION>();
		return;
	}
	
	glDrawArrays(mode, first, count);
	
	_renderMutex.unlock();
}

void glDrawArraysEx
(
	GLenum   mode,
	GLint    first,
	GLsizei  count
)
{
	Get<RenderPipe>().Render(mode, first, count);
}
