#ifndef _SIMPLE_ARROW_TOWER_LVL3_H_
#define _SIMPLE_ARROW_TOWER_LVL3_H_

#include "cocos2d.h"
#include "BaseArrowTower.h"

USING_NS_CC;

class SimpleArrowTowerlvl3: public BaseArrowTower
{
public:
	bool init();
    CREATE_FUNC(SimpleArrowTowerlvl3);
	void updateTower();
	void showUpdateMenu();
	Bullet* ArrowTowerBullet();
	void update1();
	void update2();
private:

};


#endif