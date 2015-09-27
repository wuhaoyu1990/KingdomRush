#ifndef __Tower_SCENE_H__
#define __Tower_SCENE_H__

#include "cocos2d.h"
#include "TowerDesc.h"
#include "EncyclopediaScene.h"
USING_NS_CC;

class Tower : public cocos2d::Layer
{
	public:
		static cocos2d::Scene* createScene();
		virtual bool init();
		void closeScene(Ref* pSendser);

		virtual bool onTouchBegan(Touch* touch, Event* event);
		virtual void onTouchEnded(Touch* touch, Event* event);

		CREATE_FUNC(Tower);
	private:
		int towerId;
		MenuItemSprite* spriteCloseButton;

		Label* labelName;
		//3个属性
		Label* labelAttackSpeed;
		Label* labelAttackValue;
		Label* labelAttackRange;
		
		Label* labelNotice;

		//3个值
		Label* labelAttackSpeed1;
		Label* labelAttackValue1;
		Label* labelAttackRange1;

		Label* labelNotice1;

		//浮动框框
		Sprite* creepFrame;
		MoveTo *moveFrame;
		Size visibleSize;
		Sprite* bigSprite;

		TowerDesc* towerDesc[50];

};

#endif // __Tower_SCENE_H__
