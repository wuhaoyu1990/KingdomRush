#ifndef _THUG_H_
#define _THUG_H_

#include "BaseMonster.h"
#include "cocos2d.h"
USING_NS_CC;

class Thug : public BaseMonster
{
public:
	virtual bool init() override;    
	static Thug* createMonster(std::vector<Point> points, int hp ,int value);
	static Thug* createMonster(std::vector<Point> points);
};

#endif