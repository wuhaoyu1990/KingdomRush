#ifndef _FALLEN_H_
#define _FALLEN_H_

#include "BaseMonster.h"
#include "cocos2d.h"

USING_NS_CC;

class Fallen : public BaseMonster
{
public:
   virtual bool init() override;
    
   static Fallen* createMonster(std::vector<Point> points);
   static Fallen* createMonster(std::vector<Point> points,Point birthLocation,int pointCounter);
   void birth(Point birthLocation,int pointCounter);
};

#endif