#ifndef _WASPQUEEN_H_
#define _WASPQUEEN_H_

#include "BaseMonster.h"
#include "cocos2d.h"
USING_NS_CC;

class WaspQueen : public BaseMonster
{
public:
	virtual bool init() override;    
	static WaspQueen* createMonster(std::vector<Point> points, int hp ,int value);
	static WaspQueen* createMonster(std::vector<Point> points);
	void refrozen(float dt);
	void frozen();
};

#endif