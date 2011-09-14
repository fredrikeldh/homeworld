#ifndef _HW_GLES_GLPART_H_
#define _HW_GLES_GLPART_H_

#include "include.h"
#include "data.h"
#include <errno.h>

template<GLenum... ValidEnums>
class GLPart
{
protected:
	static const GLenum INVALID_INDEX;
	GLPart()
	{
	};
private:
	
	template<short INDEX, GLenum One>
	bool GetIndexInternal(GLenum value)
	{
		if( value == One )
			return INDEX;
		else
			return GetIndex<INDEX>(value); // Not found
	};

	template<short INDEX, GLenum One, GLenum Two, GLenum... Others>
	bool GetIndexInternal(GLenum value)
	{
		if( value == One )
			return INDEX;
	
		// Try out the rest
		return GetIndex<INDEX + 1, Two, Others...>(value);
	};
	
	template<short INDEX>
	bool GetIndexInternal(GLenum)
	{
		return -1;
	};
protected:
	template<typename T>
	static void Copy(const T* source, T* target, GLubyte size)
	{
		Buffer::Copy<T>(source, target, size);
	}
	
	template<typename T1, typename T2>
	static void Copy(const T1* source, T2* target, GLubyte size)
	{
		Buffer::Copy<T1, T2>(source, target, size);
	}
	
	GLenum GetError()
	{
		GLenum error = glGetError();
		
		if( error != GL_NO_ERROR )
			return error;

		return errno;
	}
	
	template<GLenum ERROR>
	void SetError()
	{
		errno = ERROR;
	}
	
	void SetError(GLenum error)
	{
		errno = error;
	}
	
	template<GLenum One, GLenum Two, GLenum... Others>
	short GetIndex(GLenum value)
	{
		return GetIndexInternal<0, One, Two, Others...>(value);
	}
	
	short GetIndex(GLenum value)
	{
		return GetIndex<ValidEnums...>(value);
	}
	
	bool Evaluate(GLenum value)
	{
		short index = GetIndex(value);

		bool isValid = (index >= 0);

		if( !isValid )
			SetError(GL_INVALID_ENUM);
	
		return isValid;
	};
	
	template<GLenum ONE, GLenum...VALIDS>
	bool Evaluate(GLenum value)
	{
		short index = GetIndex<ONE, VALIDS ...>(value);

		bool isValid = (index >= 0);

		if( !isValid )
			SetError(GL_INVALID_ENUM);
	
		return isValid;
	}
public:
	virtual void Apply(RENDER_PROCESSOR* renderer);
};

#endif //_HW_GLES_GLPART_H_




