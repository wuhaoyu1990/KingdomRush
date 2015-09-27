#ifndef _SHIT_H_
#define _SHIT_H_

#include "Bullet.h"
#include "cocos2d.h"
USING_NS_CC;

class Shit : public Bullet
{
public:
    virtual bool init();
    CREATE_FUNC(Shit);
	void shoot();
	void removeBullet();
};

#endif