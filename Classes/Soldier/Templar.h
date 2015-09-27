#ifndef _TEMPLAR_H_
#define _TEMPLAR_H_

#include "BaseSoldier.h"

class Templar : public BaseSoldier
{
public:
	bool initTemplar();
	CREATE_FUNC(Templar);
	static Templar* createTemplar(Point location);
	void createAndSetHpBar();
	void cheakState();
	void update(float dt);
	//void runToMonster();
	void attackMonster(float dt);
};

#endif