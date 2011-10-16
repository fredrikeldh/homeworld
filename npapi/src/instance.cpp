#include "instance.h"

#define PPVAR_IS_NULL(var) (var.type == PP_VARTYPE_NULL)

using namespace npapi;

HomeInstance::HomeInstance(PP_Instance instance) :
	pp::Instance(instance)
{
}
	
HomeInstance::~HomeInstance()
{
}

bool HomeInstance::Init(uint32_t argc, const char* argn[], const char* argv[])
{
	return pp::Instance::Init(argc, argn, argv);
}
	
bool HomeInstance::HandleInputEvent(const pp::InputEvent& event)
{
	return pp::Instance::HandleInputEvent(event);
}

bool HomeInstance::HandleDocumentLoad(const pp::URLLoader& url_loader)
{
	return pp::Instance::HandleDocumentLoad(url_loader);
}

void HomeInstance::HandleMessage(const pp::Var& message)
{
	return pp::Instance::HandleMessage(message);
}

NPP HomeInstance::GetNP() const
{
	return _np_instance;
}

