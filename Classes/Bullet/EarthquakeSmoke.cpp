#include "EarthquakeSmoke.h"


bool EarthquakeSmoke::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	auto smoke0_0 = Sprite::createWithSpriteFrameName("EarthquakeTower_HitSmoke_0015.png");
	smoke0_0->setPosition(Point(0,90));
	addChild(smoke0_0);

	auto smoke1_0 = Sprite::createWithSpriteFrameName("EarthquakeTower_HitSmoke_0015.png");
	smoke1_0->setPosition(Point(60,60));
	addChild(smoke1_0);

	auto smoke2_0 = Sprite::createWithSpriteFrameName("EarthquakeTower_HitSmoke_0015.png");
	smoke2_0->setPosition(Point(120,30));
	addChild(smoke2_0);

	auto smoke3_0 = Sprite::createWithSpriteFrameName("EarthquakeTower_HitSmoke_0015.png");
	smoke3_0->setPosition(Point(120,0));
	addChild(smoke3_0);

	auto smoke4_0 = Sprite::createWithSpriteFrameName("EarthquakeTower_HitSmoke_0015.png");
	smoke4_0->setPosition(Point(120,-30));
	addChild(smoke4_0);

	auto smoke5_0 = Sprite::createWithSpriteFrameName("EarthquakeTower_HitSmoke_0015.png");
	smoke5_0->setPosition(Point(60,-60));
	addChild(smoke5_0);

	auto smoke6_0 = Sprite::createWithSpriteFrameName("EarthquakeTower_HitSmoke_0015.png");
	smoke6_0->setPosition(Point(0,-90));
	addChild(smoke6_0);

	auto smoke7_0 = Sprite::createWithSpriteFrameName("EarthquakeTower_HitSmoke_0015.png");
	smoke7_0->setPosition(Point(-60,60));
	addChild(smoke7_0);

	auto smoke8_0 = Sprite::createWithSpriteFrameName("EarthquakeTower_HitSmoke_0015.png");
	smoke8_0->setPosition(Point(-120,30));
	addChild(smoke8_0);

	auto smoke9_0 = Sprite::createWithSpriteFrameName("EarthquakeTower_HitSmoke_0015.png");
	smoke9_0->setPosition(Point(-120,0));
	addChild(smoke9_0);

	auto smoke10_0 = Sprite::createWithSpriteFrameName("EarthquakeTower_HitSmoke_0015.png");
	smoke10_0->setPosition(Point(-120,-30));
	addChild(smoke10_0);

	auto smoke11_0 = Sprite::createWithSpriteFrameName("EarthquakeTower_HitSmoke_0015.png");
	smoke11_0->setPosition(Point(-60,-60));
	addChild(smoke11_0);

	smokes.pushBack(smoke0_0);
	smokes.pushBack(smoke1_0);
	smokes.pushBack(smoke2_0);
	smokes.pushBack(smoke3_0);
	smokes.pushBack(smoke4_0);
	smokes.pushBack(smoke5_0);
	smokes.pushBack(smoke6_0);
	smokes.pushBack(smoke7_0);
	smokes.pushBack(smoke8_0);
	smokes.pushBack(smoke9_0);
	smokes.pushBack(smoke10_0);
	smokes.pushBack(smoke11_0);
	return true;
}

void EarthquakeSmoke::shoot()
{
	for(int i = 0;i<smokes.size();i++){
		smokes.at(i)->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("EarthquakeTower_hitsmoke")));
	}
}