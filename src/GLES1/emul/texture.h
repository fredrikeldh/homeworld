
namespace gles1
{
	class TextureSetup : public GLPart<
	>
	{
	public:
		TextureSetup();
	private:
		GLfloat texcoord[16384];
		GLuint texcoord_count = 0;
	};
}

