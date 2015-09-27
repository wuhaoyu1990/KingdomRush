#include "Freeze.h"
#include "GameManager.h"

bool Freeze::init()
{
	if(!Sprite::init()){
		return false;
	}
	sprite = Sprite::createWithSpriteFrameName("small_freeze_bomb.png");
	addChild(sprite);
	return true;
}

void Freeze::shoot(Point point)
{
	setPosition(point);

	sprite->runAction(Spawn::create(
		Sequence::create(MoveBy::create(0.5f,Point(0,50)),
			MoveBy::create(0.5f,Point(0,-50)),
			Animate::create(AnimationCache::getInstance()->getAnimation("freeze_explosion")),
			CallFuncN::create(CC_CALLBACK_0(Freeze::removeBullet, this)),NULL),
				RotateBy::create(1.0f,1080.0f),NULL));
}

void Freeze::removeBullet()
{
	auto instance = GameManager::getInstance();
    auto monsterVector = instance->monsterVector;

	for(int i = 0; i < monsterVector.size(); i++)
	{
		auto monster = monsterVector.at(i);
		double distance = (this->getPosition()).getDistance(monster->baseSprite->getPosition());

		if (monster!=NULL && distance < 100)
			monster->frozen();
	}
	this->removeFromParent();
}