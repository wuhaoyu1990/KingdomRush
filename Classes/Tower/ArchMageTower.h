#ifndef _ARCH_MAGE_TOWER_H_
#define _ARCH_MAGE_TOWER_H_

#include "cocos2d.h"
#include "BaseMageTower.h"
#include "Twister.h"

USING_NS_CC;

class ArchMageTower: public BaseMageTower
{
public:
	bool init();
	CREATE_FUNC(ArchMageTower);
	void getTwister(int level);
	void getForce(int level);
	void showUpdateMenu();
	Bullet* MageTowerBullet();
	void Attack(float dt);
	void AtTwister(float dt);
	void sellTower();
private:
	void buildDelayBullet();
	Bullet* DelayBullet[3];
};

#endif