#ifndef _TOWER_PANLE_LAYER_H_
#define _TOWER_PANLE_LAYER_H_

#include "cocos2d.h"
#include "Circle.h"
#include "Terrain.h"
#include "BaseBuildIcon.h"

USING_NS_CC; 

class TowerPanleLayer: public Sprite
{
public:
    virtual bool init() override;
    CREATE_FUNC(TowerPanleLayer);
    // 重载触摸回调函数
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchEnded(Touch* touch, Event* event);
    CC_SYNTHESIZE(Terrain*, terrain, MyTerrain); 
	void inAnimation();
private:    
	void addIcons();
	void addTempTower(int type);
	void addTower(int type);
    BaseBuildIcon* archerIcon; 
	BaseBuildIcon* artilleryIcon;
	BaseBuildIcon* barracksIcon;
	BaseBuildIcon* magicIcon;
	Sprite* planesprite; 
	Circle* circle;
	Sprite *tempTower;
	bool isBuilt;
};

#endif