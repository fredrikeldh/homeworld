/* Copyright (c) 2011 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/* From ppp.idl modified Mon Aug  8 06:47:44 2011. */

#include <ppapi/c/ppp.h>
#include <ppapi/c/pp_errors.h>
#include <npapi.h>
#include <ppapi/npapi/module_ppb_var_deprecated.h>
#include <ppapi/npapi/module_ppb_opengles2.h>
#include "ppp.h"
#include <ppapi/cpp/instance.h>

typedef pp::Instance Instance;

class ThreadInstance;

thread_local std::vector<std::pair<Instance, NPP>> NP_INSTANCES;

class ThreadInstance
{
private:
	std::pair<Instance, NPP> _instance;
public:
	ThreadInstance(Instance& pp_instance, NPP np_instance):
		_instance({pp_instance, np_instance})
	{
		NP_INSTANCES.push_back(_instance);
	}
	
	~ThreadInstance()
	{
		NPP instance = NP_INSTANCES.pop().second;
		
		if( instance.pdata != _instance.first.pdata )
			throw "ThreadInstance corruption!";
	}
	
	void* operator new   (size_t) = delete;
	void* operator new[] (size_t) = delete;
	void  operator delete   (void *) = delete;
	void  operator delete[] (void*)  = delete;
};


NPP GetNPInstance()
{
	return NP_INSTANCES.end().second;
}

Instance* GetPPInstance()
{
	Instance& instance = NP_INSTANCES.end().second;
	return instance;
}

PPB_GetInterface pp_browser_interface;
static std::string userAgent;

// May not be 0 because are pointers in NaCL
static PP_Module moduleId     = 1;
static PP_Instance instanceId = 1;

NPError MapError_PP_2_NP(int32_t result)
{
	switch( result )
	{
		case PP_OK:
		case PP_OK_COMPLETIONPENDING:
			return NPERR_NO_ERROR;
		case PP_ERROR_BADARGUMENT:
			return NPERR_INVALID_PARAM;
		case PP_ERROR_NOMEMORY:
			return NPERR_OUT_OF_MEMORY_ERROR;
		case PP_ERROR_FILENOTFOUND:
			return NPERR_FILE_NOT_FOUND;
		case PP_ERROR_FAILED:
		case PP_ERROR_ABORTED:
		case PP_ERROR_BADRESOURCE:
		case PP_ERROR_NOINTERFACE:
		case PP_ERROR_NOACCESS:
		case PP_ERROR_NOSPACE:
		case PP_ERROR_NOQUOTA:
		case PP_ERROR_INPROGRESS:
		case PP_ERROR_NOTSUPPORTED:
		case PP_ERROR_BLOCKS_MAIN_THREAD:
		case PP_ERROR_FILEEXISTS;
		case PP_ERROR_FILETOOBIG:
		case PP_ERROR_FILECHANGED:
		case PP_ERROR_TIMEDOUT:
		case PP_ERROR_USERCANCEL:
		case PP_ERROR_CONTEXT_LOST:
			return NPERR_GENERIC_ERROR;
		default:
			std::err << "Unknown Pepper error code: [" << result << "]";
			return NPERR_GENERIC_ERROR;
	}
	
/* Unused:

NPERR_INVALID_INSTANCE_ERROR     2	Invalid instance passed to the plug-in
NPERR_INVALID_FUNCTABLE_ERROR    3	Function table invalid
NPERR_MODULE_LOAD_FAILED_ERROR   4	Loading of plug-in failed
NPERR_INVALID_PLUGIN_ERROR       6	Plug-in missing or invalid
NPERR_INVALID_PLUGIN_DIR_ERROR   7	Plug-in directory missing or invalid
NPERR_INCOMPATIBLE_VERSION_ERROR 8	Versions of plug-in and Communicator do not match
NPERR_INVALID_URL               10	URL missing or invalid
NPERR_NO_DATA                   12	Stream contains no data
NPERR_STREAM_NOT_SEEKABLE       13	Seekable stream expected
*/
}

int32_t MapError_NP_2_PP(NPError result)
{
	switch( result )
	{
		case NPERR_NO_ERROR:
			return PP_OK;
		case NPERR_INVALID_PARAM:
			return PP_ERROR_BADARGUMENT;
		case NPERR_OUT_OF_MEMORY_ERROR:
			return PP_ERROR_NOMEMORY;
		case NPERR_FILE_NOT_FOUND:
			return PP_ERROR_FILENOTFOUND;
		case NPERR_GENERIC_ERROR:
		case NPERR_INVALID_INSTANCE_ERROR:
		case NPERR_INVALID_FUNCTABLE_ERROR:
		case NPERR_MODULE_LOAD_FAILED_ERROR:
		case NPERR_INVALID_PLUGIN_ERROR:
		case NPERR_INVALID_PLUGIN_DIR_ERROR:
		case NPERR_INCOMPATIBLE_VERSION_ERROR:
		case NPERR_INVALID_URL:
		case NPERR_NO_DATA:
		case NPERR_STREAM_NOT_SEEKABLE:
			return PP_ERROR_FAILED;
		default:
			std::err << "Unknown NPAPI error code: [" << result << "]";
			return PP_ERROR_FAILED;
	}
}

static const size_t OPENGLES2_HASH = std::hash(PPB_OPENGLES2_INTERFACE);
static const size_t PPB_VAR_DEPRECATED_HASH = std::hash(PPB_VAR_DEPRECATED_INTERFACE);

const void* get_wrapped_np_interface(const char* interface_name)
{
	size_t interface_hash = std::hash(interface_name);
	
	switch( interface_hash )
	{
	case OPENGLES2_HASH:
		return BROWSER_OPENGLES2;
	case PPB_VAR_DEPRECATED_HASH:
		return BROWSER_VAR_DEPRECATED;
	default:
	{
		std::err << "Interface not known " + interface_name;
		return nullptr;
	}
}

//
// BEGIN - Callback into our plugin
//

NPError NewProcPtr(NPMIMEType pluginType, NPP instance, uint16_t mode, int16_t argc, char* argn[], char* argv[], NPSavedData* saved)
{
	ThreadInstance rememberNPInstance(instance);
	return NPERR_NO_ERROR;
}

NPError DestroyProcPtr(NPP instance, NPSavedData** save)
{
	ThreadInstance rememberNPInstance(instance);
	return NPERR_NO_ERROR;
}

NPError SetWindowProcPtr(NPP instance, NPWindow* window)
{
	ThreadInstance rememberNPInstance(instance);
	return NPERR_NO_ERROR;
}

NPError NewStreamProcPtr(NPP instance, NPMIMEType type, NPStream* stream, NPBool seekable, uint16_t* stype)
{
	ThreadInstance rememberNPInstance(instance);
	return NPERR_NO_ERROR;
}

NPError DestroyStreamProcPtr(NPP instance, NPStream* stream, NPReason reason)
{
	ThreadInstance rememberNPInstance(instance);
	return NPERR_NO_ERROR;
}

int32_t NPP_WriteReadyProcPtr(NPP instance, NPStream* stream);
int32_t WriteProcPtr(NPP instance, NPStream* stream, int32_t offset, int32_t len, void* buffer)
{
	ThreadInstance rememberNPInstance(instance);
}

void* StreamAsFileProcPtr(NPP instance, NPStream* stream, const char* fname)
{
	ThreadInstance rememberNPInstance(instance);
}

void PrintProcPtr(NPP instance, NPPrint* platformPrint)
{
	ThreadInstance rememberNPInstance(instance);
}

int16_t HandleEventProcPtr(NPP instance, void* event)
{
	ThreadInstance rememberNPInstance(instance);
}

void URLNotifyProcPtr(NPP instance, const char* url, NPReason reason, void* notifyData)
{
	ThreadInstance rememberNPInstance(instance);
}

/* Any NPObjects returned to the browser via NPP_GetValue should be retained
   by the plugin on the way out. The browser is responsible for releasing. */
NPError GetValueProcPtr(NPP instance, NPPVariable variable, void *ret_value)
{
	ThreadInstance rememberNPInstance(instance);
	return NPERR_NO_ERROR;
}

NPError SetValueProcPtr(NPP instance, NPNVariable variable, void *value)
{
	ThreadInstance rememberNPInstance(instance);
	return NPERR_NO_ERROR;
}

NPBool NPP_GotFocusPtr(NPP instance, NPFocusDirection direction)
{
	ThreadInstance rememberNPInstance(instance);
}

void LostFocusPtr(NPP instance)
{
	ThreadInstance rememberNPInstance(instance);
}

void URLRedirectNotifyPtr(NPP instance, const char* url, int32_t status, void* notifyData)
{
	ThreadInstance rememberNPInstance(instance);
}

NPError ClearSiteDataPtr(const char* site, uint64_t flags, uint64_t maxAge)
{
	return NPERR_NO_ERROR;
}

char** GetSitesWithDataPtr()
{
}

void setCallback(NPPluginFuncs* pFuncs)
{
	pFuncs->size              = sizeof(NPPluginFuncs);
	pFuncs->version           = (NP_VERSION_MAJOR << 8) | NP_VERSION_MINOR;
	pFuncs->newp              = NewProcPtr;
	pFuncs->destroy           = DestroyProcPtr;
	pFuncs->setwindow         = SetWindowProcPtr;
	pFuncs->newstream         = NewStreamProcPtr;
	pFuncs->destroystream     = DestroyStreamProcPtr;
	pFuncs->asfile            = StreamAsFileProcPtr;
	pFuncs->writeready        = WriteReadyProcPtr;
	pFuncs->write             = WriteProcPtr;
	pFuncs->print             = PrintProcPtr;
	pFuncs->event             = HandleEventProcPtr;
	pFuncs->urlnotify         = URLNotifyProcPtr;
	pFuncs->javaClass         = nullptr; //Are you kidding me?
	pFuncs->getvalue          = GetValueProcPtr;
	pFuncs->setvalue          = SetValueProcPtr;
	pFuncs->gotfocus          = GotFocusPtr;
	pFuncs->lostfocus         = LostFocusPtr;
	pFuncs->urlredirectnotify = URLRedirectNotifyPtr;
	pFuncs->clearsitedata     = ClearSiteDataPtr;
	pFuncs->getsiteswithdata  = GetSitesWithDataPtr;
}

//
// END - Callback into our plugin
//

//
// Module handling
//

#ifdef WINAPI
NPError WINAPI NP_Initialize(NPNetscapeFuncs *aNPNFuncs) // Windows
#else
NPError NP_Initialize(NPNetscapeFuncs *aNPNFuncs, NPPluginFuncs *aNPPFuncs) // Linux
#endif
{
	// Get the user agent from the browser.
	const char* result = NPN_UserAgent();
	
	if( !result )
		return NPERR_OUT_OF_MEMORY_ERROR;

	// Memorize
	userAgent = result;

	NPError error = MapError_PP_2_NP
	(
		PPP_InitializeModule
		(
			moduleId,
			get_wrapped_np_interface
		)
	);
	
	if( error == NPERR_NO_ERROR )
	{
		moduleId++;
		setCallback(aNPPFuncs);
	}
		
	return error;
}


NPError NP_Shutdown()
{
	PPP_ShutdownModule();
	instanceId = 1;
	return NPERR_NO_ERROR;
}

//
// Instance handling
//

constexpr PPP_Instance* GetInstanceInterface()
{
	return const_cast<PPP_Instance*>(pp::Module::Get()->GetPluginInterface(PPP_INSTANCE_INTERFACE));
}

Instance* GetInstance(NPP instance)
{
	return pp::Module::Get()->InstanceForPPInstance((PP_Instance)*instance->pdata);
}

NPError NPP_New(NPMIMEType pluginType,
                NPP instance, uint16 mode,
                int16 argc, char *argn[],
                char *argv[], NPSavedData *saved)
{
	ThreadInstance rememberNPInstance(NPP);
	PPP_Instance* callInterface = GetInstanceInterface();
	
	if( !callInterface )
		return NPERR_GENERIC_ERROR;
	
	if
	(
		callInterface->DidCreate
		(
			instanceId,
			arc,
			argn,
			argv
		)
	)
	{
		instance->pdata = &instanceId;
		instanceId++;
		return NPERR_NO_ERROR;
	}
	
	return NPERR_GENERIC_ERROR;
}
 
NPError NPP_Destroy(NPP instance,
                    NPSavedData **save)
{
	ThreadInstance rememberNPInstance(NPP);
	Instance* ppInstance = GetInstance(instance);
	
	PPP_Instance* callInterface = GetInstanceInterface();
	
	if( !callInterface )
		return NPERR_GENERIC_ERROR;
		
	callInterface->DidDestroy(ppInstance);
	return NPERR_NO_ERROR;
}

