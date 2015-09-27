#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "cocos2d.h"
USING_NS_CC;

class Circle : public Sprite
{
public:
    virtual bool init();
    CREATE_FUNC(Circle);
};

#endif