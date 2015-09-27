#ifndef _BASE_MAGE_TOWER_H_
#define _BASE_MAGE_TOWER_H_
#include "cocos2d.h"
#include "BaseTower.h"
#include "Bullet.h"
USING_NS_CC;

class BaseMageTower:public BaseTower
{
public:

protected:
	Sprite* shooter;
	Sprite* towerBase;
	Bullet* currBullet;
	void initTower(int level);
	void addTerrain();

	virtual Bullet* MageTowerBullet();
	void shoot(float dt);
};
#endif