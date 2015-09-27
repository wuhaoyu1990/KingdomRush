#ifndef _TOTEM_TOWER_H_
#define _TOTEM_TOWER_H_

#include "cocos2d.h"
#include "BaseArrowTower.h"

USING_NS_CC;

class TotemTower: public BaseArrowTower
{
public:
	bool init();
    CREATE_FUNC(TotemTower);
	void showUpdateMenu();
	Bullet* ArrowTowerBullet();

private:
	void shoot(float dt);
	int monstersCount;
	Sprite* eyesDown;
	void checkNearestMonster();
	void TotemCD(float dt);
	bool totemCD;
};


#endif