
#ifdef HW_ENABLE_GLES2
#include "gles2.h"

template<typename... TYPES>
class Setup
{
private:

	struct FalseType { enum { value = false }; };
	struct TrueType  { enum { value =  true }; };

	template<typename T1, typename T2>
	struct IsSame
	{
		typedef FalseType Result;
	};

	template <typename T>
	struct IsSame<T,T>
	{
		typedef TrueType Result;
	};

	template<GLubyte INDEX, typename TEST, typename T1>
	GLubyte GetIndex()
	{
		if( IsSame<TEST, T1>::Result::value )
			return INDEX;
		
		throw "Type not registered";
	}

	template<GLubyte INDEX, typename TEST, typename T1, typename T2, typename... TOTHER>
	GLubyte GetIndex()
	{
		if( IsSame<TEST, T1>::Result::value )
			return INDEX;
		
		return GetIndex<INDEX + 1, TEST, T2, TOTHER...>();
	};
public:
	template<typename T>
	T& Get()
	{
		GLubyte byte = GetIndex<0, T, TYPES...>();
		return *(new T());
	};
};

Setup<
	AlphaSetup,
	ClipSetup,
	ColorSetup,
	FogSetup,
	LightSetup,
	LineSetup,
	MaterialSetup,
	NormalSetup,
	PointSetup,
	StateSetup,
	TextureSetup,
	VertexSetup
> setup(); 

template<typename T>
T& Get()
{
	return setup.Get<T>();
}
/*
#include <GLES/emul/color.c>
#include <GLES/emul/error.c>
#include <GLES2/emul/light.c>
#include <GLES2/emul/line.c>
#include <GLES2/emul/matrices.c>
#include <GLES/emul/normal.c>
#include <GLES2/emul/point.c>
#include <GLES/emul/state.c>
#include <GLES2/emul/state.c>
#include <GLES/emul/texture.c>
#include <GLES2/emul/texture.c>
#include <GLES/emul/vertex.c>
#include <GLES2/emul/vertex.c>
*/

#endif //HW_ENABLE_GLES2
