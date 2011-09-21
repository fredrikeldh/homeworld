
#ifndef _HW_GLES2_CLIP_H_
#define _HW_GLES2_CLIP_H_

#include "include.h"

namespace gles2
{
	class ClipSetup : public GLPart
	{
	#define MAX_PLANE_COUNT 6
	public:
		ClipSetup();
		void SetClipPlane(GLenum, const GLfloat*);
	private:
		friend class RENDER_PROCESSOR;
		GLfloat planes[MAX_PLANE_COUNT][4];
	};
};

#endif //#define _HW_GLES2_CLIP_H_

