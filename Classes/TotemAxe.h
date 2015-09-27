#ifndef _TOTEM_AXE_H_
#define _TOTEM_AXE_H_

#include "cocos2d.h"
#include "Bullet.h"

USING_NS_CC;

class TotemAxe : public Bullet
{
public:
    virtual bool init();
    CREATE_FUNC(TotemAxe);
	void shoot();
	void removeBullet();
};

#endif