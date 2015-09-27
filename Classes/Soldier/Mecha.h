#ifndef _MECHA_H_
#define _MECHA_H_

#include "BaseSoldier.h"
#include "Bomb.h"

class Mecha : public BaseSoldier
{
public:
	bool init();
	CREATE_FUNC(Mecha);
	void runToLocation(Point location);
private:
	void shootMissiles();
	void bombMonster(float dt);
	void checkNearestMonster();
	void checkFarestMonster();
	Bomb* MechaBullet();
	BaseMonster* farestMonster1;
	BaseMonster* farestMonster2;
	int monsterCount;
	Sprite* shit;
	void addShit();
	void shitting();
	void shitCD(float dt);
	bool couldShit;
};

#endif