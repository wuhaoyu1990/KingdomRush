#ifndef _EFREETI_H_
#define _EFREETI_H_

#include "BaseMonster.h"
#include "cocos2d.h"
USING_NS_CC;

class Efreeti : public BaseMonster
{
public:
	virtual bool init() override;    
	static Efreeti* createMonster(std::vector<Point> points,int pointCounter);
	void getHurt();
	void death();
	void explosion();
};

#endif