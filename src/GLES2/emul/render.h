
#ifndef _HW_GLES2_RENDER_H_
#define _HW_GLES2_RENDER_H_

#include "include.h"
#include "../../GLES1/emul/render.h"
#include "light.h"

namespace gles2
{
	class RenderPipe : public gles1::RenderPipe
	{
	public:
		virtual void Render();
	protected:
		void preLight(const LightSetup& setup, GLuint * const lightMap);
	};
};


#endif //_HW_GLES2_RENDER_H_

