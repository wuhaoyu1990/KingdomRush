#ifndef _BOMB_H_
#define _BOMB_H_

#include "cocos2d.h"
#include "Bullet.h"

USING_NS_CC;

class Bomb : public Bullet
{
public:
	static Bomb* createBombWithType(int type);
    virtual bool initWithType(int type);
	int type;
    CREATE_FUNC(Bomb);
	void shoot();
	void removeBullet();
};

#endif