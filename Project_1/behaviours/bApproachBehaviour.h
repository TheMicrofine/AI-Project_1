#ifndef _HG_ApproachBehaviour_
#define _HG_ApproachBehaviour_

#include "Behaviour.h"
#include "Entity.h"

class ApproachBehaviour : public Behaviour
{
public:
	ApproachBehaviour(Entity* agent, Entity* target);
	virtual ~ApproachBehaviour(void);

	virtual void Update(float dt);

private:
	Entity* mAgent;
	Entity* mTarget;
};

#endif
