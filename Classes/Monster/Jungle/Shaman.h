#ifndef _SHAMAN_H_
#define _SHAMAN_H_

#include "BaseMonster.h"
#include "cocos2d.h"
USING_NS_CC;

class Shaman : public BaseMonster
{
public:
	virtual bool init() override;    
	static Shaman* createMonster(std::vector<Point> points);
};

#endif