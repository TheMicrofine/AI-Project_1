#ifndef _HG_PursueBehaviour_
#define _HG_PursueBehaviour_

#include "Behaviour.h"
#include "Entity.h"

class PursueBehaviour : public Behaviour
{
public:
	PursueBehaviour(Entity* agent, Entity* target);
	virtual ~PursueBehaviour(void);

	virtual void Update(float dt);

private:
	Entity* mAgent;
	Entity* mTarget;
};

#endif
