#ifndef _BARRACK_Soldier_H_
#define _BARRACK_Soldier_H_

#include "BaseSoldier.h"

class BarrackSoldier : public BaseSoldier
{
public:
	bool initSoldier(int level);
	CREATE_FUNC(BarrackSoldier);
	static BarrackSoldier* createSoldier(Point point,int level);
	CC_SYNTHESIZE(int, level, Level);
	void update(float dt);
	//void runToMonster();
	void attackMonster(float dt);
	void updateSoldier(int level);
};

#endif