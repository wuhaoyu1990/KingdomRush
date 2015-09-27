#ifndef _UPDATE_PANLE_LAYER2_WITHFLAG_H_
#define _UPDATE_PANLE_LAYER2_WITHFLAG_H_

#include "cocos2d.h"
#include "Circle.h"
#include "UpdateIcon.h"
#include "BaseBarracksTower.h"
#include "SellIcon.h"

USING_NS_CC; 

class UpdatePanleLayer2WithFlag: public Sprite
{
public:
    virtual bool initWithIcons(int icon1,int icon2,int money1,int money2);
	static UpdatePanleLayer2WithFlag* createPanle(int icon1,int icon2,int money1,int money2);
    CREATE_FUNC(UpdatePanleLayer2WithFlag);
	void inAnimation();
	BaseBuildIcon* updateIcon1;
	BaseBuildIcon* updateIcon2;
	SellIcon* sellIcon;
	bool couldUpdate1;
	bool couldUpdate2;
	Sprite* lock1;
	Sprite* lock2;
	CC_SYNTHESIZE(BaseBarracksTower*, tower, Tower); 
	Sprite* flag;
private:  
	void addIcons();
	Sprite* planesprite; 
	
	bool onTouchBegan(Touch *touch, Event *event);
    void onTouchEnded(Touch* touch, Event* event);
	bool isBuilt;
};

#endif