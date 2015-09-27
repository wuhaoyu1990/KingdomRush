#include "Lava.h"

bool Lava::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	auto lava = Sprite::createWithSpriteFrameName("EarthquakeTower_Lava.png");
	lava->setScale(2.0f);
	lava->setPosition(Point(0,-20));
	addChild(lava);
	this->setVisible(false);
	return true;
}

void Lava::shoot()
{
	this->setVisible(true);
	runAction(Sequence::create(FadeOut::create(1.0f),
		CallFuncN::create(CC_CALLBACK_0(Lava::setVisible,this,false)),
		NULL));
}