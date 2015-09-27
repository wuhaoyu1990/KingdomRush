#ifndef _LEVEL_3_H_
#define _LEVEL_3_H_

#include "BaseMap.h"
#include "cocos2d.h"

USING_NS_CC;

class Level3 : public BaseMap
{
public:
	Level3();
	~Level3();
	static Level3* createGame(int difficulty);
    virtual bool initWithDifficulty(int difficulty);
private:
	//void addMonsters(float dt);
	void addOrnament();
	void onExit();
	void addTerrains();
};

#endif