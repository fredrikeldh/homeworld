
class StateSetup : public GLPart<
	GL_VERTEX_ARRAY,
	GL_NORMAL_ARRAY,
	GL_COLOR_ARRAY,
	GL_INDEX_ARRAY,
	GL_TEXTURE_COORD_ARRAY,
	GL_EDGE_FLAG_ARRAY,
	GL_FOG_COORD_ARRAY,
	GL_SECONDARY_COLOR_ARRAY>
{
public:
	StateSetup();
	void SetState(GLenum cap, bool value);
	void SetModel(GLenum mode);
	GLenum caps[8];
	GLenum shadeModel;
};

