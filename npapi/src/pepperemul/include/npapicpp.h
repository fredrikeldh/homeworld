#ifdef  _NPAPICPP_H_
#define _NPAPICPP_H_

using namespace npapi;

template<typename T>
class AbstractValue
{
protected:
	virtual T IsValidType(const NPVariant& variant) = 0;
	vritual T GetValue(const NPVariant& variant) = 0;

	AbstractValue(const NPVariant& variant) :
		value()
	{
	}
	
	void init(T value)
	{
		this = value;
	}
	
	virtual T GetValue(const NPVariant& variant) = 0;
public:
	bool operator=(const T value)
	{
		_value = value;
	}
	
	bool operator=(const NPVariant& variant)
	{
		if( !IsValidType(variant) )
			throw -1;
			
		this = GetValue(variant);
	}
private:
	T _value;
};

class BoolValue : public AbstractValue<bool>
{
public:
	static BoolValue create(bool value)
	{
		BoolValue value;
		value.init(value);
		return value;
	}
protected:
	bool IsValidType(const NPVariant& variant)
	{
		return NPVARIANT_IS_BOOLEAN(variant);
	}
	
	bool GetValue(const NPVariant& variant)
	{
		return NPVARIANT_TO_BOOLEAN(variant);
	}
};

class Int32Value : public AbstractValue<int32_t>
{
public:
	static Int32Value create(int32_t value)
	{
		Int32Value value;
		value.init(value);
		return value;
	}
protected:
	bool IsValidType(const NPVariant& variant)
	{
		return NPVARIANT_IS_INT32(variant);
	}
	
	int32_t GetValue(const NPVariant& variant)
	{
		return NPVARIANT_TO_INT32(variant);
	}
};

class DoubleValue : public AbstractValue<double_t>
{
public:
	static double_t create(double_t value)
	{
		DoubleValue value;
		value.init(value);
		return value;
	}
protected:
	bool IsValidType(const NPVariant& variant)
	{
		return NPVARIANT_IS_DOUBLE(variant);
	}
	
	int32_t GetValue(const NPVariant& variant)
	{
		return NPVARIANT_TO_DOUBLE(variant);
	}
};

class StringValue : public AbstractValue<NPString>
{
public:
	static NPString create(NPString&& value)
	{
		StringValue value;
		value.init(value);
		return value;
	}
protected:
	bool IsValidType(const NPVariant& variant)
	{
		return NPVARIANT_IS_STRING(variant);
	}
	
	NPString GetValue(const NPVariant& variant)
	{
		return NPVARIANT_TO_STRING(variant);
	}
};

class ObjectValue : public AbstractValue<NPObject*>
{
public:
	static NPObject* create(NPObject* value)
	{
		ObjectValue* value = new ObjectValue();;
		value->init(value);
		return value;
	}
protected:
	bool IsValidType(const NPVariant& variant)
	{
		return NPVARIANT_IS_OBJECT(variant);
	}
	
	NPObject* GetValue(const NPVariant& variant)
	{
		return NPVARIANT_TO_OBJECT(variant);
	}
};

class Function
{
};

#endif //_NPAPICPP_H_

