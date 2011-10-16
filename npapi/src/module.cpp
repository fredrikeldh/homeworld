#include "module.h"
#include "instance.h"

using namespace npapi;

HomeModule::HomeModule() :
	Module()
{
}

bool HomeModule::Init()
{
	return true;
}

pp::Instance* HomeModule::CreateInstance(PP_Instance instance)
{
	return new HomeInstance(instance);
}

