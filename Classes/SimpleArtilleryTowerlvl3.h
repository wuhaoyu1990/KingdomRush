#ifndef _SIMPLE_ARTILLERY_TOWER_LVL3_H_
#define _SIMPLE_ARTILLERY_TOWER_LVL3_H_

#include "cocos2d.h"
#include "BaseArtilleryTower.h"

USING_NS_CC;

class SimpleArtilleryTowerlvl3: public BaseArtilleryTower
{
public:

	virtual bool init();
    CREATE_FUNC(SimpleArtilleryTowerlvl3);
	void showUpdateMenu();
	void update1();
	void update2();
private:

};


#endif