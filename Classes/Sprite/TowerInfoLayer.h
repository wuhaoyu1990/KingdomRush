#ifndef _TOWER_LAYER_H_
#define _TOWER_LAYER_H_

#include "cocos2d.h"
#include"BaseTower.h"

USING_NS_CC;

class TowerInfoLayer : public Sprite
{
public:
	static TowerInfoLayer* createTowerInfoLayer(TowerType towerType);
	virtual bool init(TowerType towerType);
	void setTowerInfo(TowerType towerType);
	Sprite* info_bg;
};
#endif