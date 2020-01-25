#ifndef _HG_Behaviour_
#define _HG_Behaviour_

#include "Component.h"

class Behaviour : public Component
{
public:
	virtual ~Behaviour(void) { }

	virtual void Update(float dt) = 0;

protected:
	Behaviour(void) { }
};

#endif
