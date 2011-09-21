#ifndef _HW_GLES_INCLUDE_H_
#define _HW_GLES_INCLUDE_H_

#ifndef N_ELEMENTS
	#define N_ELEMENTS(X) (sizeof(X)/sizeof(*(X)))
#endif //N_ELEMENTS

#if defined __cplusplus

#ifdef HW_USE_GLES1
namespace gles1
{
	class IRenderState;
}
// use define since typedef does not work as a friend even with gcc 4.6!
#define RENDER_PROCESSOR gles1::IRenderState
#elif defined HW_USE_GLES2
namespace gles2
{
	class IRenderState;
}
// use define since typedef does not work as a friend even with gcc 4.6!
#define RENDER_PROCESSOR gles2::IRenderState
#endif

#ifndef nullptr
const                        // this is a const object...
class {
public:
  template<class T>          // convertible to any type
    operator T*() const      // of null non-member
    { return 0; }            // pointer...
  template<class C, class T> // or any type of null
    operator T C::*() const  // member pointer...
    { return 0; }
private:
  void operator&() const;    // whose address can't be taken
} nullptr = {};
#endif //nullptr

#if __GNUC__ <= 4 && __GNUC_MINOR__ < 6
	#define HAS_MOVE_ASSIGN_BUG 1
	#define ENABLE_MOVE(CLAZZ) \
		CLAZZ(CLAZZ&&) = default;
#else
	#define HAS_MOVE_ASSIGN_BUG 0
	#define ENABLE_MOVE(CLAZZ) \
		CLAZZ(CLAZZ&&) = default; \
		CLAZZ& operator=(CLAZZ&&) = default;
#endif //__GNUC__ <= 4 && __GNUC_MINOR__ < 6
	
#define ENABLE_COPY(CLAZZ) \
	CLAZZ(CLAZZ const &) = default; \
	CLAZZ& operator=(CLAZZ const &) = default;
	
#define DISABLE_COPY(CLAZZ) \
	CLAZZ(CLAZZ const &) = delete; \
	CLAZZ& operator=(CLAZZ const &) = delete;
	

#define ENABLE_MOVE_AND_COPY(CLAZZ) \
	ENABLE_MOVE(CLAZZ) \
	ENABLE_COPY(CLAZZ)

#define ONLY_MOVE(CLAZZ) \
	ENABLE_MOVE(CLAZZ) \
	DISABLE_COPY(CLAZZ)

template<typename T>
static T clamp(T Value, T Min, T Max)
{
	return (Value < Min)? Min : (Value > Max)? Max : Value;
}

template<typename T>
static T& Get();

#include "glinclude.h"
#include "GLPart.h"

#endif //__cplusplus
#endif //_HW_GLES_INCLUDE_H_

