#ifndef _HW_GLES1_RENDER_H_
#define _HW_GLES1_RENDER_H_

#include "include.h"

namespace gles1
{
	class RenderPipe : public GLPart<>
	{
	public:
		virtual void Render();
		void Start(GLenum enume);
		void End();
	private:
		bool immediate;
		GLenum mode;
	};
};

#endif //_HW_GLES1_RENDER_H_

