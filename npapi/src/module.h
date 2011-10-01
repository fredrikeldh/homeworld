#ifndef _HOME_NPAPI_MODULE_H_
#define _HOME_NPAPI_MODULE_H_

#include "ppapi/cpp/module.h"

namespace npapi
{
class Instance;
class HomeModule : public pp::Module
{
public:

	HomeModule();
	virtual bool Init();

protected:
	// Override to create your own plugin type.
	virtual pp::Instance* CreateInstance(PP_Instance instance);
};

}  // namespace pp

#endif  //_HOME_NPAPI_MODULE_H_

