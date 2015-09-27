#include "Blazefang.h"

USING_NS_CC;


Blazefang* Blazefang::createMonster(std::vector<Point> points)
{
    auto monster = new Blazefang();
    if (monster && monster->init())
    {

        monster->setPointsVector(points);
		monster->setMaxHp(200);
		monster->setCurrHp(200);
		monster->setMoney(10);
		monster->setForce(15);
		monster->setArmor(10);
		monster->setAttackBySoldier(true);
		monster->setRunSpeed(40);
        monster->runNextPoint();       
        monster->autorelease();
        return monster;
    }
    CC_SAFE_DELETE(monster);
    return NULL;
}

bool Blazefang::init()
{
	if (!BaseMonster::init())
	{
		return false;
	}
	setMonsterType(BLAZEFANG);
	setName("Blazefang_");
	baseSprite = Sprite::createWithSpriteFrameName("SaurianBlazefang_0001.png");
	addChild(baseSprite);
	createAndSetHpBar();
	blood = Sprite::createWithSpriteFrameName("fx_blood_splat_green_0001.png");
	blood->setPosition(Point(baseSprite->getContentSize().width/2,baseSprite->getContentSize().height/2));
	baseSprite->addChild(blood);
	blood->setVisible(false);
	lastState = stateNone;
	scheduleUpdate();
	setListener();
	return true;
}