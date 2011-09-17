
#ifndef _HW_GLES2_LIGHT_H_
#define _HW_GLES2_LIGHT_H_

#include "include.h"
#include "../../GLES/render_component.h"
#include "uniform.h"

class LightSetup : public GLPart<>, public IRenderComponent
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
	
	virtual void ApplyTo(RENDER_PROCESSOR* renderer);
	
protected:
	class Light : public GLPart<>, public IRenderComponent
	{
	public:
		Light(GLubyte index);
		
		ONLY_MOVE(Light)
#if HAS_MOVE_ASSIGN_BUG
		Light& operator=(Light&& other);
#endif
	private:
		friend class LightSetup;
		friend class RENDER_PROCESSOR;
		
		virtual void ApplyTo(RENDER_PROCESSOR* renderer);

		std::string _prefix;
		
		Uniform<bool,    1> enabled;
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
	friend class std::vector<Light>;
	
private:
	friend class RENDER_PROCESSOR;
	Uniform<GLfloat, 4> ambient;
	GLenum color_control;
	bool local_viewer;
	bool two_sided; 
	std::vector<Light> _lights;
};

#endif //_HW_GLES2_LIGHT_H_

