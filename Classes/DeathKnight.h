#ifndef _DEATH_KNIGHT_H_
#define _DEATH_KNIGHT_H_

#include "BaseSoldier.h"

class DeathKnight : public BaseSoldier
{
public:
	bool init();
	CREATE_FUNC(DeathKnight);
	static DeathKnight* createDeathKnight(Point point);
	void update(float dt);
	void attackMonster(float dt);
	void birth(Point point);
	void createAndSetHpBar();
};

#endif