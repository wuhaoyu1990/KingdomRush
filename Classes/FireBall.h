#ifndef _FIREBALL_H_
#define _FIREBALL_H_

#include "cocos2d.h"
#include "Bullet.h"

class FireBall : public Bullet
{
public :
	bool init();
	CREATE_FUNC(FireBall);
	void shoot(Point location);
	void removeBullet();
	void smoke(float dt);
	void round();
	void explosion();
};

#endif