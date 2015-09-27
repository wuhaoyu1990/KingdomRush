#ifndef _PRIEST_H_
#define _PRIEST_H_

#include "BaseMonster.h"
#include "cocos2d.h"
USING_NS_CC;

class Priest : public BaseMonster
{
public:
	virtual bool init() override;    
	static Priest* createMonster(std::vector<Point> points);
};

#endif