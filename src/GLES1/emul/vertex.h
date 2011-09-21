
#ifndef _HW_GLES1_VERTEX_H_
#define _HW_GLES1_VERTEX_H_

#include "include.h"
#include <array>

namespace gles1
{
	class VertexSetup : public GLPart
	{
	public:
		VertexSetup();
		void Set(GLfloat x, GLfloat y, GLfloat z);
		
		template<typename T, unsigned int SIZE>
		class Array
		{
		private:
			std::array<T, SIZE> _array;
			GLfloat _count;
		public:
			Array():
				_array(),
				_count(0)
			{
			}
			
			~Array()
			{
			}
			
			operator const T*() const
			{
				return _array.data();
			}
			
			T& operator[] (unsigned int index)
			{
				if( _count >= index )
					throw -1;
				
				return _array[index];
			}
			
			void push_back(GLfloat value)
			{
				if( _count == SIZE )
					throw -1; //TODO: replace with exception
				
				_array[_count] = value;
				_count++;
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
	private:
		friend class RenderPipe;
		unsigned int _count;
		unsigned int _vertex_dimensions;
		
		// 3
		Array<GLfloat, 16384> _vertices;
		// 4
		Array<GLfloat, 16384> _colors;
		
		// 3
		Array<GLfloat, 16384> _normals;
		
		Array<GLfloat, 16384> _texCoords;
	};
};

#endif //_HW_GLES1_VERTEX_H_

