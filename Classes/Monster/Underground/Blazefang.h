#ifndef _BLAZEFANG_H_
#define _BLAZEFANG_H_

#include "BaseMonster.h"
#include "cocos2d.h"
USING_NS_CC;

class Blazefang : public BaseMonster
{
public:
	virtual bool init() override;    
	static Blazefang* createMonster(std::vector<Point> points);
};

#endif