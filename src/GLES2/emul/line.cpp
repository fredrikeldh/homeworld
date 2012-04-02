
#include "../gles2.h"

LineSetup::LineSetup():
	line_factor(1),
	line_pattern(0xFFFF)
{
}

void LineSetup::SetStripple(
	GLint     factor,
	GLushort  pattern)
{
	line_factor = clamp(factor, 1, 256);
	line_pattern = pattern;
}

void glLineStipple(
	GLint     factor,
	GLushort  pattern)
{
	Get<LineSetup>().SetStripple(factor, pattern);
}
