#ifndef _MYRMIDON_H_
#define _MYRMIDON_H_

#include "BaseMonster.h"
#include "cocos2d.h"
USING_NS_CC;

class Myrmidon : public BaseMonster
{
public:
	virtual bool init() override;    
	static Myrmidon* createMonster(std::vector<Point> points);
};

#endif