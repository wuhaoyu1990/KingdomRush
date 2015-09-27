#ifndef _REINFORCE_SOLDIER_1_H_
#define _REINFORCE_SOLDIER_1_H_

#include "BaseSoldier.h"

class ReinforceSoldier1 : public BaseSoldier
{
public:
	bool init();
	CREATE_FUNC(ReinforceSoldier1);
	static ReinforceSoldier1* createReinforceSoldier(Point point);
	void update(float dt);
	void attackMonster(float dt);
	void birth(Point point);
	void checkNearestMonster();
	bool checkDirectionForMonster();
	void runToMonster();
};

#endif