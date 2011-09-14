
#ifndef _HW_GLES2_STATE_H_
#define _HW_GLES2_STATE_H_

#include "include.h"
#include "../../GLES1/emul/state.h"

namespace gles2
{
	class StateSetup : public gles1::StateSetup
	{
	public:
		StateSetup();
		void SetState(GLenum cap, bool value);
		void SetModel(GLenum mode);
	protected:
		virtual RenderPipe& GetRenderer();
	private:
		friend class RENDER_PROCESSOR;
		GLenum caps[8];
		GLenum shadeModel;
	};
};

#endif //_HW_GLES2_STATE_H_

