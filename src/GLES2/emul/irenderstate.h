#ifndef _HW_GLES2_IRENDERSTATE_H_
#define _HW_GLES2_IRENDERSTATE_H_

#include "include.h"
#include "iuniform.h"
#include "iuniformvalue.h"

namespace gles2
{
	class IRenderState
	{
	protected:
		IRenderState()
		{
		}
	public:

		virtual IUniformValue<bool,    1>& GetValue(IUniform<bool,    1>& uniform) = 0;
		virtual IUniformValue<GLfloat, 1>& GetValue(IUniform<GLfloat, 1>& uniform) = 0;
		virtual IUniformValue<GLfloat, 3>& GetValue(IUniform<GLfloat, 3>& uniform) = 0;
		virtual IUniformValue<GLfloat, 4>& GetValue(IUniform<GLfloat, 4>& uniform) = 0;
	};
}

#endif //_HW_GLES2_IRENDERSTATE_H_

