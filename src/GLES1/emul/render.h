#ifndef _HW_GLES1_RENDER_H_
#define _HW_GLES1_RENDER_H_

#include "include.h"
#include "vertex.h"

namespace gles1
{
	class RenderPipe : public GLPart
	{
	public:
		RenderPipe();
		virtual void Render();
		void Render(GLenum  mode, GLint  first, GLsizei  count);
		void Start(GLenum enume);
		void End();
		
		bool is_texture_enabled(const VertexSetup& vertexData) const;
		bool is_color_enabled(const VertexSetup& vertexData) const;
		bool is_normal_enabled(const VertexSetup& vertexData) const;
	private:
	
		bool _immediate;
		GLenum _mode;
	};
};

#endif //_HW_GLES1_RENDER_H_

