
PointSetup::PointSetup() :
	point_size(1)
{
}

void PointSetup::SetSize(GLfloat  size)
{
	if( size <= 0 )
	{
		SetError(GL_INVALID_VALUE);
		return;
	}
	
	point_size = size;
}


void glPointSize(GLfloat  size)
{
	Get<PointSize>().SetSize(size);
}

