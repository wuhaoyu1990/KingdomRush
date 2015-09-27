#ifndef _BASE_Soldier_H_
#define _BASE_Soldier_H_

#include "SoundManager.h"
#include "BaseMonster.h"
#include "cocos2d.h"
USING_NS_CC;

typedef enum{
    SoldierStateNone = 0, //ÎÞ×´Ì¬
    SoldierStateRun,//ÐÐ×ß
	SoldierStateHit, //¹¥»÷
	SoldierStateDeath,//ËÀÍö
	SoldierStateWait,//Ñ°ÕÒµÐÈË
	SoldierStateSkill1,
	SoldierStateSkill2
}SoldierState;

class BaseSoldier : public Sprite
{
public:
	CC_SYNTHESIZE(float, maxHp, MaxHp);
    CC_SYNTHESIZE(float, currHp, CurrHp);
	CC_SYNTHESIZE(float, force, Force);
	CC_SYNTHESIZE(float, armor, Armor);
	CC_SYNTHESIZE(float, hpPercentage, HpPercentage);
	CC_SYNTHESIZE(SoldierState, state, State);
    CC_SYNTHESIZE_READONLY(ProgressTimer*, hpBar, HpBar);
	CC_SYNTHESIZE(Point, location, Location);
	Sprite* baseSprite;
	virtual void runToLocation(Point point);
	virtual bool init();
	BaseMonster* nearestMonster;  
	virtual void updateSoldier(int level){};
protected:
	virtual void createAndSetHpBar();
	Sprite* hpBgSprite;
	virtual void lookingForMonsters(float dt);
	
	virtual void checkNearestMonster();
	virtual void attack();
	virtual void update(float dt){};
	
	virtual void runToDestination(Point destination,bool isAttacking){};
	SoldierState lastState;
	virtual void stopSoldierAnimation();
	void checkDirection(Point point);
	//falseÓÒ±ßtrue×ó±ß
	virtual bool checkDirectionForMonster();
	float caculateTime(Point point);
	virtual void runToMonster();
	virtual void attackMonster(float dt){};
	int attackCount;
};

#endif