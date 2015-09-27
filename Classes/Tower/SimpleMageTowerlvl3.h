#ifndef _SIMPLE_MAGE_TOWER_LVL3_H_
#define _SIMPLE_MAGE_TOWER_LVL3_H_

#include "cocos2d.h"
#include "BaseMageTower.h"

USING_NS_CC;

class SimpleMageTowerlvl3: public BaseMageTower
{
public:
	bool init();
	CREATE_FUNC(SimpleMageTowerlvl3);
	void updateTower();
	void showUpdateMenu();
	Bullet* MageTowerBullet();
	void update1();
	void update2();
private:

};


#endif