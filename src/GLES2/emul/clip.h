
#ifndef _HW_GLES2_CLIP_H_
#define _HW_GLES2_CLIP_H_

#include "include.h"

class ClipSetup : public GLPart<>
{
public:
	ClipSetup();
	void SetClipPlane(GLenum, const GLfloat*);
	GLfloat planes[GL_MAX_CLIP_PLANES][4];
};

#endif //#define _HW_GLES2_CLIP_H_

