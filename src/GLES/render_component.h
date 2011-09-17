
#ifndef _HW_GLES_IRENDERCOMPONENT_H_
#define _HW_GLES_IRENDERCOMPONENT_H_

#include "include.h"
#include <vector>

class IRenderComponent;

class IRenderComponent
{
private:
	std::vector<IRenderComponent> _renderComponents;
protected:
	
	
	IRenderComponent():
		_renderComponents()
	{
	}
	
	void AddComponent(IRenderComponent& component)
	{
		_renderComponents.push_back(component);
	}
	
public:
	virtual void ApplyTo(RENDER_PROCESSOR* pRenderer)
	{
		for( std::vector<IRenderComponent>::iterator it = _renderComponents.begin(); it != _renderComponents.end(); it++ )
		{
			(*it).ApplyTo(pRenderer);
		}
	}
};

#endif //_HW_GLES_IRENDERCOMPONENT_H_

