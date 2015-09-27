#ifndef _SIMPLE_MAGE_TOWER_LVL1_H_
#define _SIMPLE_MAGE_TOWER_LVL1_H_

#include "cocos2d.h"
#include "BaseMageTower.h"

USING_NS_CC;

class SimpleMageTowerlvl1: public BaseMageTower
{
public:

	bool init();
    CREATE_FUNC(SimpleMageTowerlvl1);
	void updateTower();
	void showUpdateMenu();
	Bullet* MageTowerBullet();
private:
	void buildingAnimation();
	void buildingSmokeAnimation(float dt);
};

#endif