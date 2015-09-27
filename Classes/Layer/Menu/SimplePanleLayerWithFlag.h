#ifndef _SIMPLE_PANLE_LAYER_WITH_FLAG_H_
#define _SIMPLE_PANLE_LAYER_WITH_FLAG_H_

#include "cocos2d.h"
#include "Circle.h"
#include "BaseTower.h"
#include "SellIcon.h"

USING_NS_CC; 

class SimplePanleLayerWithFlag: public Layer
{
public:
    virtual bool init() override;
    CREATE_FUNC(SimplePanleLayerWithFlag);
	void inAnimation();
	SellIcon* sellIcon;
	Sprite* flag;
	CC_SYNTHESIZE(BaseTower*, tower, Tower); 
private:  
	void addIcons();
	bool isBuilt;
	Sprite* planesprite; 
	bool onTouchBegan(Touch *touch, Event *event);
    void onTouchEnded(Touch* touch, Event* event);
	void showTowerInfo();
};

#endif