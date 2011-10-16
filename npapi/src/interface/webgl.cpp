#include "gl2.h"

NPError NPN_GetValue(NPP         instance,
                     NPNVariable variable,
                     void*       value);

NPP INSTANCE;
NPObject* CANVAS;


namespace npapi
{
	class ObjectPtr
	{
	private:
		NPObject* _ptr;
	protected:
		ObjectPtr(NPObject* ptr) :
			_ptr(ptr)
		{
		}
	public:
		~ObjectPtr()
		{
			NPN_ReleaseObject(ptr);
		}
	};
	
GL_CONTEXT;

	class WindowPtr : public ObjectPtr
	{
	private:
		Window(NPObject* ptr) :
			ObjectPtr(ptr)
		{
		}
	public:
		
		static Window* getCurrent()
		{
			NPObject* window = nullptr;
			NPN_GetValue(INSTANCE, NPNVWindowNPObject, &window);
			
			if( window )
				return new Window(window);
				
			return nullptr;
		};
	};
}

void glActiveTexture(GLenum texture)
{
	// Get window object
	NPObject* window = NULL;
	NPN_GetValue(aInstance, NPNVWindowNPObject, &window);
	
	Window.getCurrent()

	// Get document object
	NPVariant controllerVar;
	NPIdentifier id = NPN_GetStringIdentifier("activeTexture");
	NPN_GetProperty(aInstance, window, id, &controllerVar);
	//NPObject* document = NPVARIANT_TO_OBJECT(controllerVar);
	
	NPVariant arguments;
	arguments.type = NPVariantType_Void;
	
	

	NPVariant result;
	
	NPObject* document = NPN_InvokeDefault
	(
		INSTANCE,
		CANVAS,
		&arguments,
		uint32_t argCount,
		&result
	);
	
	activeTexture
}

GL_APICALL void         GL_APIENTRY glAttachShader (GLuint program, GLuint shader);
GL_APICALL void         GL_APIENTRY glBindAttribLocation (GLuint program, GLuint index, const GLchar* name);
GL_APICALL void         GL_APIENTRY glBindBuffer (GLenum target, GLuint buffer);
GL_APICALL void         GL_APIENTRY glBindFramebuffer (GLenum target, GLuint framebuffer);
GL_APICALL void         GL_APIENTRY glBindRenderbuffer (GLenum target, GLuint renderbuffer);
GL_APICALL void         GL_APIENTRY glBindTexture (GLenum target, GLuint texture);
GL_APICALL void         GL_APIENTRY glBlendColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
GL_APICALL void         GL_APIENTRY glBlendEquation ( GLenum mode );
GL_APICALL void         GL_APIENTRY glBlendEquationSeparate (GLenum modeRGB, GLenum modeAlpha);
GL_APICALL void         GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor);
GL_APICALL void         GL_APIENTRY glBlendFuncSeparate (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
GL_APICALL void         GL_APIENTRY glBufferData (GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
GL_APICALL void         GL_APIENTRY glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data);
GL_APICALL GLenum       GL_APIENTRY glCheckFramebufferStatus (GLenum target);
GL_APICALL void         GL_APIENTRY glClear (GLbitfield mask);
GL_APICALL void         GL_APIENTRY glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
GL_APICALL void         GL_APIENTRY glClearDepthf (GLclampf depth);
GL_APICALL void         GL_APIENTRY glClearStencil (GLint s);
GL_APICALL void         GL_APIENTRY glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
GL_APICALL void         GL_APIENTRY glCompileShader (GLuint shader);
GL_APICALL void         GL_APIENTRY glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data);
GL_APICALL void         GL_APIENTRY glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data);
GL_APICALL void         GL_APIENTRY glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
GL_APICALL void         GL_APIENTRY glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
GL_APICALL GLuint       GL_APIENTRY glCreateProgram (void);
GL_APICALL GLuint       GL_APIENTRY glCreateShader (GLenum type);
GL_APICALL void         GL_APIENTRY glCullFace (GLenum mode);
GL_APICALL void         GL_APIENTRY glDeleteBuffers (GLsizei n, const GLuint* buffers);
GL_APICALL void         GL_APIENTRY glDeleteFramebuffers (GLsizei n, const GLuint* framebuffers);
GL_APICALL void         GL_APIENTRY glDeleteProgram (GLuint program);
GL_APICALL void         GL_APIENTRY glDeleteRenderbuffers (GLsizei n, const GLuint* renderbuffers);
GL_APICALL void         GL_APIENTRY glDeleteShader (GLuint shader);
GL_APICALL void         GL_APIENTRY glDeleteTextures (GLsizei n, const GLuint* textures);
GL_APICALL void         GL_APIENTRY glDepthFunc (GLenum func);
GL_APICALL void         GL_APIENTRY glDepthMask (GLboolean flag);
GL_APICALL void         GL_APIENTRY glDepthRangef (GLclampf zNear, GLclampf zFar);
GL_APICALL void         GL_APIENTRY glDetachShader (GLuint program, GLuint shader);
GL_APICALL void         GL_APIENTRY glDisable (GLenum cap);
GL_APICALL void         GL_APIENTRY glDisableVertexAttribArray (GLuint index);
GL_APICALL void         GL_APIENTRY glDrawArrays (GLenum mode, GLint first, GLsizei count);
GL_APICALL void         GL_APIENTRY glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
GL_APICALL void         GL_APIENTRY glEnable (GLenum cap);
GL_APICALL void         GL_APIENTRY glEnableVertexAttribArray (GLuint index);
GL_APICALL void         GL_APIENTRY glFinish (void);
GL_APICALL void         GL_APIENTRY glFlush (void);
GL_APICALL void         GL_APIENTRY glFramebufferRenderbuffer (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_APICALL void         GL_APIENTRY glFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_APICALL void         GL_APIENTRY glFrontFace (GLenum mode);
GL_APICALL void         GL_APIENTRY glGenBuffers (GLsizei n, GLuint* buffers);
GL_APICALL void         GL_APIENTRY glGenerateMipmap (GLenum target);
GL_APICALL void         GL_APIENTRY glGenFramebuffers (GLsizei n, GLuint* framebuffers);
GL_APICALL void         GL_APIENTRY glGenRenderbuffers (GLsizei n, GLuint* renderbuffers);
GL_APICALL void         GL_APIENTRY glGenTextures (GLsizei n, GLuint* textures);
GL_APICALL void         GL_APIENTRY glGetActiveAttrib (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
GL_APICALL void         GL_APIENTRY glGetActiveUniform (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
GL_APICALL void         GL_APIENTRY glGetAttachedShaders (GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders);
GL_APICALL int          GL_APIENTRY glGetAttribLocation (GLuint program, const GLchar* name);
GL_APICALL void         GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean* params);
GL_APICALL void         GL_APIENTRY glGetBufferParameteriv (GLenum target, GLenum pname, GLint* params);
GL_APICALL GLenum       GL_APIENTRY glGetError (void);
GL_APICALL void         GL_APIENTRY glGetFloatv (GLenum pname, GLfloat* params);
GL_APICALL void         GL_APIENTRY glGetFramebufferAttachmentParameteriv (GLenum target, GLenum attachment, GLenum pname, GLint* params);
GL_APICALL void         GL_APIENTRY glGetIntegerv (GLenum pname, GLint* params);
GL_APICALL void         GL_APIENTRY glGetProgramiv (GLuint program, GLenum pname, GLint* params);
GL_APICALL void         GL_APIENTRY glGetProgramInfoLog (GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog);
GL_APICALL void         GL_APIENTRY glGetRenderbufferParameteriv (GLenum target, GLenum pname, GLint* params);
GL_APICALL void         GL_APIENTRY glGetShaderiv (GLuint shader, GLenum pname, GLint* params);
GL_APICALL void         GL_APIENTRY glGetShaderInfoLog (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog);
GL_APICALL void         GL_APIENTRY glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision);
GL_APICALL void         GL_APIENTRY glGetShaderSource (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source);
GL_APICALL const GLubyte* GL_APIENTRY glGetString (GLenum name);
GL_APICALL void         GL_APIENTRY glGetTexParameterfv (GLenum target, GLenum pname, GLfloat* params);
GL_APICALL void         GL_APIENTRY glGetTexParameteriv (GLenum target, GLenum pname, GLint* params);
GL_APICALL void         GL_APIENTRY glGetUniformfv (GLuint program, GLint location, GLfloat* params);
GL_APICALL void         GL_APIENTRY glGetUniformiv (GLuint program, GLint location, GLint* params);
GL_APICALL int          GL_APIENTRY glGetUniformLocation (GLuint program, const GLchar* name);
GL_APICALL void         GL_APIENTRY glGetVertexAttribfv (GLuint index, GLenum pname, GLfloat* params);
GL_APICALL void         GL_APIENTRY glGetVertexAttribiv (GLuint index, GLenum pname, GLint* params);
GL_APICALL void         GL_APIENTRY glGetVertexAttribPointerv (GLuint index, GLenum pname, GLvoid** pointer);
GL_APICALL void         GL_APIENTRY glHint (GLenum target, GLenum mode);
GL_APICALL GLboolean    GL_APIENTRY glIsBuffer (GLuint buffer);
GL_APICALL GLboolean    GL_APIENTRY glIsEnabled (GLenum cap);
GL_APICALL GLboolean    GL_APIENTRY glIsFramebuffer (GLuint framebuffer);
GL_APICALL GLboolean    GL_APIENTRY glIsProgram (GLuint program);
GL_APICALL GLboolean    GL_APIENTRY glIsRenderbuffer (GLuint renderbuffer);
GL_APICALL GLboolean    GL_APIENTRY glIsShader (GLuint shader);
GL_APICALL GLboolean    GL_APIENTRY glIsTexture (GLuint texture);
GL_APICALL void         GL_APIENTRY glLineWidth (GLfloat width);
GL_APICALL void         GL_APIENTRY glLinkProgram (GLuint program);
GL_APICALL void         GL_APIENTRY glPixelStorei (GLenum pname, GLint param);
GL_APICALL void         GL_APIENTRY glPolygonOffset (GLfloat factor, GLfloat units);
GL_APICALL void         GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels);
GL_APICALL void         GL_APIENTRY glReleaseShaderCompiler (void);
GL_APICALL void         GL_APIENTRY glRenderbufferStorage (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
GL_APICALL void         GL_APIENTRY glSampleCoverage (GLclampf value, GLboolean invert);
GL_APICALL void         GL_APIENTRY glScissor (GLint x, GLint y, GLsizei width, GLsizei height);
GL_APICALL void         GL_APIENTRY glShaderBinary (GLsizei n, const GLuint* shaders, GLenum binaryformat, const GLvoid* binary, GLsizei length);
GL_APICALL void         GL_APIENTRY glShaderSource (GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
GL_APICALL void         GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint mask);
GL_APICALL void         GL_APIENTRY glStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint mask);
GL_APICALL void         GL_APIENTRY glStencilMask (GLuint mask);
GL_APICALL void         GL_APIENTRY glStencilMaskSeparate (GLenum face, GLuint mask);
GL_APICALL void         GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
GL_APICALL void         GL_APIENTRY glStencilOpSeparate (GLenum face, GLenum fail, GLenum zfail, GLenum zpass);
GL_APICALL void         GL_APIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
GL_APICALL void         GL_APIENTRY glTexParameterf (GLenum target, GLenum pname, GLfloat param);
GL_APICALL void         GL_APIENTRY glTexParameterfv (GLenum target, GLenum pname, const GLfloat* params);
GL_APICALL void         GL_APIENTRY glTexParameteri (GLenum target, GLenum pname, GLint param);
GL_APICALL void         GL_APIENTRY glTexParameteriv (GLenum target, GLenum pname, const GLint* params);
GL_APICALL void         GL_APIENTRY glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels);
GL_APICALL void         GL_APIENTRY glUniform1f (GLint location, GLfloat x);
GL_APICALL void         GL_APIENTRY glUniform1fv (GLint location, GLsizei count, const GLfloat* v);
GL_APICALL void         GL_APIENTRY glUniform1i (GLint location, GLint x);
GL_APICALL void         GL_APIENTRY glUniform1iv (GLint location, GLsizei count, const GLint* v);
GL_APICALL void         GL_APIENTRY glUniform2f (GLint location, GLfloat x, GLfloat y);
GL_APICALL void         GL_APIENTRY glUniform2fv (GLint location, GLsizei count, const GLfloat* v);
GL_APICALL void         GL_APIENTRY glUniform2i (GLint location, GLint x, GLint y);
GL_APICALL void         GL_APIENTRY glUniform2iv (GLint location, GLsizei count, const GLint* v);
GL_APICALL void         GL_APIENTRY glUniform3f (GLint location, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL void         GL_APIENTRY glUniform3fv (GLint location, GLsizei count, const GLfloat* v);
GL_APICALL void         GL_APIENTRY glUniform3i (GLint location, GLint x, GLint y, GLint z);
GL_APICALL void         GL_APIENTRY glUniform3iv (GLint location, GLsizei count, const GLint* v);
GL_APICALL void         GL_APIENTRY glUniform4f (GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GL_APICALL void         GL_APIENTRY glUniform4fv (GLint location, GLsizei count, const GLfloat* v);
GL_APICALL void         GL_APIENTRY glUniform4i (GLint location, GLint x, GLint y, GLint z, GLint w);
GL_APICALL void         GL_APIENTRY glUniform4iv (GLint location, GLsizei count, const GLint* v);
GL_APICALL void         GL_APIENTRY glUniformMatrix2fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
GL_APICALL void         GL_APIENTRY glUniformMatrix3fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
GL_APICALL void         GL_APIENTRY glUniformMatrix4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
GL_APICALL void         GL_APIENTRY glUseProgram (GLuint program);
GL_APICALL void         GL_APIENTRY glValidateProgram (GLuint program);
GL_APICALL void         GL_APIENTRY glVertexAttrib1f (GLuint indx, GLfloat x);
GL_APICALL void         GL_APIENTRY glVertexAttrib1fv (GLuint indx, const GLfloat* values);
GL_APICALL void         GL_APIENTRY glVertexAttrib2f (GLuint indx, GLfloat x, GLfloat y);
GL_APICALL void         GL_APIENTRY glVertexAttrib2fv (GLuint indx, const GLfloat* values);
GL_APICALL void         GL_APIENTRY glVertexAttrib3f (GLuint indx, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL void         GL_APIENTRY glVertexAttrib3fv (GLuint indx, const GLfloat* values);
GL_APICALL void         GL_APIENTRY glVertexAttrib4f (GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GL_APICALL void         GL_APIENTRY glVertexAttrib4fv (GLuint indx, const GLfloat* values);
GL_APICALL void         GL_APIENTRY glVertexAttribPointer (GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr);
GL_APICALL void         GL_APIENTRY glViewport (GLint x, GLint y, GLsizei width, GLsizei height);


WebGLContextAttributes getContextAttributes();
    boolean isContextLost();
    
    DOMString[ ] getSupportedExtensions();
    object getExtension(DOMString name);


    void attachShader(WebGLProgram program, WebGLShader shader);
    void bindAttribLocation(WebGLProgram program, GLuint index, DOMString name);
    void bindBuffer(GLenum target, WebGLBuffer buffer);
    void bindFramebuffer(GLenum target, WebGLFramebuffer framebuffer);
    void bindRenderbuffer(GLenum target, WebGLRenderbuffer renderbuffer);
    void bindTexture(GLenum target, WebGLTexture texture);
    void blendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
    void blendEquation(GLenum mode);
    void blendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);
    void blendFunc(GLenum sfactor, GLenum dfactor);
    void blendFuncSeparate(GLenum srcRGB, GLenum dstRGB, 
                           GLenum srcAlpha, GLenum dstAlpha);

    void bufferData(GLenum target, GLsizeiptr size, GLenum usage);
    void bufferData(GLenum target, ArrayBufferView data, GLenum usage);
    void bufferData(GLenum target, ArrayBuffer data, GLenum usage);
    void bufferSubData(GLenum target, GLintptr offset, ArrayBufferView data);
    void bufferSubData(GLenum target, GLintptr offset, ArrayBuffer data);

    GLenum checkFramebufferStatus(GLenum target);
    void clear(GLbitfield mask);
    void clearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
    void clearDepth(GLclampf depth);
    void clearStencil(GLint s);
    void colorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
    void compileShader(WebGLShader shader);

    void copyTexImage2D(GLenum target, GLint level, GLenum internalformat, 
                        GLint x, GLint y, GLsizei width, GLsizei height, 
                        GLint border);
    void copyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, 
                           GLint x, GLint y, GLsizei width, GLsizei height);

    WebGLBuffer createBuffer();
    WebGLFramebuffer createFramebuffer();
    WebGLProgram createProgram();
    WebGLRenderbuffer createRenderbuffer();
    WebGLShader createShader(GLenum type);
    WebGLTexture createTexture();

    void cullFace(GLenum mode);

    void deleteBuffer(WebGLBuffer buffer);
    void deleteFramebuffer(WebGLFramebuffer framebuffer);
    void deleteProgram(WebGLProgram program);
    void deleteRenderbuffer(WebGLRenderbuffer renderbuffer);
    void deleteShader(WebGLShader shader);
    void deleteTexture(WebGLTexture texture);

    void depthFunc(GLenum func);
    void depthMask(GLboolean flag);
    void depthRange(GLclampf zNear, GLclampf zFar);
    void detachShader(WebGLProgram program, WebGLShader shader);
    void disable(GLenum cap);
    void disableVertexAttribArray(GLuint index);
    void drawArrays(GLenum mode, GLint first, GLsizei count);
    void drawElements(GLenum mode, GLsizei count, GLenum type, GLintptr offset);

    void enable(GLenum cap);
    void enableVertexAttribArray(GLuint index);
    void finish();
    void flush();
    void framebufferRenderbuffer(GLenum target, GLenum attachment, 
                                 GLenum renderbuffertarget, 
                                 WebGLRenderbuffer renderbuffer);
    void framebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, 
                              WebGLTexture texture, GLint level);
    void frontFace(GLenum mode);

    void generateMipmap(GLenum target);

    WebGLActiveInfo getActiveAttrib(WebGLProgram program, GLuint index);
    WebGLActiveInfo getActiveUniform(WebGLProgram program, GLuint index);
    WebGLShader[ ] getAttachedShaders(WebGLProgram program);

    GLint getAttribLocation(WebGLProgram program, DOMString name);

    any getParameter(GLenum pname);
    any getBufferParameter(GLenum target, GLenum pname);

    GLenum getError();

    any getFramebufferAttachmentParameter(GLenum target, GLenum attachment, 
                                          GLenum pname);
    any getProgramParameter(WebGLProgram program, GLenum pname);
    DOMString getProgramInfoLog(WebGLProgram program);
    any getRenderbufferParameter(GLenum target, GLenum pname);
    any getShaderParameter(WebGLShader shader, GLenum pname);
    DOMString getShaderInfoLog(WebGLShader shader);

    DOMString getShaderSource(WebGLShader shader);

    any getTexParameter(GLenum target, GLenum pname);

    any getUniform(WebGLProgram program, WebGLUniformLocation location);

    WebGLUniformLocation getUniformLocation(WebGLProgram program, DOMString name);

    any getVertexAttrib(GLuint index, GLenum pname);

    GLsizeiptr getVertexAttribOffset(GLuint index, GLenum pname);

    void hint(GLenum target, GLenum mode);
    GLboolean isBuffer(WebGLBuffer buffer);
    GLboolean isEnabled(GLenum cap);
    GLboolean isFramebuffer(WebGLFramebuffer framebuffer);
    GLboolean isProgram(WebGLProgram program);
    GLboolean isRenderbuffer(WebGLRenderbuffer renderbuffer);
    GLboolean isShader(WebGLShader shader);
    GLboolean isTexture(WebGLTexture texture);
    void lineWidth(GLfloat width);
    void linkProgram(WebGLProgram program);
    void pixelStorei(GLenum pname, GLint param);
    void polygonOffset(GLfloat factor, GLfloat units);

    void readPixels(GLint x, GLint y, GLsizei width, GLsizei height, 
                    GLenum format, GLenum type, ArrayBufferView pixels);

    void renderbufferStorage(GLenum target, GLenum internalformat, 
                             GLsizei width, GLsizei height);
    void sampleCoverage(GLclampf value, GLboolean invert);
    void scissor(GLint x, GLint y, GLsizei width, GLsizei height);

    void shaderSource(WebGLShader shader, DOMString source);

    void stencilFunc(GLenum func, GLint ref, GLuint mask);
    void stencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask);
    void stencilMask(GLuint mask);
    void stencilMaskSeparate(GLenum face, GLuint mask);
    void stencilOp(GLenum fail, GLenum zfail, GLenum zpass);
    void stencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass);

    void texImage2D(GLenum target, GLint level, GLenum internalformat, 
                    GLsizei width, GLsizei height, GLint border, GLenum format, 
                    GLenum type, ArrayBufferView pixels);
    void texImage2D(GLenum target, GLint level, GLenum internalformat,
                    GLenum format, GLenum type, ImageData pixels);
    void texImage2D(GLenum target, GLint level, GLenum internalformat,
                    GLenum format, GLenum type, HTMLImageElement image);
    void texImage2D(GLenum target, GLint level, GLenum internalformat,
                    GLenum format, GLenum type, HTMLCanvasElement canvas);
    void texImage2D(GLenum target, GLint level, GLenum internalformat,
                    GLenum format, GLenum type, HTMLVideoElement video);

    void texParameterf(GLenum target, GLenum pname, GLfloat param);
    void texParameteri(GLenum target, GLenum pname, GLint param);

    void texSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, 
                       GLsizei width, GLsizei height, 
                       GLenum format, GLenum type, ArrayBufferView pixels);
    void texSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, 
                       GLenum format, GLenum type, ImageData pixels);
    void texSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, 
                       GLenum format, GLenum type, HTMLImageElement image);
    void texSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, 
                       GLenum format, GLenum type, HTMLCanvasElement canvas);
    void texSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, 
                       GLenum format, GLenum type, HTMLVideoElement video);

    void uniform1f(WebGLUniformLocation location, GLfloat x);
    void uniform1fv(WebGLUniformLocation location, Float32Array v);
    void uniform1fv(WebGLUniformLocation location, float[] v);
    void uniform1i(WebGLUniformLocation location, GLint x);
    void uniform1iv(WebGLUniformLocation location, Int32Array v);
    void uniform1iv(WebGLUniformLocation location, long[] v);
    void uniform2f(WebGLUniformLocation location, GLfloat x, GLfloat y);
    void uniform2fv(WebGLUniformLocation location, Float32Array v);
    void uniform2fv(WebGLUniformLocation location, float[] v);
    void uniform2i(WebGLUniformLocation location, GLint x, GLint y);
    void uniform2iv(WebGLUniformLocation location, Int32Array v);
    void uniform2iv(WebGLUniformLocation location, long[] v);
    void uniform3f(WebGLUniformLocation location, GLfloat x, GLfloat y, GLfloat z);
    void uniform3fv(WebGLUniformLocation location, Float32Array v);
    void uniform3fv(WebGLUniformLocation location, float[] v);
    void uniform3i(WebGLUniformLocation location, GLint x, GLint y, GLint z);
    void uniform3iv(WebGLUniformLocation location, Int32Array v);
    void uniform3iv(WebGLUniformLocation location, long[] v);
    void uniform4f(WebGLUniformLocation location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void uniform4fv(WebGLUniformLocation location, Float32Array v);
    void uniform4fv(WebGLUniformLocation location, float[] v);
    void uniform4i(WebGLUniformLocation location, GLint x, GLint y, GLint z, GLint w);
    void uniform4iv(WebGLUniformLocation location, Int32Array v);
    void uniform4iv(WebGLUniformLocation location, long[] v);

    void uniformMatrix2fv(WebGLUniformLocation location, GLboolean transpose, 
                          Float32Array value);
    void uniformMatrix2fv(WebGLUniformLocation location, GLboolean transpose, 
                          float[] value);
    void uniformMatrix3fv(WebGLUniformLocation location, GLboolean transpose, 
                          Float32Array value);
    void uniformMatrix3fv(WebGLUniformLocation location, GLboolean transpose, 
                          float[] value);
    void uniformMatrix4fv(WebGLUniformLocation location, GLboolean transpose, 
                          Float32Array value);
    void uniformMatrix4fv(WebGLUniformLocation location, GLboolean transpose, 
                          float[] value);

    void useProgram(WebGLProgram program);
    void validateProgram(WebGLProgram program);

    void vertexAttrib1f(GLuint indx, GLfloat x);
    void vertexAttrib1fv(GLuint indx, Float32Array values);
    void vertexAttrib1fv(GLuint indx, float[] values);
    void vertexAttrib2f(GLuint indx, GLfloat x, GLfloat y);
    void vertexAttrib2fv(GLuint indx, Float32Array values);
    void vertexAttrib2fv(GLuint indx, float[] values);
    void vertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z);
    void vertexAttrib3fv(GLuint indx, Float32Array values);
    void vertexAttrib3fv(GLuint indx, float[] values);
    void vertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void vertexAttrib4fv(GLuint indx, Float32Array values);
    void vertexAttrib4fv(GLuint indx, float[] values);
    void vertexAttribPointer(GLuint indx, GLint size, GLenum type, 
                             GLboolean normalized, GLsizei stride, GLintptr offset);

    void viewport(GLint x, GLint y, GLsizei width, GLsizei height);
