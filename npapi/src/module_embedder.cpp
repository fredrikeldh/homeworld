using namespace pp;

#include "module.h"
#include "ppapi/cpp/module_embedder.h"

pp::Module* CreateModule()
{
	return new HomeModule();
}

