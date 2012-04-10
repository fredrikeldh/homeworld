// =============================================================================
//  Types.c
// =============================================================================

#include "Types.h"

typedef union Swap
{
	float  f;
	Uint32 i;
} Swap;

float SwapFloat32( float val )
{
	Swap swap;
	swap.f = val;
	swap.i = SDL_Swap32( swap.i );

	return swap.f;
}

udword Real32ToUdword(real32 a)
{
	Swap swap;
	swap.f = a;
	return swap.i;
}

sdword Real32ToSdword(real32 a)
{
	Swap swap;
	swap.f = a;
	return swap.i;
}

real32 UdwordToReal32(udword a)
{
	Swap swap;
	swap.i = a;
	return swap.f;
}

real32 SdwordToReal32(sdword a)
{
	Swap swap;
	swap.i = a;
	return swap.f;
}
