
GLenum validCaps[] =
{
	GL_VERTEX_ARRAY,
	GL_NORMAL_ARRAY,
	GL_COLOR_ARRAY,
	GL_INDEX_ARRAY,
	GL_TEXTURE_COORD_ARRAY,
	GL_EDGE_FLAG_ARRAY,
	GL_FOG_COORD_ARRAY,
	GL_SECONDARY_COLOR_ARRAY
};

TYPE_INDEX_FUNCTION(validCaps)

void glEnableClientState(GLenum cap)
{
	short index = TYPE_INDEX_FUNCTION_NAME(cap);

	if( index == -1 )
	{
		glSetError(GL_INVALID_ENUM);
		return;
	}

	caps[index] = TRUE;
}

void glDisableClientState(GLenum cap)
{
	short index = TYPE_INDEX_FUNCTION_NAME(cap);

	if( index == -1 )
	{
		glSetError(GL_INVALID_ENUM);
		return;
	}

	caps[index] = FALSE;
}

GLenum shadeModel = GL_SMOOTH;

void glShadeModel(GLenum mode)
{
	if( shadeModel == mode )
		return;

	switch( mode )
	{
	case GL_FLAT:
	case GL_SMOOTH:
		shadeModel = GL_SMOOTH;
	default:
		glSetError(GL_INVALID_ENUM);
	}
}
