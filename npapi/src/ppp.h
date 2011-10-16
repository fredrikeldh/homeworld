#ifndef _HOME_NPAPI_PPP_H_
#define _HOME_NPAPI_PPP_H_

#include <npapi.h>

namespace pp
{
	class Instance;
}

NPP GetNPInstance();
pp::Instance* GetPPInstance();

#endif //_HOME_NPAPI_PPP_H_

