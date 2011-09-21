
#ifdef HW_USE_GLES

#ifdef HW_USE_GLES1
	#include "../GLES1/glinclude.h"
#elif defined HW_USE_GLES2
	#include "../GLES2/glinclude.h"
#endif

#include "../GLES1/emul/defines.h"
#include "../GLES1/emul/declarations.h"

#ifdef HW_USE_GLES2
	#include "../GLES2/emul/defines.h"
	#include "../GLES2/emul/declarations.h"
#endif //HW_USE_GLES2

#endif //HW_USE_GLES

