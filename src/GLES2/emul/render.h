
#ifndef _HW_GLES2_RENDER_H_
#define _HW_GLES2_RENDER_H_

#include "include.h"
#include "../../GLES1/emul/render.h"
#include "iuniform.h"
#include "iuniformvalue.h"
#include "light.h"
#include <string>
#include <vector>

namespace gles2
{
	template<typename T, GLubyte NUMBER>
	class UniformValue
	{
	};

	template<>
	class UniformValue<bool, 1> : public IUniformValue<bool, 1>, public IUniform<bool, 1>::ICustomData
	{
	public:

		UniformValue(GLint location):
			IUniformValue<bool, 1>(location), IUniform<bool, 1>::ICustomData()
		{
		}

		void Set(const bool* array)
		{
			Set(array[0]);
		}

		void Set(const std::vector<bool>& array)
		{
			Set(array[0]);
		}

		void Set(bool value)
		{
			glUniform1i(location, value ? 1 : 0);
		}
	};

	template<>
	class UniformValue<GLfloat, 1> : public IUniformValue<GLfloat, 1>, public IUniform<GLfloat, 1>::ICustomData
	{
	public:

		UniformValue(GLint location):
			IUniformValue<GLfloat, 1>(location), IUniform<GLfloat, 1>::ICustomData()
		{
		}

		void Set(const GLfloat* array)
		{
			Set(array[0]);
		}

		void Set(const std::vector<GLfloat>& array)
		{
			Set(array[0]);
		}

		void Set(GLfloat value)
		{
			glUniform1f(location, value);
		}
	};

	template<>
	class UniformValue<GLfloat, 3> : public IUniformValue<GLfloat, 3>, public IUniform<GLfloat, 3>::ICustomData
	{
	public:
		UniformValue(GLint location):
			IUniformValue<GLfloat, 3>(location), IUniform<GLfloat, 3>::ICustomData()
		{
		}

		void Set(const GLfloat* array)
		{
			glUniform3fv(location, 3, array);
		}

		void Set(const std::vector<GLfloat>& array)
		{
			glUniform3f(location, array[0], array[1], array[2]);
		}
	};

	template<>
	class UniformValue<GLfloat, 4> : public IUniformValue<GLfloat, 4>, public IUniform<GLfloat, 4>::ICustomData
	{
	public:
		UniformValue(GLint location):
			IUniformValue<GLfloat, 4>(location), IUniform<GLfloat, 4>::ICustomData()
		{
		}

		void Set(const GLfloat* array)
		{
			glUniform4fv(location, 4, array);
		}

		void Set(const std::vector<GLfloat>& array)
		{
			glUniform4f(location, array[0], array[1], array[2], array[3]);
		}
	};

	class RenderPipe : public gles1::RenderPipe, public IRenderState
	{
	private:
		class ProgramConfiguration
		{
		private:
			friend class RenderPipe;
			std::string vertexShader;
			std::string fragmentShader;
		};

		std::vector<ProgramConfiguration> _configurations;

		std::vector<GLuint> _programs;

		GLuint _program;

		template<typename T, GLubyte NUMBER>
		IUniformValue<T, NUMBER>& Get(IUniform<T, NUMBER>& uniform)
		{
			//TODO: find type safe way to do this

			// See whether we saved information earlier
			UniformValue<T, NUMBER>* uniformInfo = (UniformValue<T, NUMBER>*)uniform.GetCustomData();

			if( !uniformInfo )
			{
				GLint location = glGetUniformLocation
				(
					_program,
					uniform.GetName().c_str()
				);

				if( location == -1 )
					maPanic(-1, "IUniformValue");

				uniformInfo = new UniformValue<T, NUMBER>(location);
				uniform.SetCustomData
				(
					std::unique_ptr< typename IUniform<T, NUMBER >::ICustomData >(uniformInfo)
				);
			}

			return *uniformInfo;
		}

	public:
		RenderPipe();
		virtual void Render();

		virtual IUniformValue<bool   , 1>& GetValue(IUniform<bool   , 1>& uniform);
		virtual IUniformValue<GLfloat, 1>& GetValue(IUniform<GLfloat, 1>& uniform);
		virtual IUniformValue<GLfloat, 3>& GetValue(IUniform<GLfloat, 3>& uniform);
		virtual IUniformValue<GLfloat, 4>& GetValue(IUniform<GLfloat, 4>& uniform);

	protected:
		GLuint LoadShader(std::string& shaderFile, GLenum type);
		void LoadProgram(GLubyte index);
	};
};


#endif //_HW_GLES2_RENDER_H_

