
#ifndef _HW_GLES_UNIFORM_H_
#define _HW_GLES_UNIFORM_H_

#include "include.h"
#include "GLPart.h"
#include <string>

template<typename T>
class BaseUniform : public GLPart<>
{
public:
	virtual bool operator==(const T* other) const = 0;
	
	bool operator!=(const T* other) const
	{
		return !(*this == other);
	};
private:
	std::string name;
protected:
	BaseUniform(const char* name):
		GLPart(),
		name(name)
	{
	};
};

template<typename T, unsigned char NUMBER>
class Uniform
{
};

template<typename T>
class Uniform<T, 3> : public BaseUniform<T>
{
private:
	T _array[3];
public:
	Uniform(T x, T y, T z, const char* name):
		BaseUniform<T>(name),
		_array({x, y, z})
	{};
	
	bool operator==(const T* other) const
	{
		return memcmp(_array, other, 3) == 0;
	};
	
	void Set(T x, T y, T z)
	{
		_array[0] = x;
		_array[1] = y;
		_array[2] = z;
	};
	
	void Set(const T* values)
	{
		Copy(values, _array, 3);
	};
};

template<typename T>
class Uniform<T, 4> : public BaseUniform<T>
{
private:
	T _array[4];
public:
	Uniform(T x, T y, T z, T w, const char* name):
		BaseUniform<T>(name),
		_array({x, y, z, w})
	{};
	
	bool operator==(const T* other) const
	{
		return memcmp(_array, other, 4) == 0;
	};
	
	void Set(T x, T y, T z, T w)
	{
		_array[0] = x;
		_array[1] = y;
		_array[2] = z;
		_array[3] = w;
	};
	
	void Set(const T* values)
	{
		Copy(values, _array, 4);
	};
};

template<typename T>
class Uniform<T, 1> : public BaseUniform<T>
{
private:
	T value;
	std::string name;
public:
	Uniform(T value, const char* name):
		BaseUniform<T>(name),
		value(value)
	{
	}
	
	bool operator==(const T* other) const
	{
		return value == *other;
	};
	
	void Set(T value)
	{
		this->value = value;
	};
	
	void Set(const T* values)
	{
		value = *values;
	};
};

#endif //_HW_GLES_UNIFORM_H_


