#include "RespirationSprite.h"

bool RespirationSprite::RespirationInit(const std::string SpriteFrameName)
{
	if (!Sprite::init())
	{
		return false;
	}
	addChild(Sprite::createWithSpriteFrameName(SpriteFrameName));
	schedule(schedule_selector(RespirationSprite::startRespiration),0.5f);
	return true;
}

void RespirationSprite::startRespiration(float dt)
{
	runAction(Sequence::create(ScaleTo::create(0.25f,1.2f,1.2f),ScaleTo::create(0.25f,1.0f,1.0f),NULL));
}

RespirationSprite* RespirationSprite::createRespirationSprite(const std::string SpriteFrameName)
{
	auto respirationSprite = new RespirationSprite();
 
	if (respirationSprite && respirationSprite->RespirationInit(SpriteFrameName))
    {
        respirationSprite->autorelease();
        return respirationSprite;
    }
    CC_SAFE_DELETE(respirationSprite);
    return NULL;
}