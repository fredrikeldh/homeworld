
#ifndef _HW_GLES2_STATE_H_
#define _HW_GLES2_STATE_H_

#include "include.h"

namespace gles2
{
	class StateSetup : public GLPart<>, public IRenderComponent
	{
	public:
		StateSetup();
		void SetState(GLenum cap, bool value);
		void SetModel(GLenum mode);
		
		virtual void ApplyTo(IRenderState* pRenderer);
	protected:
	
		// Compile time version
		template<GLenum value>
		short GetStateIndex()
		{
			return IndexFast<GLenum>::Get
			<
				value,
				GL_VERTEX_ARRAY,
				GL_NORMAL_ARRAY,
				GL_COLOR_ARRAY,
				GL_TEXTURE_COORD_ARRAY
			>();
		}
		
		// Runtime version
		short GetStateIndex(GLenum value)
		{
			return IndexSlow<GLenum>::Get
			<
				GL_VERTEX_ARRAY,
				GL_NORMAL_ARRAY,
				GL_COLOR_ARRAY,
				GL_TEXTURE_COORD_ARRAY
			>(value);
		}
	private:
		friend class RENDER_PROCESSOR;
		GLenum caps[8];
		GLenum shadeModel;
	};
};

#endif //_HW_GLES2_STATE_H_

