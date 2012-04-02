#ifndef _HW_GLES2_ALPHA_H_
#define _HW_GLES2_ALPHA_H_

#include "include.h"

class AlphaSetup : public GLPart
{
public:
	AlphaSetup();
public:
	void SetFunc(
		GLenum    func,
		GLclampf  ref);
private:
	friend class RENDER_PROCESSOR;
	GLenum   func;
	GLclampf ref;
};

#endif //_HW_GLES2_ALPHA_H_
