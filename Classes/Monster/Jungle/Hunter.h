#ifndef _HUNTER_H_
#define _HUNTER_H_

#include "BaseMonster.h"
#include "cocos2d.h"
USING_NS_CC;

class Hunter : public BaseMonster
{
public:
	virtual bool init() override;    
	static Hunter* createMonster(std::vector<Point> points);
};

#endif