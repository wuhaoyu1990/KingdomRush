#ifndef _ASSASSIN_H_
#define _ASSASSIN_H_

#include "BaseSoldier.h"

class Assassin : public BaseSoldier
{
public:
	bool initAssassin();
	CREATE_FUNC(Assassin);
	static Assassin* createAssassin(Point location);
	void createAndSetHpBar();
	void cheakState();
	void update(float dt);
	//void runToMonster();
	void attackMonster(float dt);
};

#endif