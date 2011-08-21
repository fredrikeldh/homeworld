
static GLfloat gles_colors[16384];
static unsigned int gles_color_count = 0;

static inline void glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    if (gles_immediate) {
        if (gles_color_count / 4 <= gles_vertex_count / gles_vertex_dimensions) {
            gles_colors[gles_color_count++] = red;
            gles_colors[gles_color_count++] = green;
            gles_colors[gles_color_count++] = blue;
            gles_colors[gles_color_count++] = alpha;
        } else {
            gles_colors[gles_color_count - 4] = red;
            gles_colors[gles_color_count - 3] = green;
            gles_colors[gles_color_count - 2] = blue;
            gles_colors[gles_color_count - 1] = alpha;
        }
    } else {
        gles_colors[0] = red;
        gles_colors[1] = green;
        gles_colors[2] = blue;
        gles_colors[3] = alpha;
        glColor4f(red, green, blue, alpha);
    }
}

static inline void glColor3f(GLfloat red, GLfloat green, GLfloat blue) {
    glesColor4f(red, green, blue, 1.0f);
}

static inline void glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) {
    glesColor4f((GLfloat)red / 255.0f, (GLfloat)green / 255.0f, (GLfloat)blue / 255.0f, (GLfloat)alpha / 255.0f);
}

static inline void glColor3ub(GLubyte red, GLubyte green, GLubyte blue) {
    glesColor4ub(red, green, blue, 255);
}
