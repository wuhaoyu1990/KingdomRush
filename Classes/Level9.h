#ifndef _LEVEL_9_H_
#define _LEVEL_9_H_

#include "BaseMap.h"
#include "cocos2d.h"

USING_NS_CC;

class Level9 : public BaseMap
{
public:
	Level9();
	~Level9();
	static Level9* createGame(int difficulty);
    virtual bool initWithDifficulty(int difficulty);

private:
	void addOrnament();
	void onExit();
	void addTerrains();
};

#endif