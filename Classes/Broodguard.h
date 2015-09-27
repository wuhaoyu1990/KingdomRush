#ifndef _BROODGUARD_H_
#define _BROODGUARD_H_

#include "BaseMonster.h"
#include "cocos2d.h"
USING_NS_CC;

class Broodguard : public BaseMonster
{
public:
	virtual bool init() override;    
	static Broodguard* createMonster(std::vector<Point> points);
};

#endif