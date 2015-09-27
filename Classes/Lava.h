#ifndef _LAVA_H_
#define _LAVA_H_

#include "cocos2d.h"
#include "Bullet.h"

USING_NS_CC;

class Lava : public Bullet
{
public :
	bool init();
	CREATE_FUNC(Lava);
	void shoot();
	Vector<Sprite*> Lavas;
};

#endif