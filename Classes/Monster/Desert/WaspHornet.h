#ifndef _WASPHORNET_H_
#define _WASPHORNET_H_

#include "BaseMonster.h"
#include "cocos2d.h"
USING_NS_CC;

class WaspHornet : public BaseMonster
{
public:
	virtual bool init() override;    
	static WaspHornet* createMonster(std::vector<Point> points, int hp ,int value);
	static WaspHornet* createMonster(std::vector<Point> points);
	void frozen();
	void refrozen(float dt);
};

#endif