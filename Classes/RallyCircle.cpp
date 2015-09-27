#include "RallyCircle.h"

bool RallyCircle::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	auto circle_1 = Sprite::createWithSpriteFrameName("rally_circle.png");
	auto circle_2 = Sprite::createWithSpriteFrameName("rally_circle.png");
	auto circle_3 = Sprite::createWithSpriteFrameName("rally_circle.png");
	auto circle_4 = Sprite::createWithSpriteFrameName("rally_circle.png");
	circle_1->setAnchorPoint(Point(1,0));

	circle_1->setScaleX(1.25f);
	circle_2->setScaleX(1.25f);
	circle_3->setScaleX(1.25f);
	circle_4->setScaleX(1.25f);

	circle_2->setFlippedX(true);
	circle_2->setAnchorPoint(Point(0,0));
	circle_3->setFlippedX(true);
	circle_3->setFlippedY(true);
	circle_3->setAnchorPoint(Point(0,1));
	circle_4->setFlippedY(true);
	circle_4->setAnchorPoint(Point(1,1));
	addChild(circle_1);
	addChild(circle_2);
	addChild(circle_3);
	addChild(circle_4);
	return true;
}