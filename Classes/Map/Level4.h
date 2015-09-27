#ifndef _LEVEL_4_H_
#define _LEVEL_4_H_

#include "BaseMap.h"
#include "cocos2d.h"

USING_NS_CC;

class Level4 : public BaseMap
{
public:
	Level4();
	~Level4();
	static Level4* createGame(int difficulty);
    virtual bool initWithDifficulty(int difficulty);
 
private:
	//void addMonsters(float dt);
	void addOrnament();
	void onExit();
	void initAction();
	void treeCover();
	void addTerrains();
	Sprite* doorSprite;
	void waveEvent();
	Sprite* TreeSprite[4][3];
	Sprite* treeTerrains[4];
};

#endif