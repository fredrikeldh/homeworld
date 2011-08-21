
struct vertex_pointer_t
{
	GLint         size;
	ubyte         typeIndex;
	GLsizei       stride;
	const GLvoid* pointer
	
} vertex_pointer;

TYPE_INDEX_FUNCTION(
	GL_SHORT,
	GL_INT,
	GL_FLOAT,
	GL_DOUBLE
)

void glVertexPointer(
	GLint          size,
	GLenum         type,
	GLsizei        stride,
	const GLvoid*  pointer)
{
	if( size < 2 || size > 4 || stride < 0)
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
	
	vertex_pointer.size = size;
	vertex_pointer.typeIndex = index;
	vertex_pointer.stride = stride;
	vertex_pointer.pointer = pointer;
}

