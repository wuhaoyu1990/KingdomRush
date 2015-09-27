#ifndef _MUNRA_H_
#define _MUNRA_H_

#include "BaseMonster.h"
#include "cocos2d.h"

USING_NS_CC;

class Munra : public BaseMonster
{
public:
   virtual bool init() override;
    
   static Munra* createMonster(std::vector<Point> points);
};

#endif