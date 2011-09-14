
namespace gles1
{
	class NormalSetup : public GLPart<>
	{
	public:
		NormalSetup();
		void Get(const GLfloat*);
		void Set(GLfloat x, GLfloat y, GLfloat z);
	private:
		GLfloat _current[3];
	};
};

