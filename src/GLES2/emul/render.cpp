
#include "render.h"
#include "light.h"
/*
const mediump int gl_MaxVertexAttribs               8
const mediump int gl_MaxVertexUniformVectors      128
const mediump int gl_MaxVaryingVectors              8
const mediump int gl_MaxVertexTextureImageUnits     0
const mediump int gl_MaxCombinedTextureImageUnits   8
const mediump int gl_MaxTextureImageUnits           8
const mediump int gl_MaxFragmentUniformVectors     16
const mediump int gl_MaxDrawBuffers                 1
*/

void RenderPipe::preLight(const LightSetup& setup, GLuint * const lightMap)
{
	GLuint map = 1;
	
	const LightSetup::Light* currentLight = setup.lights;
	
	for( GLuint i = 0; i != N_ELEMENTS(setup.lights); i++, currentLight++ )
	{
		if
		(
			currentLight->ambient != LightSetup::DARK
			|| currentLight->diffuse != LightSetup::DARK
			|| currentLight->diffuse != LightSetup::DARK
		)
			(*lightMap) |= map;
		
		map <<= 1; // next map value
	}
}
	
void RenderPipe::Render()
{
	GLuint lightMap = 0;
	LightSetup& lightSetup = Get<LightSetup>();
	preLight(lightSetup, &lightMap);
	
	GLuint program = 0;
	
	GLint param = 0;
	
	glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &param);

	Get<LightSetup>().Apply(this);
/*
	GLint index = glGetUniformLocation(GLuint program, const char* name);

	
	GLuint uniform_index = GetUniformIndex();
	
	GLint size = 0;
	GLenum type = 0;
	char* name = new char[uniformNameLength];
	
	for( int i = 0; i != uniform_count; i++ )
	{
		glGetActiveUniform
		(
			program,
			uniform_index, 
			uniformNameLength,
			NULL, //length
			&size,
			&type,
			name
		);
		
		
	}
	
	delete name;
	
	gles1::RenderPipe::Render();
*/
}

