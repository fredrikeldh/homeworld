#ifndef _HW_GLES1_STATE_H_
#define _HW_GLES1_STATE_H_

#include "include.h"

namespace gles1
{
	class StateSetup : public GLPart<>
	{
	public:
		StateSetup();
/*
		template<GLEnum T>
		void Start();
*/
		void Start(GLenum enume);
		void End();
	private:
		friend class RENDER_PROCESSOR;
		bool immediate;
		GLenum mode;
	};
};

#endif //_HW_GLES1_STATE_H_
