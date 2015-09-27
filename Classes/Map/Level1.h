#ifndef _LEVEL_1_H_
#define _LEVEL_1_H_

#include "BaseMap.h"
#include "cocos2d.h"

USING_NS_CC;

class Level1 : public BaseMap
{
public:
	Level1();
	~Level1();
	static Level1* createGame(int difficulty);
    virtual bool initWithDifficulty(int difficulty);
private:
	//添加不同关卡的特殊装饰物
	void addOrnament();
	void onExit();
	//void addMonsters(float dt);
	void addTerrains();
};

#endif