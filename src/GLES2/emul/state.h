
#ifndef _HW_GLES2_STATE_H_
#define _HW_GLES2_STATE_H_

#include "include.h"

namespace gles2
{
	class StateSetup : public GLPart<>
	{
	public:
		StateSetup();
		void SetState(GLenum cap, bool value);
		void SetModel(GLenum mode);
	private:
		friend class RENDER_PROCESSOR;
		GLenum caps[8];
		GLenum shadeModel;
	};
};

#endif //_HW_GLES2_STATE_H_

