#ifndef _DYNAMITE_H_
#define _DYNAMITE_H_

#include "cocos2d.h"
#include "Bullet.h"

USING_NS_CC;

class Dynamite : public Bullet
{
public:
    virtual bool init();
    CREATE_FUNC(Dynamite);
	void shoot(Point point);
	void removeBullet();
private:
	
};

#endif