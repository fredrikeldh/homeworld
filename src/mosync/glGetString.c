#include <GLES/gl.h>
#include <maheap.h>

typedef struct glString_t {
	GLenum name;
	char *stringData;
} glString;

static glString sGLStrings[32];
static int sNumGLStrings = 0;

const char* glGetString(GLenum name) {
	int i, strLen;
	MAHandle data;
	char* str;

	for(i = 0; i < sNumGLStrings; i++) {
		if(sGLStrings[i].name == name) {
			return sGLStrings[i].stringData;
		}
	}

	data = glGetStringHandle(name);

	if(data == IOCTL_UNAVAILABLE) {
		return "";
	}

	strLen = maGetDataSize(data);
	sGLStrings[sNumGLStrings].name = name;
	sGLStrings[sNumGLStrings].stringData = str = (char*)malloc(strLen+1);
	maReadData(data, str, 0, strLen);
	str[strLen] = 0;
	maDestroyObject(data);
	sNumGLStrings++;
	return str;
}
