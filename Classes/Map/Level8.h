#ifndef _LEVEL_8_H_
#define _LEVEL_8_H_

#include "BaseMap.h"
#include "cocos2d.h"

USING_NS_CC;

class Level8 : public BaseMap
{
public:
	Level8();
	~Level8();
	static Level8* createGame(int difficulty);
    virtual bool initWithDifficulty(int difficulty);

private:
	//void addMonsters(float dt);
	void addOrnament();
	void onExit();
	void addTerrains();
};

#endif