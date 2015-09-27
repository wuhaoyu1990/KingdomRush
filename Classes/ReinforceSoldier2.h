#ifndef _REINFORCE_SOLDIER_2_H_
#define _REINFORCE_SOLDIER_2_H_

#include "BaseSoldier.h"

class ReinforceSoldier2 : public BaseSoldier
{
public:
	bool init();
	CREATE_FUNC(ReinforceSoldier2);
	static ReinforceSoldier2* createReinforceSoldier(Point point);
	void update(float dt);
	void attackMonster(float dt);
	void birth(Point point);
	void checkNearestMonster();
	bool checkDirectionForMonster();
	void runToMonster();
};

#endif