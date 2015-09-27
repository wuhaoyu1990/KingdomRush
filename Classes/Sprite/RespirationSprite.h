#ifndef _RESPIRATION_SPRITE_H_
#define _RESPIRATION_SPRITE_H_

#include "cocos2d.h"

USING_NS_CC;

class RespirationSprite : public Sprite
{
public:
	virtual bool RespirationInit(const std::string SpriteFrameName);
    CREATE_FUNC(RespirationSprite);
	static RespirationSprite* createRespirationSprite(const std::string SpriteFrameName);
private:
	void startRespiration(float dt);
};

#endif