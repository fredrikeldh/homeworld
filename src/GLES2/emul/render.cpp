
#include "render.h"
#include "light.h"
#include <cstring>
#include <fstream>
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

RenderPipe::RenderPipe():
	gles1::RenderPipe(),
	_configurations(),
	_programs(),
	_program()
{
}

void RenderPipe::LoadProgram(GLubyte index)
{
	ProgramConfiguration& configuration = _configurations[index];
	
	GLuint vertexShader = LoadShader(configuration.vertexShader,   GL_VERTEX_SHADER);
	GLuint fragmentShader = LoadShader(configuration.fragmentShader, GL_FRAGMENT_SHADER);
	
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	_programs.push_back(program);
	_program = program;
}

class ShaderStrings : public std::vector<char*>
{
#define BUFFER_SIZE 4096
public:
	ShaderStrings()
	{
	}
	
	using std::vector<char*>::push_back;
	
	char* push_back(size_t& size)
	{
		size = BUFFER_SIZE;
		char* buffer = new char[BUFFER_SIZE];
		push_back(buffer);
		return buffer;
	}
	
	void clamp(size_t size)
	{
		(*lengths.end()) = size;
	}

	~ShaderStrings()
	{
		for( std::vector<char*>::iterator it = begin(); it != end(); it++ )
		{
			delete[] *it;
		}
	}
	
	std::vector<size_t> lengths;
};

GLuint RenderPipe::LoadShader(std::string& shaderFile, GLenum type)
{
	ShaderStrings strings;

	{
		std::string& fileName = shaderFile;
		std::ifstream file(fileName, std::ifstream::in);
		
		do
		{
			size_t size = 0;
			char* currentBuffer = strings.push_back(size);
			file.read(currentBuffer, size);
			strings.clamp(file.gcount());
		}
		while( !file.eof() );
	}

	GLint* stringLengths = new GLint[strings.size()];
	const char** stringArray = new const char*[strings.size()];
	
	GLuint index = 0;
	for( std::vector<char*>::iterator it = strings.begin(); it != strings.end(); it++, index++ )
	{
		stringArray[index] = *it;
		stringLengths[index] = BUFFER_SIZE;
	}
	
	{
		GLuint lastIndex = strings.size() - 1;
		stringLengths[lastIndex] = (strchr(stringArray[lastIndex], '\0') - stringArray[lastIndex]); 
	}
#undef BUFFER_SIZE

	GLuint shader = glCreateShader(type);
	
	glShaderSource
	(
		shader,
		strings.size(),
		stringArray,
		stringLengths
	);
	
	glCompileShader(shader);
	return shader;
}

void RenderPipe::Render()
{
	GLuint program = 0;
	
	GLint param = 0;
	
	glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &param);

	::Get<LightSetup>().ApplyTo(this);
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

IUniformValue<bool, 1>& RenderPipe::GetValue(IUniform<bool, 1>& uniform)
{
	return Get<bool, 1>(uniform);
}

IUniformValue<GLfloat, 1>& RenderPipe::GetValue(IUniform<GLfloat, 1>& uniform)
{
	return Get<GLfloat, 1>(uniform);
}

IUniformValue<GLfloat, 3>& RenderPipe::GetValue(IUniform<GLfloat, 3>& uniform)
{
	return Get<GLfloat, 3>(uniform);
}

IUniformValue<GLfloat, 4>& RenderPipe::GetValue(IUniform<GLfloat, 4>& uniform)
{
	return Get<GLfloat, 4>(uniform);
}

