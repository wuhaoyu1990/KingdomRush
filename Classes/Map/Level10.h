#ifndef _LEVEL_10_H_
#define _LEVEL_10_H_

#include "BaseMap.h"
#include "cocos2d.h"

USING_NS_CC;

class Level10 : public BaseMap
{
public:
	Level10();
	~Level10();
	static Level10* createGame(int difficulty);
    virtual bool initWithDifficulty(int difficulty);

private:
	void addOrnament();
	void onExit();
	void addTerrains();
	Sprite* stageTower;
	void waveEvent();
};

#endif