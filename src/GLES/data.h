
#include "include.h"
#include <cstring>
#include <vector>
#include <GLES2/gl2.h>

class Buffer
{
public:
	template<typename T>
	static void Copy(const T* source, T* target, const GLubyte size)
	{
		std::memcpy(target, source, sizeof(T) * size);
	}

	template<typename T, GLubyte SIZE>
	static void Copy(const T* source, T* target)
	{
		Copy<T>(source, target, SIZE);
	}

	template<typename T1, typename T2>
	static void Copy(const T1* source, T2* target, GLubyte size)
	{
		// Copy matrix
		for( ; size != 0; size--, target++, source++ )
		{
			*target = *source;
		}
	}

	template<typename T>
	static void Copy(const T* source, std::vector<T>& target, GLubyte size)
	{
		// Copy matrix
		for( typename std::vector< T >::iterator it = target.begin(); it != target.end() && size != 0; size--, it++, source++ )
		{
			*it = *source;
		}
	}

};

