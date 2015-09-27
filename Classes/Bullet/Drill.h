#ifndef _DRILL_H_
#define _DRILL_H_

#include "cocos2d.h"
#include "Bullet.h"
#include "BaseMonster.h"

USING_NS_CC;

class Drill : public Bullet
{
public:
    virtual bool init();
    CREATE_FUNC(Drill);
	void shoot();
	void removeBullet();
	Sprite* drill;
	void DrillMonster(float dt);
	BaseMonster* monsterToBeDrilled;
};

#endif