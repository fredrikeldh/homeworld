#ifndef _HW_GLES2_LINE_H_
#define _HW_GLES2_LINE_H_

#include "include.h"

class LineSetup : public GLPart
{
public:
	LineSetup();
	void SetStripple(
		GLint     factor,
		GLushort  pattern);
private:
	friend class RENDER_PROCESSOR;
	GLushort line_factor;
	GLushort line_pattern;
};

#endif //_HW_GLES2_LINE_H_
