#include <mutex>
#include <npapi.h>
#include <npruntime.h>
#include <ppapi/c/pp_var.h>
#include <ppapi/c/pp_module.h>
#include <ppapi/c/dev/ppb_var_deprecated.h>
#include "instance.h"
#include "module.h"
#include "ppp.h"

typedef pp::Module Module;
typedef npapi::HomeInstance HomeInstance;

class PP_String
{
public:
	std::mutex lock;
	uint32_t refcount;
	NPString str;
	
	PP_String(NPString& str) :
		lock(),
		refcount(1),
		str(str)
	{
	}
	
	PP_String() :
		lock(),
		refcount(1),
		str({nullptr, 0})
	{
	}
};

constexpr bool PP_Var_is_string(PP_Var& var)
{
	return var.type == PP_VARTYPE_BOOL;
}

constexpr bool PP_Var_is_int(PP_Var& var)
{
	return var.type == PP_VARTYPE_INT32;
}

constexpr bool PP_Var_is_null(PP_Var& var)
{
	return var.type == PP_VARTYPE_NULL;
}

PP_Var PP_MakeString(PP_String* str)
{
	PP_Var var;
	var.type = PP_VARTYPE_STRING;
	var.padding = 0;
	var.value.as_id = reinterpret_cast<int64_t>(str);
	
	return var;
}

PP_Var PP_MakeString(NPString& str)
{
	PP_String* wrapper = new PP_String(str);
	return PP_MakeString(wrapper);
}

PP_Var PP_MakeString(NPString* str)
{
	return PP_MakeString(*str);
}

PP_Var PP_MakeString(std::string& str)
{
	NPString npstr{str.data(), (uint32_t)str.size()};
	return PP_MakeString(npstr);
}

PP_Var PP_MakeObject(NPObject& object)
{
	PP_Var var;
	var.type = PP_VARTYPE_STRING;
	var.padding = 0;
	var.value.as_id = reinterpret_cast<int64_t>(&object);
	
	return var;
}

PP_Var PP_MakeObject(NPObject* pObject)
{
	if( !pObject )
		return PP_MakeNull();
	
	return PP_MakeObject(*pObject);
}

PP_String* getString(PP_VarValue value)
{
	PP_String* str = (PP_String*)value.as_id;
	return str;
}

PP_String* getString(PP_Var var)
{
	if( PP_Var_is_string(var) )
		return getString(var.value);
	
	return nullptr;
}

NPObject* getObject(PP_VarValue value)
{
	NPObject* obj = (NPObject*)value.as_id;
	return obj;
}

NPObject* getObject(PP_Var var)
{
	return getObject(var.value);
}

NPIdentifier getIdentifier(PP_Var var)
{
	if( PP_Var_is_string(var) || PP_Var_is_int(var) )
		return (NPIdentifier)var.value.as_id;
	
	return nullptr;
}

NPVariant getVariant(PP_Var var)
{
	NPVariant npvar;
	switch( var.type )
	{
	case PP_VARTYPE_UNDEFINED:
		VOID_TO_NPVARIANT(npvar);
		break;
	case PP_VARTYPE_BOOL:
		BOOLEAN_TO_NPVARIANT(var.value.as_bool, npvar);
		break;
	case PP_VARTYPE_INT32:
		INT32_TO_NPVARIANT(var.value.as_int, npvar);
		break;
	case PP_VARTYPE_DOUBLE:
		DOUBLE_TO_NPVARIANT(var.value.as_double, npvar);
		break;
	case PP_VARTYPE_STRING:
	{
		PP_String* pstr = getString(var);
		STRINGN_TO_NPVARIANT(pstr->str.UTF8Characters, pstr->str.UTF8Length, npvar);
		break;
	}
	case PP_VARTYPE_OBJECT:
	{
		NPObject* obj = getObject(var);
		OBJECT_TO_NPVARIANT(obj, npvar);
		break;
	}
	case PP_VARTYPE_NULL:
		NULL_TO_NPVARIANT(npvar);
		break;
	case PP_VARTYPE_ARRAY:
	case PP_VARTYPE_DICTIONARY:
	default:
		throw "UNSUPPORTED TYPE";
	
	}
	
	return npvar;
}

PP_Var PP_Var_from_np(NPVariant& npvar)
{
	switch( npvar.type )
	{
	case NPVariantType_Void:
		return PP_MakeUndefined();
	case NPVariantType_Bool:
		return PP_MakeBool(npvar.value.boolValue ? PP_TRUE : PP_FALSE);
	case PP_VARTYPE_INT32:
		return PP_MakeInt32(npvar.value.intValue);
	case PP_VARTYPE_DOUBLE:
		return PP_MakeDouble(npvar.value.doubleValue);
	case PP_VARTYPE_STRING:
		return PP_MakeString(npvar.value.stringValue);
	case PP_VARTYPE_OBJECT:
		return PP_MakeObject(npvar.value.objectValue);
	case PP_VARTYPE_NULL:
		return PP_MakeNull();
	//case PP_VARTYPE_ARRAY:
	//case PP_VARTYPE_DICTIONARY:
	default:
		throw "UNSUPPORTED TYPE";
	}
}

PP_Var PP_Var_from_np(const NPIdentifier& id)
{
	if( !NPN_IdentifierIsString(id) )
		throw "NO STR";
		
	std::string str(NPN_UTF8FromIdentifier(id));
	
	return PP_MakeString(str);
}

void RetainString(PP_String* value)
{
	std::lock_guard<std::mutex>(value->lock);
	
	if( value->refcount == 1 || value->refcount == 0 )
		delete value;
	else
		value->refcount++;
}

void ReleaseString(PP_String* value)
{
	std::lock_guard<std::mutex>(value->lock);
	
	value->refcount++;
}

template<typename T>
class ConstArray
{
private:
	T* _array;
public:
	ConstArray(PP_Var* source, uint32_t size) :
		_array(new T[size])
	{
		for( uint32_t i = 0; i != size; i++ )
		{
			NPObject* obj = getObject(source[i]);
			OBJECT_TO_NPVARIANT(obj, _array[i]);
		}
		
	}
	
	~ConstArray()
	{
		delete[] _array;
	}
	
	T* get() const
	{
		return _array;
	}
};

/**
 * Adds a reference to the given var. If this is not a refcounted object,
 * this function will do nothing so you can always call it no matter what the
 * type.
 */
void varAddRef(PP_Var var)
{
	switch( var.type )
	{
	case PP_VARTYPE_STRING:
		RetainString(getString(var.value));
		return;
	case PP_VARTYPE_OBJECT:
	case PP_VARTYPE_ARRAY:
	case PP_VARTYPE_DICTIONARY:
		NPN_RetainObject(getObject(var.value));
		return;
	default:
		return;
	}
}


/**
 * Removes a reference to given var, deleting it if the internal refcount
 * becomes 0. If the given var is not a refcounted object, this function will
 * do nothing so you can always call it no matter what the type.
 */
void varRelease(PP_Var var)
{
	switch( var.type )
	{
	case PP_VARTYPE_STRING:
		ReleaseString(getString(var.value));
		return;
	case PP_VARTYPE_OBJECT:
	case PP_VARTYPE_ARRAY:
	case PP_VARTYPE_DICTIONARY:
		NPN_ReleaseObject(getObject(var.value));
		return;
	default:
		return;
	}
}

/**
 * Creates a string var from a string. The string must be encoded in valid
 * UTF-8 and is NOT NULL-terminated, the length must be specified in |len|.
 * It is an error if the string is not valid UTF-8.
 *
 * If the length is 0, the |data| pointer will not be dereferenced and may
 * be NULL. Note, however, that if you do this, the "NULL-ness" will not be
 * preserved, as VarToUtf8 will never return NULL on success, even for empty
 * strings.
 *
 * The resulting object will be a refcounted string object. It will be
 * AddRef()ed for the caller. When the caller is done with it, it should be
 * Release()d.
 *
 * On error (basically out of memory to allocate the string, or input that
 * is not valid UTF-8), this function will return a Null var.
 */
PP_Var varFromUtf8(PP_Module, const char* data, uint32_t len)
{
	NPString* str;
	
	if( data && len )
		str = new NPString{data, len};
	else
		str = nullptr;

	return PP_MakeString(str);
}

/**
 * Converts a string-type var to a char* encoded in UTF-8. This string is NOT
 * NULL-terminated. The length will be placed in |*len|. If the string is
 * valid but empty the return value will be non-NULL, but |*len| will still
 * be 0.
 *
 * If the var is not a string, this function will return NULL and |*len| will
 * be 0.
 *
 * The returned buffer will be valid as long as the underlying var is alive.
 * If the plugin frees its reference, the string will be freed and the pointer
 * will be to random memory.
 */
const char* varToUtf8(PP_Var var, uint32_t* len)
{
	PP_String* str = getString(var.value);
	
	if( str )
	{
		*len = str->str.UTF8Length;
		return str->str.UTF8Characters;
	}
	else
	{
		*len = 0;
		return nullptr;
	}
}

HomeInstance* getInstance()
{
	HomeInstance* instance = static_cast<npapi::HomeInstance*>(GetPPInstance());
	return instance;
}

NPP getNPInstance()
{
	return getInstance()->GetNP();
}


/**
 * Returns true if the property with the given name exists on the given
 * object, false if it does not. Methods are also counted as properties.
 *
 * The name can either be a string or an integer var. It is an error to pass
 * another type of var as the name.
 *
 * If you pass an invalid name or object, the exception will be set (if it is
 * non-NULL, and the return value will be false).
 */
bool varHasProperty(PP_Var object,
                    PP_Var name,
                    PP_Var* exception)
{
	NPObject* npobj = getObject(object);
	NPIdentifier propertyName = getIdentifier(name);
	
	return NPN_HasProperty
	(
		getNPInstance(),
		npobj,
		propertyName
	);
}

/**
 * Identical to HasProperty, except that HasMethod additionally checks if the
 * property is a function.
 */
bool varHasMethod(PP_Var object,
                  PP_Var name,
                  PP_Var* exception)
{
	
	NPObject* npobj = getObject(object);
	NPIdentifier propertyName = getIdentifier(name);
	
	return NPN_HasMethod
	(
		getNPInstance(),
		npobj,
		propertyName
	);
}

/**
 * Returns the value of the given property. If the property doesn't exist, the
 * exception (if non-NULL) will be set and a "Void" var will be returned.
 */
PP_Var varGetProperty(PP_Var object,
                      PP_Var name,
                      PP_Var* exception)
{
	NPObject* npobj = getObject(object);
	NPIdentifier propertyName = getIdentifier(name);

	NPVariant result;
	
	if
	(
		NPN_GetProperty
		(
			getNPInstance(),
			npobj,
			propertyName,
			&result
		)
	)
	{
		PP_Var var;
	
		switch( result.type )
		{
		case NPVariantType_Null:
			var = PP_MakeNull();
			break;
		case NPVariantType_Bool:
			var = PP_MakeBool(result.value.boolValue ? PP_TRUE : PP_FALSE);
			break;
		case NPVariantType_Int32:
			var = PP_MakeInt32(result.value.intValue);
			break;
		case NPVariantType_Double:
			var = PP_MakeDouble(result.value.doubleValue);
			break;
		case NPVariantType_String:
			var = varFromUtf8
			(
				Module::Get()->pp_module(),
				result.value.stringValue.UTF8Characters,
				result.value.stringValue.UTF8Length
			);
			break;
		case NPVariantType_Object:
			var.type = PP_VARTYPE_OBJECT;
			var.padding = 0;
			var.value.as_id = reinterpret_cast<int64_t>(result.value.objectValue);
			break;
		case NPVariantType_Void:
		default:
			var = PP_MakeUndefined();
			//TODO: exception
			break;
		}
		
		return var;
	}
	else
	{
		return PP_MakeUndefined();
		//TODO: exception
	}
}

/**
 * Retrieves all property names on the given object. Property names include
 * methods.
 *
 * If there is a failure, the given exception will be set (if it is non-NULL).
 * On failure, |*properties| will be set to NULL and |*property_count| will be
 * set to 0.
 *
 * A pointer to the array of property names will be placesd in |*properties|.
 * The caller is responsible for calling Release() on each of these properties
 * (as per normal refcounted memory management) as well as freeing the array
 * pointer with PPB_Core.MemFree().
 *
 * This function returns all "enumerable" properties. Some JavaScript
 * properties are "hidden" and these properties won't be retrieved by this
 * function, yet you can still set and get them.
 *
 * Example:
 * <pre>  uint32_t count;
 *   PP_Var* properties;
 *   ppb_var.GetAllPropertyNames(object, &count, &properties);
 *
 *   ...use the properties here...
 *
 *   for (uint32_t i = 0; i < count; i++)
 *     ppb_var.Release(properties[i]);
 *   ppb_core.MemFree(properties); </pre>
 */
void varGetAllPropertyNames(PP_Var object,
                            uint32_t* property_count,
                            PP_Var** ppProperties,
                            PP_Var* exception)
{
	NPIdentifier* pIdentifier = nullptr;
	NPObject* npobj = getObject(object);
	
	if
	(
		NPN_Enumerate
		(
			getNPInstance(),
			npobj,
			&pIdentifier,
			property_count
		)
	)
	{
		*ppProperties = new PP_Var[*property_count];
	
		for( uint32_t i = 0; i != *property_count; i++ )
		{
			(*ppProperties)[i] = PP_Var_from_np(pIdentifier[i]);
		}
		
		//TODO: check memory allocation!
		 NPN_MemFree(pIdentifier);
	}
	else
	{
		//TODO: exception
		*ppProperties = nullptr;
		*property_count = 0;
	}
}

/**
 * Sets the property with the given name on the given object. The exception
 * will be set, if it is non-NULL, on failure.
 */
void varSetProperty(PP_Var object,
                    PP_Var name,
                    PP_Var value,
                    PP_Var* exception)
{
	NPObject* npobj = getObject(object);
	NPIdentifier propertyName = getIdentifier(name);
	NPVariant npvalue = getVariant(value);

	if
	(
		!NPN_SetProperty
		(
			getNPInstance(),
			npobj,
			propertyName,
			&npvalue
		)
	)
		;//TODO: exception
}

/**
 * Removes the given property from the given object. The property name must
 * be an string or integer var, using other types will throw an exception
 * (assuming the exception pointer is non-NULL).
 */
void varRemoveProperty(PP_Var object,
                       PP_Var name,
                       PP_Var* exception)
{
	NPObject* npobj = getObject(object);
	NPIdentifier propertyName = getIdentifier(name);

	if
	(
		NPN_RemoveProperty
		(
			getNPInstance(),
			npobj,
			propertyName
		)
	)
		return;
	
	// Failed
	//TODO: exception
}

// TODO(brettw) need native array access here.

/**
 * Invoke the function |method_name| on the given object. If |method_name|
 * is a Null var, the default method will be invoked, which is how you can
 * invoke function objects.
 *
 * Unless it is type Null, |method_name| must be a string. Unlike other
 * Var functions, integer lookup is not supported since you can't call
 * functions on integers in JavaScript.
 *
 * Pass the arguments to the function in order in the |argv| array, and the
 * number of arguments in the |argc| parameter. |argv| can be NULL if |argc|
 * is zero.
 *
 * Example:
 *   Call(obj, VarFromUtf8("DoIt"), 0, NULL, NULL) = obj.DoIt() in JavaScript.
 *   Call(obj, PP_MakeNull(), 0, NULL, NULL) = obj() in JavaScript.
 */
PP_Var varCall(PP_Var object,
               PP_Var method_name,
               uint32_t argCount,
               PP_Var* argv,
               PP_Var* exception)
{
	NPObject* npobj = getObject(object);
	NPIdentifier methodName = getIdentifier(method_name);
	NPVariant npresult;
	
	ConstArray<NPVariant> args(argv, argCount);
	
	bool success;

	if( PP_Var_is_null(method_name) )
	{
		success = NPN_InvokeDefault
		(
			getNPInstance(),
			npobj,
			args.get(),
			argCount,
			&npresult
		);
	}
	else
	{
		success = NPN_Invoke
		(
			getNPInstance(),
			npobj,
			methodName,
			args.get(),
			argCount,
			&npresult
		);
	}
	
	if( success )
		return PP_Var_from_np(npresult);
		
	//TODO: exception
	return PP_MakeNull();
}


/**
 * Invoke the object as a constructor.
 *
 * For example, if |object| is |String|, this is like saying |new String| in
 * JavaScript.
 */
PP_Var varConstruct(PP_Var object,
                    uint32_t argCount,
                    PP_Var* argv,
                    PP_Var* exception)
{
	NPObject* npobj = getObject(object);

	const ConstArray<NPVariant> args(argv, argCount);

	NPVariant result;

	if
	(
		NPN_Construct
		(
			getNPInstance(),
			npobj,
			args.get(),
			argCount,
			&result
		)
	)
		return PP_Var_from_np(result);
	
	//TODO: exception
	return PP_MakeNull();
}

/**
 * If the object is an instance of the given class, then this method returns
 * true and sets *object_data to the value passed to CreateObject provided
 * object_data is non-NULL. Otherwise, this method returns false.
 */
bool varIsInstanceOf(PP_Var var,
                     const PPP_Class_Deprecated* object_class,
                     void** object_data)
{
	throw "ME YOU FUCK";
}

/**
 * Creates an object that the plugin implements. The plugin supplies a
 * pointer to the class interface it implements for that object, and its
 * associated internal data that represents that object.
 *
 * The returned object will have a reference count of 1. When the reference
 * count reached 0, the class' Destruct function wlil be called.
 *
 * On failure, this will return a null var. This probably means the module
 * was invalid.
 *
 * Example: Say we're implementing a "Point" object.
 * <pre>  void PointDestruct(void* object) {
 *     delete (Point*)object;
 *   }
 *
 *   const PPP_Class_Deprecated point_class = {
 *   ... all the other class functions go here ...
 *   &PointDestruct
 *   };
 *
 *    * The plugin's internal object associated with the point.
 *   class Point {
 *     ...
 *   };
 *
 *   PP_Var MakePoint(int x, int y) {
 *     return CreateObject(&point_class, new Point(x, y));
 *   }</pre>
 */
PP_Var varCreateObject(PP_Module module,
                       const PPP_Class_Deprecated* object_class,
                       void* object_data)
{
	return PP_MakeUndefined();
}

// Like CreateObject but takes a module. This will be deleted when all callers
// can be changed to use the PP_Instance CreateObject one.
PP_Var varCreateObjectWithModuleDeprecated(PP_Module module,
                                           const struct PPP_Class_Deprecated* object_class,
                                           void* object_data)
{
	return PP_MakeUndefined();
}

PPB_Var_Deprecated deprecated = 
{
	varAddRef,
	varRelease,
	varFromUtf8,
	varToUtf8,
	varHasProperty,
	varHasMethod,
	varGetProperty,
	varGetAllPropertyNames,
	varSetProperty,
	varRemoveProperty,
	varCall,
	varConstruct,
	varIsInstanceOf,
	varCreateObject,
	varCreateObjectWithModuleDeprecated
};

