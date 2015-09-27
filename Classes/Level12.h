#ifndef _LEVEL_12_H_
#define _LEVEL_12_H_

#include "BaseMap.h"
#include "cocos2d.h"

USING_NS_CC;

class Level12 : public BaseMap
{
public:
	Level12();
	~Level12();
	static Level12* createGame(int difficulty);
    virtual bool initWithDifficulty(int difficulty);

private:
	void addOrnament();
	void onExit();
	void addTerrains();
};

#endif