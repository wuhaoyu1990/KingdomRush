#ifndef _FREEZE_H_
#define _FREEZE_H_

#include "cocos2d.h"
#include "Bullet.h"
USING_NS_CC;

class Freeze : public Bullet
{
public:
    virtual bool init();
    CREATE_FUNC(Freeze);
	void shoot(Point point);
	void removeBullet();
private:
	
};

#endif