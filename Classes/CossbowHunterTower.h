#ifndef _CORSSBOW_HUNTER_TOWER_H_
#define _CORSSBOW_HUNTER_TOWER_H_

#include "cocos2d.h"
#include "BaseArrowTower.h"

USING_NS_CC;

class CossbowHunterTower: public BaseArrowTower
{
public:
	bool init();
    CREATE_FUNC(CossbowHunterTower);
	void showUpdateMenu();
	Bullet* ArrowTowerBullet();

private:
	void shoot(float dt);
	int attackCount;
	Sprite* hawk;
};


#endif