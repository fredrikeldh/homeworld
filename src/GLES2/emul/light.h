
#ifndef _HW_GLES2_LIGHT_H_
#define _HW_GLES2_LIGHT_H_

#include "include.h"

class LightSetup : public GLPart<>
{
public:
	LightSetup();
	
	static GLfloat DARK[4];
	
	template<typename T>
	void Set(
		GLenum    pname,
		const T*  params
	);
		
	void Set(
		GLenum          light,
		GLenum          pname,
		const GLfloat*  params
	);
	
protected:
	
	class Light
	{
	public:
		Light();
	private:
		friend class LightSetup;
		friend class RENDER_PROCESSOR;
		Uniform<GLfloat, 4> ambient;
		Uniform<GLfloat, 4> diffuse;
		Uniform<GLfloat, 4> specular;
		Uniform<GLfloat, 4> position;
		Uniform<GLfloat, 3> direction;
		Uniform<GLfloat, 1> spot_exponent;
		Uniform<GLfloat, 1> spot_cutoff;
		Uniform<GLfloat, 1> constantAttenuation;
		Uniform<GLfloat, 1> linearAttenuation;
		Uniform<GLfloat, 1> quadraticAttenuation;
	};
private:
	friend class RENDER_PROCESSOR;
	Uniform<GLfloat, 4> ambient;
	GLenum color_control;
	bool local_viewer;
	bool two_sided; 
	Light lights[GL_MAX_LIGHTS];
	
	virtual void Apply(RENDER_PROCESSOR* renderer);
};

#endif //_HW_GLES2_LIGHT_H_

