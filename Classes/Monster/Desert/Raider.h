#ifndef _RADIER_H_
#define _RADIER_H_

#include "BaseMonster.h"
#include "cocos2d.h"

USING_NS_CC;

class Raider : public BaseMonster
{
public:
   virtual bool init() override;
    
   static Raider* createMonster(std::vector<Point> points);
};

#endif