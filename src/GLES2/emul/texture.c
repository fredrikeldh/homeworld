const GLenum validGLES2TextureTypes[] =
{
	GL_SHORT,
	GL_INT,
	GL_FLOAT,
	GL_DOUBLE
};

TYPE_INDEX_FUNCTION(validGLES2TextureTypes)

void glTexCoordPointer(
	GLint          size,
	GLenum         type,
	GLsizei        stride,
	const GLvoid*  pointer)
{

	if( size < 1 || size > 4 )
	{
		glSetError(GL_INVALID_VALUE);
		return;
	}
	
	ubyte index = TYPE_INDEX_FUNCTION_NAME(type);
	
	if( glGetErrorX() != GL_NO_ERROR )
		return;

	glContext.texturePointer.size = size;
	glContext.texturePointer.typeIndex = index;
	glContext.texturePointer.stride = stride;
	glContext.texturePointer.pointer = pointer;
}

void init()
{
	glContext.texturePointer.size = 4;
	glContext.texturePointer.typeIndex = 3;
	glContext.texturePointer.stride = 0;
	glContext.texturePointer.pointer = NULL;
}

