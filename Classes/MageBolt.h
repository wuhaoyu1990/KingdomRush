#ifndef _MAGEBOLT_H_
#define _MAGEBOLT_H_

#include "cocos2d.h"
#include "Bullet.h"

USING_NS_CC;

class MageBolt : public Bullet
{
public:
    virtual bool init();
    CREATE_FUNC(MageBolt);
	void shoot();
	void removeBullet();
};

	
#endif