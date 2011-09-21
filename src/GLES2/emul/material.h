
#ifndef _HW_GLES2_MATERIAL_H_
#define _HW_GLES2_MATERIAL_H_

#include "include.h"

class MaterialSetup : public GLPart
{
public:
	template<typename T>
	void Set(
		GLenum         face,
		GLenum         pname,
		const T* params);
private:
	class Side
	{
	public:
		Side();
	private:
		friend class MaterialSetup;
		friend class RENDER_PROCESSOR;
		GLfloat ambient[4];
		GLfloat diffuse[4];
		GLfloat specular[4];
		GLfloat emission[4];
		GLubyte shininess;
		GLint   color_indices[4];
	};

	friend class RENDER_PROCESSOR;
	GLubyte getFaceBitMap(GLenum face);
	template <typename T>
	void setAmbient(const GLubyte cullBits, const T* params);

	template <typename T>
	void setDiffuse(const GLubyte cullBits, const T* params);
	static const GLubyte MFRONT;
	static const GLubyte MBACK;
	
	Side front;
	Side back;
};

#endif // _HW_GLES2_MATERIAL_H_

