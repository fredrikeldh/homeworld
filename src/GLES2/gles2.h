#ifndef _HW_GLES2_H_
#define _HW_GLES2_H_

#include "emul/include.h"

#include "emul/alpha.h"
#include "emul/clip.h"
#include "emul/color.h"
#include "emul/fog.h"
#include "emul/light.h"
#include "emul/line.h"
#include "emul/material.h"
#include "emul/normal.h"
#include "emul/point.h"
#include "emul/render.h"
#include "emul/state.h"
#include "emul/texture.h"
#include "emul/vertex.h"

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

		maPanic(0, "Type not registered");
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

typedef Setup<
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
> GLES2Setup ;

extern GLES2Setup setup;

template<typename T>
T& Get()
{
	return setup.Get<T>();
}

#endif //_HW_GLES2_H_

