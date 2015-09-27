#ifndef _SKELETON_H_
#define _SKELETON_H_

#include "BaseSoldier.h"

class Skeleton : public BaseSoldier
{
public:
	bool init();
	CREATE_FUNC(Skeleton);
	static Skeleton* createSkeleton(Point point);
	void update(float dt);
	void attackMonster(float dt);
	void birth(Point point);
	void runToMonster();
	bool checkDirectionForMonster();
	void checkNearestMonster();
	void createAndSetHpBar();
};

#endif