#ifndef _HOME_PPAPI_INSTANCE_H_
#define _HOME_PPAPI_INSTANCE_H_

#include <ppapi/cpp/instance.h>
#include <npapi.h>

namespace npapi {

class HomeInstance : public pp::Instance
{
public:
	HomeInstance(PP_Instance instance);
	virtual ~HomeInstance();

	virtual bool Init(uint32_t argc, const char* argn[], const char* argv[]);
	
	virtual bool HandleInputEvent(const pp::InputEvent& event);
	virtual bool HandleDocumentLoad(const pp::URLLoader& url_loader);
	virtual void HandleMessage(const pp::Var& message);
	NPP GetNP() const;
private:
	NPP _np_instance;
};

}  // namespace npapi

#endif  // _HOME_PPAPI_INSTANCE_H_
