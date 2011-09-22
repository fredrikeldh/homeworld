
#include "texture.h"

TextureSetup::TextureSetup() :
	GLPart()
{
}

void TextureSetup::GetCoord(GLfloat* buffer)
{
	Copy(_current.data(), buffer, 2);
}

void TextureSetup::SetCoord(GLfloat s, GLfloat t)
{
	_current.push_back(s, t);
}

void glTexCoord2f(GLfloat s, GLfloat t) {
	Get<TextureSetup>().SetCoord(s, t);
}
