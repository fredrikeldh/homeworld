
#include "texture.h"

TextureSetup::TextureSetup() :
	GLPart(),
	texcoord_count(0)
{
}

void TextureSetup::SetCoord(GLfloat s, GLfloat t)
{
	texcoord[texcoord_count++] = s;
	texcoord[texcoord_count++] = t;
}

void glTexCoord2f(GLfloat s, GLfloat t) {
	Get<TextureSetup>().SetCoord(s, t);
}
