#ifndef _HW_GLES1_RENDER_H_
#define _HW_GLES1_RENDER_H_

#include "include.h"

namespace gles1
{
	class RenderPipe : public GLPart<>
	{
	public:
		virtual void Render();
	};
};

#endif //_HW_GLES1_RENDER_H_

