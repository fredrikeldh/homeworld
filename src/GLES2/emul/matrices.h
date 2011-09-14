
#ifndef _HW_GLES2_MATRICES_H_
#define _HW_GLES2_MATRICES_H_

#include "include.h"
#include <vector>

namespace gles2
{
	class MatrixSetup : public GLPart<>
	{
	public:
#define MATRIX_SIZE 16
		MatrixSetup();
		void SetActive(GLenum mode);
		GLenum GetMatrixMode();
		template<typename T>
		void GetMatrix(GLenum type, T* buffer)
		{
			Copy<GLfloat, T>(GetMatrixEntry(type).matrix, buffer, MATRIX_SIZE);
		};
		void GetActiveMatrix(GLfloat* buffer);
		void SetActiveMatrix(const GLfloat* buffer);
		void Push();
		void Pop();
		void MultiplyActive(const GLfloat* m);

		template<typename T>
		void Get(GLenum pname, T* params)
		{
			switch( pname )
			{
			case GL_MATRIX_MODE:
				*params = GetMatrixMode();
				break;
			case GL_PROJECTION_MATRIX:
			{
				GetMatrix<T>(GL_PROJECTION_MATRIX, params);
				break;
			}
			default:
				SetError<GL_INVALID_ENUM>();
				break;
			}
		};
	private:

		class MatrixEntry
		{
		public:
			MatrixEntry(MatrixEntry* previous);
			MatrixEntry* previous;
			GLfloat matrix[MATRIX_SIZE];
		};
		
		MatrixEntry& GetMatrixEntry(GLubyte type);
		MatrixEntry& GetMatrixEntry(GLenum type);
		
		MatrixEntry& GetActiveMatrixEntry();
		GLubyte GetMatrixIndex(GLenum mode);
		
		std::vector<MatrixEntry> _topMatrixEntries;
		GLubyte _activeMatrixIndex;
	};
};

#endif //_HW_GLES2_MATRICES_H_

