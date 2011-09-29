/**********************************************************\

  Auto-generated HomeAPI.cpp

\**********************************************************/

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"

#include "HomeAPI.h"

///////////////////////////////////////////////////////////////////////////////
/// @fn HomeAPI::HomeAPI(const HomePtr& plugin, const FB::BrowserHostPtr host)
///
/// @brief  Constructor for your JSAPI object.  You should register your methods, properties, and events
///         that should be accessible to Javascript from here.
///
/// @see FB::JSAPIAuto::registerMethod
/// @see FB::JSAPIAuto::registerProperty
/// @see FB::JSAPIAuto::registerEvent
///////////////////////////////////////////////////////////////////////////////
HomeAPI::HomeAPI(const HomePtr& plugin, const FB::BrowserHostPtr& host) : m_plugin(plugin), m_host(host)
{
    registerMethod("echo",      make_method(this, &HomeAPI::echo));
    registerMethod("testEvent", make_method(this, &HomeAPI::testEvent));

    // Read-write property
    registerProperty("testString",
                     make_property(this,
                        &HomeAPI::get_testString,
                        &HomeAPI::set_testString));

    // Read-only property
    registerProperty("version",
                     make_property(this,
                        &HomeAPI::get_version));
}

///////////////////////////////////////////////////////////////////////////////
/// @fn HomeAPI::~HomeAPI()
///
/// @brief  Destructor.  Remember that this object will not be released until
///         the browser is done with it; this will almost definitely be after
///         the plugin is released.
///////////////////////////////////////////////////////////////////////////////
HomeAPI::~HomeAPI()
{
}

///////////////////////////////////////////////////////////////////////////////
/// @fn HomePtr HomeAPI::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
HomePtr HomeAPI::getPlugin()
{
    HomePtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}



// Read/Write property testString
std::string HomeAPI::get_testString()
{
    return m_testString;
}
void HomeAPI::set_testString(const std::string& val)
{
    m_testString = val;
}

// Read-only property version
std::string HomeAPI::get_version()
{
    return "CURRENT_VERSION";
}

// Method echo
FB::variant HomeAPI::echo(const FB::variant& msg)
{
    static int n(0);
    fire_echo(msg, n++);
    return msg;
}

void HomeAPI::testEvent(const FB::variant& var)
{
    fire_fired(var, true, 1);
}

