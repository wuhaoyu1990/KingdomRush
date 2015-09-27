#ifndef _SCORPION_H_
#define _SCORPION_H_

#include "BaseMonster.h"
#include "cocos2d.h"

USING_NS_CC;

class Scorpion : public BaseMonster
{
public:
   virtual bool init() override;
    
   static Scorpion* createMonster(std::vector<Point> points);
};

#endif