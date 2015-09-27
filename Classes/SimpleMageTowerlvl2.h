#ifndef _SIMPLE_MAGE_TOWER_LVL2_H_
#define _SIMPLE_MAGE_TOWER_LVL2_H_

#include "cocos2d.h"
#include "BaseMageTower.h"

USING_NS_CC;

class SimpleMageTowerlvl2: public BaseMageTower
{
public:
	bool init();
    CREATE_FUNC(SimpleMageTowerlvl2);
	void updateTower();
	void showUpdateMenu();
	Bullet* MageTowerBullet();
private:

};


#endif