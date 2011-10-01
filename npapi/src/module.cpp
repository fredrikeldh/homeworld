#include "module.h"

using namespace pp;

HomeModule::HomeModule() :
	Module()
{
}

bool HomeModule::Init()
{
	return true;
}

Instance* HomeModule::CreateInstance(PP_Instance instance)
{
	return new HomeInstance(instance);
}

