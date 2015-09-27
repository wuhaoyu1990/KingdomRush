#ifndef _TOUCH_LAYER_H_
#define _TOUCH_LAYER_H_

#include "cocos2d.h"
#include "BaseTower.h"
#include "RallyCircle.h"

USING_NS_CC;

class TouchLayer :public Layer
{
public:
	virtual bool init();
    CREATE_FUNC(TouchLayer);
	EventListenerTouchOneByOne* listener;
	EventListenerTouchOneByOne* touchlistener;
	EventListenerTouchOneByOne* Soldierlistener;
	EventListenerTouchOneByOne* Freezelistener;
	EventListenerTouchOneByOne* Dynamitelistener;
	EventListenerTouchOneByOne* FiereBalllistener;

	void setDynamiteTouchShield();
	void removeDynamiteTouchShield();
	bool onDynamiteTouchBegan(Touch* touch, Event* event);
	void onDynamiteTouchEnded(Touch* touch, Event* event);

	void setRallyFlagTouchShield();
	void removeRallyFlagTouchShield();
	bool onRallyFlagTouchBegan(Touch* touch, Event* event);
	void onRallyFlagTouchEnded(Touch* touch, Event* event);

	void setSoldierTouchShield();
	void removeSoldierTouchShield();
	bool onSoldierTouchBegan(Touch* touch, Event* event);
	void onSoldierTouchEnded(Touch* touch, Event* event);

	void setFreezeTouchShield();
	void removeFreezeTouchShield();
	bool onFreezeTouchBegan(Touch* touch, Event* event);
	void onFreezeTouchEnded(Touch* touch, Event* event);

	void setFireBallTouchShield();
	void removeFireBallTouchShield();
	bool onFireBallTouchBegan(Touch* touch, Event* event);
	void onFireBallTouchEnded(Touch* touch, Event* event);

	void removeTouchShield();
	void setTouchShield();

	BaseTower* tower;
	void addRallyFlag(Point location);
	void addWrongPlace(Point location);

	bool isFlag;
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	Size winSize;
	bool isMoved;
	RallyCircle* rallyCircle;
	void removeAllListener();
};

#endif