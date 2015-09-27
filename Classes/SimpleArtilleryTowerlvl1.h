#ifndef _SIMPLE_ARTILLERY_TOWER_LVL1_H_
#define _SIMPLE_ARTILLERY_TOWER_LVL1_H_

#include "cocos2d.h"
#include "BaseArtilleryTower.h"

USING_NS_CC;

class SimpleArtilleryTowerlvl1: public BaseArtilleryTower
{
public:

	virtual bool init();
    CREATE_FUNC(SimpleArtilleryTowerlvl1);
	void updateTower();
	void showUpdateMenu();

private:
	void buildingAnimation();
	void buildingSmokeAnimation(float dt);
};


#endif