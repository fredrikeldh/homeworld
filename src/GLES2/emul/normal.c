
struct normal_pointer_t
{
	ubyte         typeIndex;
	GLsizei       stride;
	const GLvoid* pointer;
} normal_pointer;

GLenum validTypes[] =
{
		GL_BYTE,
		GL_SHORT,
		GL_INT,
		GL_FLOAT,
		GL_DOUBLE
};

TYPE_INDEX_FUNCTION(validTypes)

void glNormalPointer(
	GLenum        type,
	GLsizei       stride,
	const GLvoid* pointer)
{
	if( stride < 0 )
	{
		glSetError(GL_INVALID_VALUE);
		return;
	}

	short index = TYPE_INDEX_FUNCTION_NAME(type);

	if( index == -1 )
	{
		glSetError(GL_INVALID_ENUM);
		return;
	}

	normal_pointer.typeIndex = index;
	normal_pointer.stride = stride;
	normal_pointer.pointer = pointer;
}
