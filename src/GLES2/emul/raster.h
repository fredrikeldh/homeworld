
#include "include.h"

namespace gles2
{
	class RasterSetup : public GLPart<
	>
	{
	public:
		RasterSetup();
		void Set(GLfloat x, GLfloat y);
		GLfloat position[2];
	};
}

