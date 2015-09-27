#ifndef _BASE_TOWER_
#define _BASE_TOWER_

#include "cocos2d.h"
#include "Circle.h"
#include "Terrain.h"
#include "BaseMonster.h"
#include "SoundManager.h"

USING_NS_CC;

typedef enum{
    ARCHER_1 = 0, //级箭塔
    ARCHER_2, //2级箭塔
    ARCHER_3, //3级箭塔
	COSSBOW, //弩塔
	TOTEMTOWER, //野人
	ARTILLERY_1,//1级炮塔
	ARTILLERY_2,//2级炮塔
	ARTILLERY_3,//3级炮塔
	EARTHQUAKE, //地震
	MECHS, //机器
	BARAACKS_1,//1级兵营
	BARAACKS_2,//2级兵营
	BARAACKS_3,//3级兵营
	ASSASSIN,//盗贼
	TEMPLAR,//战士
	MAGE_1,//1级法师塔
	MAGE_2,//2级法师塔
	MAGE_3,//3级法师塔
	ARCHMAGE,//龙卷风
	NEC,//死灵法
}TowerType;

class BaseTower: public Sprite
{
public:
   BaseTower();
   ~BaseTower();
   virtual void updateTower(){};
   virtual void sellTower();
   virtual void removeTower();
   virtual bool init();
   CC_SYNTHESIZE(TowerType, towerType, TowerType); 
   CC_SYNTHESIZE(Terrain*, myTerrain, MyTerrain); 
   CC_SYNTHESIZE(std::string, towerName, TowerName); 
   CC_SYNTHESIZE(int, level, Level);
   CC_SYNTHESIZE(float, scope, Scope);
   CC_SYNTHESIZE(float, nextScope, NextScope);
   CC_SYNTHESIZE(float, rate, Rate);
   CC_SYNTHESIZE(int, force, Force);
   CC_SYNTHESIZE(int, updateMoney, UpdateMoney);
   CC_SYNTHESIZE(int, buildMoney, BuildMoney);
   virtual void showTowerInfo();
   bool isUpdateMenuShown;
   virtual void update1(){};
   virtual void update2(){};
   virtual void setRallyPoint(Point point){};
protected:   
   virtual void checkNearestMonster();
   BaseMonster* nearestMonster;  
   bool onTouchBegan(Touch *touch, Event *event);
   void onTouchEnded(Touch* touch, Event* event);
   virtual void showUpdateMenu(){};
   virtual void hideUpdateMenu();
   Sprite* terrain;
   void setListener();

};

#endif