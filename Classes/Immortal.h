#ifndef _IMMORTAL_H_
#define _IMMORTAL_H_

#include "BaseMonster.h"
#include "cocos2d.h"

USING_NS_CC;

class Immortal : public BaseMonster
{
public:
   virtual bool init() override;
    
   static Immortal* createMonster(std::vector<Point> points);
   void death();
   void explosion();
   Point nextPoint();
};

#endif