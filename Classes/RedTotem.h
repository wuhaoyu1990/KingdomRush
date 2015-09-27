#ifndef _RED_TOTEM_H_
#define _RED_TOTEM_H_

#include "cocos2d.h"
#include "Bullet.h"

USING_NS_CC;

class RedTotem : public Bullet
{
public:
	static RedTotem* createRedTotem(Point point);
    virtual bool init();
    CREATE_FUNC(RedTotem);
	void shoot(Point location);
	void removeBullet();
	void boom();
};

#endif