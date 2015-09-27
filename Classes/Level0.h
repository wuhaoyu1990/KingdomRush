#ifndef _LEVEL_0_H_
#define _LEVEL_0_H_

#include "BaseMap.h"
#include "cocos2d.h"

USING_NS_CC;

class Level0 : public BaseMap
{
public:
	Level0();
	~Level0();
	static Level0* createGame(int difficulty);
    virtual bool initWithDifficulty(int difficulty);
	void startAfterStory();
private:
	void onEnterTransitionDidFinish();
	void addOrnament();
	void onExit();
	void addTerrains();
	LayerColor* color;
};

#endif