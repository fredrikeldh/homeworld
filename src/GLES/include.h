#ifndef _HW_GLES_INCLUDE_H_
#define _HW_GLES_INCLUDE_H_

#if defined HW_ENABLE_GLES2
#include "../GLES2/glinclude.h"

#if defined __cplusplus
namespace gles2
{
	class RenderPipe;
};

// use define since typedef does not work as a friend even with gcc 4.6!
#define RENDER_PROCESSOR gles2::RenderPipe
#endif //__cplusplus

#else
#include "../GLES1/glinclude.h"
#endif //HW_ENABLE_GLES2

#ifndef N_ELEMENTS
#define N_ELEMENTS(X) (sizeof(X)/sizeof(*(X)))
#endif //N_ELEMENTS

#if defined __cplusplus

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

template<typename T>
static T clamp(T Value, T Min, T Max)
{
	return (Value < Min)? Min : (Value > Max)? Max : Value;
}

template<typename T>
static T& Get();
#endif //__cplusplus
#endif //_HW_GLES_INCLUDE_H_

