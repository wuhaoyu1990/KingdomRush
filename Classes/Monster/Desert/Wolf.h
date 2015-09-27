#ifndef _WOLF_H_
#define _WOLF_H_

#include "BaseMonster.h"
#include "cocos2d.h"

USING_NS_CC;

class Wolf : public BaseMonster
{
public:
   virtual bool init() override;
   static Wolf* createMonster(std::vector<Point> points, int hp ,int value);
   static Wolf* createMonster(std::vector<Point> points);
};

#endif