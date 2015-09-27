#ifndef _UPDATE_PANLE_LAYER2_WITHFLAG_H_
#define _UPDATE_PANLE_LAYER2_WITHFLAG_H_

#include "cocos2d.h"
#include "Circle.h"
#include "UpdateIcon.h"
#include "BaseTower.h"
#include "SellIcon.h"

USING_NS_CC; 

class UpdatePanleLayer2: public Sprite
{
public:
    virtual bool initWithIcons(int icon1,int icon2,int money1,int money2);
	static UpdatePanleLayer2* createPanle(int icon1,int icon2,int money1,int money2);
    CREATE_FUNC(UpdatePanleLayer2);
	void inAnimation();
	BaseBuildIcon* updateIcon1;
	BaseBuildIcon* updateIcon2;
	SellIcon* sellIcon;
	bool couldUpdate1;
	bool couldUpdate2;
	Sprite* lock1;
	Sprite* lock2;
	Circle* thisLvlCircle;
	Circle* nextLvlCircle;
	CC_SYNTHESIZE(BaseTower*, tower, Tower); 
private:  
	void addIcons();
	Sprite* planesprite; 
	void showTowerInfo_1();
	void showTowerInfo_2();
	bool onTouchBegan(Touch *touch, Event *event);
    void onTouchEnded(Touch* touch, Event* event);
	bool isBuilt;
};

#endif