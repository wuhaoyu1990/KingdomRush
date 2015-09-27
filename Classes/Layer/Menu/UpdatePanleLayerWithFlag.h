#ifndef _UPDATE_PANLE_LAYER_WITH_FLAG_H_
#define _UPDATE_PANLE_LAYER_WITH_FLAG_H_

#include "cocos2d.h"
#include "Circle.h"
#include "BaseBarracksTower.h"
#include "SellIcon.h"

USING_NS_CC; 

class UpdatePanleLayerWithFlag: public Layer
{
public:
    virtual bool init() override;
    CREATE_FUNC(UpdatePanleLayerWithFlag);
	void inAnimation();
	BaseBuildIcon* updateIcon;
	SellIcon* sellIcon;
	bool couldUpdate;
	Sprite* lock;
	Sprite* flag;
	CC_SYNTHESIZE(BaseBarracksTower*, tower, Tower); 
private:  
	void addIcons();
	void showTowerInfo();
	Sprite* planesprite; 
	bool onTouchBegan(Touch *touch, Event *event);
    void onTouchEnded(Touch* touch, Event* event);
	bool isBuilt;
};

#endif