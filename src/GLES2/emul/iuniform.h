
#ifndef _HW_GLES_IUNIFORM_H_
#define _HW_GLES_IUNIFORM_H_

#include "include.h"
#include "../../GLES/render_component.h"
#include <memory>
#include <string>

template<typename T, GLubyte NUMBER>
class IUniform : public IRenderComponent
{
public:
	class ICustomData
	{
	protected:
		friend class std::unique_ptr<ICustomData>;
		ICustomData()
		{
		}
	};
private:
	std::unique_ptr<ICustomData> _pointer;
	std::string _name;
protected:
	IUniform(const std::string&& name):
		IRenderComponent(),
		_pointer(),
		_name(std::move(name))
	{
	}
public:

	ONLY_MOVE(IUniform)
	
#if HAS_MOVE_ASSIGN_BUG
	IUniform& operator=(IUniform&& other)
	{
		IRenderComponent::operator=(std::move(other));
		_pointer = std::move(other._pointer);
		_name = std::move(other._name);
		return *this;
	}
#endif
	
	const std::string& GetName() const
	{
		return _name;
	}
	
	ICustomData* GetCustomData() const
	{
		return _pointer.get();
	}
	
	void SetCustomData(std::unique_ptr<ICustomData>&& data)
	{
		_pointer = std::move(data);
	};
	
	void ClearCustomData()
	{
		_pointer = nullptr;
	}
};

#endif //_HW_GLES_IUNIFORM_H_

