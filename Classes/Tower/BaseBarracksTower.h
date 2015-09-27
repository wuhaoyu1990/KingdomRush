#ifndef _BASE_BARRACKS_TOWER_H_
#define _BASE_BARRACKS_TOWER_H_

#include "cocos2d.h"
#include "BaseTower.h"
#include "BaseSoldier.h"

USING_NS_CC;

class BaseBarracksTower: public BaseTower
{
public:
	bool init();
	void updateTower();
	void showUpdateMenu();
	CREATE_FUNC(BaseBarracksTower);
	void buildingAnimation();
	void setRallyPoint(Point location);
	void update1();
	void update2();
	void sellTower();
private:
	void buildingSmokeAnimation(float dt);
protected:
	void initTower();
	void addTerrain();
	Sprite* towerBase;
	Sprite* door;
	Vector<BaseSoldier*> Soldiers;
	void cureSoldiers(float dt);
	void initSoldierLocation();
};


#endif