#ifndef _LEVEL_5_H_
#define _LEVEL_5_H_

#include "BaseMap.h"
#include "cocos2d.h"

USING_NS_CC;

class Level5 : public BaseMap
{
public:
	Level5();
	~Level5();
	static Level5* createGame(int difficulty);
    virtual bool initWithDifficulty(int difficulty);

private:
	//void addMonsters(float dt);
	void addOrnament();
	void onExit();
	void addTerrains();
	Sprite* door;
	void waveEvent();
	void eyeEffect();
	void stonesEffect();
	void beforeBoss();
};

#endif