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

	template<T SEARCH_VALUE, short INDEX, T One, T Two>
	static short GetInternal()
	{
		if( SEARCH_VALUE == One )
			return INDEX;

		// Try out the rest
		return GetInternal<SEARCH_VALUE, INDEX + 1, Two>();
	};

public:
	template<T SEARCH_VALUE, T One, T Two>
	static short Get()
	{
		return GetInternal<SEARCH_VALUE, 0, One, Two>();
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

	template<short INDEX, T One, T Two>
	static short GetInternal(GLenum value)
	{
		if( value == One )
			return INDEX;

		// Try out the rest
		return GetInternal<INDEX + 1, Two>(value);
	};
public:
	template<T One, T Two>
	static short Get(GLenum value)
	{
		return GetInternal<0, One, Two>(value);
	}
};

class GLPart
{
public:
	GLenum GetError()
	{
		GLenum error = glGetError();

		if( error != GL_NO_ERROR )
			return error;

		return errno;
	}

	template<GLenum ERROR>
	static void SetError()
	{
		errno = ERROR;
	}

	static void SetError(GLenum error)
	{
		errno = error;
	}

	ENABLE_MOVE_AND_COPY(GLPart)

protected:
	static const GLenum INVALID_INDEX;
	GLPart()
	{
	}

#if HAS_MOVE_ASSIGN_BUG
	GLPart& operator=(GLPart&)
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

	template<GLenum ONE>
	bool Evaluate(GLenum value)
	{
		short index = IndexSlow<GLenum>::Get<ONE>(value);

		bool isValid = (index >= 0);

		if( !isValid )
			SetError(GL_INVALID_ENUM);

		return isValid;
	}
};

#endif //_HW_GLES_GLPART_H_




