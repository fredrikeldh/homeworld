#ifndef _HW_GLES1_ARRAY_H_
#define _HW_GLES1_ARRAY_H_

#include "include.h"
#if defined(MAPIP) && !defined(__arm__)
#include <vector>
namespace std {
	template<class T, unsigned int SIZE>
	class array : public vector<T> {
	public:
		array() {
			this->resize(SIZE);
		}
	};
}
#else
#include <array>
#endif

template<typename T, unsigned int SIZE>
class Array
{
private:
	std::array<T, SIZE> _array;
	unsigned int _count;
public:
	Array():
		_array(),
		_count(0)
	{
	}

	void push_back(const T& value)
	{
		if( _count == SIZE )
			maPanic(-1, "Array");

		_array[_count] = value;
		_count++;
	}

#if 0
	Array(std::initializer_list<T> list):
		_array(),
		_count(0)
	{
		for( typename std::initializer_list<T>::iterator it = list.begin(); it != list.end(); it++ )
		{
			push_back(*it);
		}
	}
#endif

	~Array()
	{
	}

	const T* data() const
	{
		return _array.data();
	}

	T& operator[] (unsigned int index)
	{
		if( _count >= index )
			maPanic(-1, "Array::[]");

		return _array[index];
	}

	void push_back(const T& v1, const T& v2)
	{
		push_back(v1);
		push_back(v2);
	}

	void push_back(const T& v1, const T& v2, const T& v3)
	{
		push_back(v1);
		push_back(v2);
		push_back(v3);
	}

	void push_back(const T& v1, const T& v2, const T& v3, const T& v4)
	{
		push_back(v1);
		push_back(v2);
		push_back(v3);
		push_back(v4);
	}

	unsigned int size() const
	{
		return _count;
	}

	void clear()
	{
		_count = 0;
	}
};
#endif //_HW_GLES1_ARRAY_H_

