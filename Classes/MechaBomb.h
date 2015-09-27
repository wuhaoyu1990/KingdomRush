#ifndef _MECHA_BOMB_H_
#define _MECHA_BOMB_H_

#include "cocos2d.h"
#include "Bullet.h"

USING_NS_CC;

class MechaBomb : public Bullet
{
public:
    virtual bool init();
    CREATE_FUNC(MechaBomb);
	void shoot();
	void removeBullet();
};

#endif