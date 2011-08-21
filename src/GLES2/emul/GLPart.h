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
	
	template<short INDEX, GLenum One>
	bool GetIndex(GLenum value)
	{
		if( value == One )
			return INDEX;
		else
			return -1; // Not found
	};

	template<short INDEX, GLenum One, GLenum Two, GLenum... Others>
	bool GetIndex(GLenum value)
	{
		if( value == One )
			return INDEX;
	
		// Try out the rest
		return GetIndex<INDEX + 1, Two, Others...>(value);
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
	
	short GetIndex(GLenum value)
	{
		return GetIndex<0, ValidEnums...>(value);
	}
	
	bool Evaluate(GLenum value)
	{
		short index = GetIndex(value);

		bool isValid = (index >= 0);

		if( !isValid )
			SetError(GL_INVALID_ENUM);
	
		return isValid;
	};
};

#endif //_HW_GLES2_GLPART_H_




