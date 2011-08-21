static GLfloat gles_texcoord[16384];

static unsigned int gles_texcoord_count = 0;

void glTexCoord2f(GLfloat s, GLfloat t) {
    gles_texcoord[gles_texcoord_count++] = s;
    gles_texcoord[gles_texcoord_count++] = t;
}
