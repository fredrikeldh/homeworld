#ifndef _HW_GLES2_GLPART_H_
#define _HW_GLES2_GLPART_H_

#include "include.h"
#include "../../GLES/emul/error.h"

template<GLenum... ValidEnums>
class GLPart
{
protected:
	GLPart()
	{
	};
private:
	
	template<GLenum One>
	bool eval(GLenum value)
	{
		return value == One;
	};

	template<GLenum One, GLenum Two, GLenum... Others>
	bool eval(GLenum value)
	{
		if( eval<One>(value) )
			return true;
	
		// Try out the rest
		return eval<Two, Others...>(value);
	};
protected:
	template<typename T>
	void Copy(const T* source, T* target, GLubyte size)
	{
		Copy<T, T>(source, target, size);
	}
	
	template<typename T1, typename T2>
	void Copy(const T1* source, T2* target, GLubyte size)
	{
		// Copy matrix
		for( ; size != 0; size-- )
		{
			*target = *source;
			target++;
			source++;
		}
	}
	
	void SetError(GLenum error)
	{
		glSetError(error);
	}
	
public:
	bool Evaluate(GLenum value)
	{
		bool isValid = eval<ValidEnums...>(value);

		if( !isValid )
			SetError(GL_INVALID_ENUM);
	
		return isValid;
	};
};

#endif //_HW_GLES2_GLPART_H_




