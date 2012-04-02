
#ifndef _HW_GLES_UNIFORM_H_
#define _HW_GLES_UNIFORM_H_

#include "include.h"
#include "iuniform.h"
#include "iuniformvalue.h"
#include "../../GLES/GLPart.h"
#include "../../GLES/render_component.h"
#include "irenderstate.h"
#include <string>

template<typename T, GLubyte NUMBER>
class BaseUniform : public GLPart, public IUniform<T, NUMBER>
{
protected:
	std::vector<T> _array;

	BaseUniform(const std::string& name):
		GLPart(),
		IUniform<T, NUMBER>(std::move(name)),
		_array(NUMBER)
	{
	};

public:
	BaseUniform(const T values[NUMBER], const std::string& name):
		BaseUniform(std::move(name))
	{
		for( GLubyte i = 0; i != NUMBER; i++ )
		{
			_array[i] = values[i];
		}
	};

	ONLY_MOVE(BaseUniform)

#if HAS_MOVE_ASSIGN_BUG
	BaseUniform& operator=(BaseUniform& other)
	{
		GLPart::operator=(std::move(other));
		IUniform<T, NUMBER>::operator=(std::move(other));
		_array = std::move(other._array);
		return *this;
	}
#endif

	bool operator==(const T* other) const
	{
		GLubyte index = 0;
		for( typename std::vector<T>::const_iterator it = _array.begin(); it != _array.end(); it++, index++ )
		{
			if( *it != other[index] )
				return false;
		}

		return true;
	}

	bool operator!=(const T* other) const
	{
		return !(*this == other);
	};

	virtual void Set(const T* values)
	{
		Copy(values, _array, NUMBER);
	}

	virtual void ApplyTo(IRenderState* pRenderer)
	{
		IUniform<T, NUMBER>::ApplyTo(pRenderer);
		IUniformValue<T, NUMBER>& value = pRenderer->GetValue(*this);
		value.Set(_array);
	}
};

template<typename T, unsigned char NUMBER>
class Uniform : public BaseUniform<T, NUMBER>
{
public:
	ONLY_MOVE(Uniform)
#if HAS_MOVE_ASSIGN_BUG
	Uniform& operator=(Uniform& other)
	{
		BaseUniform<T, NUMBER>::operator=(std::move(other));
		return *this;
	}
#endif
};

template<typename T>
class Uniform<T, 3> : public BaseUniform<T, 3>
{
public:
	ONLY_MOVE(Uniform)
#if HAS_MOVE_ASSIGN_BUG
	Uniform& operator=(Uniform& other)
	{
		BaseUniform<T, 3>::operator=(std::move(other));
		return *this;
	}
#endif

	using BaseUniform<T, 3>::Set;
	using BaseUniform<T, 3>::ApplyTo;
	void Set(T x, T y, T z)
	{
		BaseUniform<T, 3>::_array[0] = x;
		BaseUniform<T, 3>::_array[1] = y;
		BaseUniform<T, 3>::_array[2] = z;
	}

	Uniform(T x, T y, T z, std::string& name):
		BaseUniform<T, 3>(std::move(name))
	{
		Set(x, y, z);
	}
};

template<typename T>
class Uniform<T, 4> : public BaseUniform<T, 4>
{
public:
	ONLY_MOVE(Uniform)
#if HAS_MOVE_ASSIGN_BUG
	Uniform& operator=(Uniform& other)
	{
		BaseUniform<T, 4>::operator=(std::move(other));
		return *this;
	}
#endif

	using BaseUniform<T, 4>::Set;
	using BaseUniform<T, 4>::ApplyTo;
	void Set(T x, T y, T z, T w)
	{
		BaseUniform<T, 4>::_array[0] = x;
		BaseUniform<T, 4>::_array[1] = y;
		BaseUniform<T, 4>::_array[2] = z;
		BaseUniform<T, 4>::_array[3] = w;
	}

	Uniform(T x, T y, T z, T w, std::string& name):
		BaseUniform<T, 4>(std::move(name))
	{
		Set(x, y, z, w);
	}
};

template<typename T>
class Uniform<T, 1> : public BaseUniform<T, 1>
{
public:
	ONLY_MOVE(Uniform)
#if HAS_MOVE_ASSIGN_BUG
	Uniform& operator=(Uniform& other)
	{
		BaseUniform<T, 1>::operator=(std::move(other));
		return *this;
	}
#endif

	using BaseUniform<T, 1>::Set;
	using BaseUniform<T, 1>::ApplyTo;
	void Set(T value)
	{
		BaseUniform<T, 1>::_array[0] = value;
	};

	Uniform(T value, std::string& name):
		BaseUniform<T, 1>(std::move(name))
	{
		Set(value);
	}
};

#endif //_HW_GLES_UNIFORM_H_


