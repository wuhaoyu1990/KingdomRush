#include "Smoke.h"
#include "GameManager.h"

bool Smoke::init()
{
	if (!Sprite::init())
	{
		return false;
	}	
	return true;
}
void Smoke::fadeSmoke(Animation* animation,float time)
{
	runAction(Sequence::create(Animate::create(animation),
							   DelayTime::create(time),
                               CallFuncN::create(CC_CALLBACK_0(Smoke::remove, this)),
                               NULL));
}
void Smoke::remove()
{
	this->removeFromParent();
}