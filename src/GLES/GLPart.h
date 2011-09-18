#ifndef _HW_GLES_GLPART_H_
#define _HW_GLES_GLPART_H_

#include "include.h"
#include "data.h"
#include <errno.h>
#include <vector>

template<typename T>
class IndexFast
{
private:
	template<T SEARCH_VALUE, short INDEX>
	static short GetInternal()
	{
		return -1;
	};

	template<T SEARCH_VALUE, short INDEX, GLenum One>
	static short GetInternal()
	{
		if( SEARCH_VALUE == One )
			return INDEX;
		else
			return GetInternal<SEARCH_VALUE, INDEX>(); // Not found
	};

	template<T SEARCH_VALUE, short INDEX, T One, T Two, T... Others>
	static short GetInternal()
	{
		if( SEARCH_VALUE == One )
			return INDEX;

		// Try out the rest
		return GetInternal<T, SEARCH_VALUE, INDEX + 1, Two, Others...>();
	};

public:
	template<T SEARCH_VALUE, T One, T Two, T... Others>
	static short Get()
	{
		return GetInternal<SEARCH_VALUE, 0, One, Two, Others...>();
	}
};

template<typename T>
class IndexSlow
{
private:
	template<short INDEX>
	static short GetInternal(GLenum)
	{
		return -1;
	};
	
	template<short INDEX, T One>
	static short GetInternal(GLenum value)
	{
		if( value == One )
			return INDEX;
		else
			return GetInternal<INDEX>(value); // Not found
	};

	template<short INDEX, T One, T Two, T... Others>
	static short GetInternal(GLenum value)
	{
		if( value == One )
			return INDEX;
	
		// Try out the rest
		return GetInternal<INDEX + 1, Two, Others...>(value);
	};
public:
	template<T One, T Two, T... Others>
	static short Get(GLenum value)
	{
		return GetInternal<0, One, Two, Others...>(value);
	}
};

template<GLenum... ValidEnums>
class GLPart
{
public:

	ENABLE_MOVE_AND_COPY(GLPart)

protected:
	static const GLenum INVALID_INDEX;
	GLPart()
	{
	}
	
#if HAS_MOVE_ASSIGN_BUG
	GLPart& operator=(GLPart&&)
	{
		return *this;
	}
#endif
	
protected:
	template<typename T>
	static void Copy(const T* source, std::vector<T>& target, GLubyte size)
	{
		Buffer::Copy<T>(source, target, size);
	}

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
	
	short GetIndex(GLenum value)
	{
		return IndexSlow<GLenum>::Get<ValidEnums...>(value);
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
		short index = IndexSlow<GLenum>::Get<ONE, VALIDS ...>(value);

		bool isValid = (index >= 0);

		if( !isValid )
			SetError(GL_INVALID_ENUM);
	
		return isValid;
	}
};

#endif //_HW_GLES_GLPART_H_




