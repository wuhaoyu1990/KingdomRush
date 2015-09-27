#ifndef _WINGRIDER_H_
#define _WINGRIDER_H_

#include "BaseMonster.h"
#include "cocos2d.h"
USING_NS_CC;

class WingRider : public BaseMonster
{
public:
	virtual bool init() override;    
	static WingRider* createMonster(std::vector<Point> points);
};

#endif