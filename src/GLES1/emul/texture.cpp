
#include "texture.h"

TextureSetup::TextureSetup() :
	GLPart(),
	texcoord_count(0)
{
}

void TextureSetup::SetCoord(GLfloat s, GLfloat t)
{
	gles_texcoord[gles_texcoord_count++] = s;
	gles_texcoord[gles_texcoord_count++] = t;
}

void glTexCoord2f(GLfloat s, GLfloat t) {
	Get<TextureSetup>().SetCoord(s, t);
}
