
#ifndef _HW_GLES2_NORMAL_H_
#define _HW_GLES2_NORMAL_H_

#include "include.h"
#include "../../GLES1/emul/normal.h"

namespace gles2
{
	class NormalSetup : public gles1::NormalSetup
	{
	public:
		NormalSetup();
		void SetPointer(
			GLenum        type,
			GLsizei       stride,
			const GLvoid* pointer);
	private:
		GLenum        type;
		GLsizei       stride;
		const GLvoid* pointer;
	};
};

#endif //_HW_GLES2_NORMAL_H_

