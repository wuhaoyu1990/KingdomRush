#include "Nightscale.h"

USING_NS_CC;


Nightscale* Nightscale::createMonster(std::vector<Point> points)
{
    auto monster = new Nightscale();
    if (monster && monster->init())
    {

        monster->setPointsVector(points);
		monster->setMaxHp(500);
		monster->setCurrHp(500);
		monster->setMoney(20);
		monster->setForce(45);
		monster->setArmor(10);
		monster->setAttackBySoldier(true);
		monster->setRunSpeed(60);
        monster->runNextPoint();       
        monster->autorelease();
        return monster;
    }
    CC_SAFE_DELETE(monster);
    return NULL;
}

bool Nightscale::init()
{
	if (!BaseMonster::init())
	{
		return false;
	}
	setMonsterType(NIGHTSCALE);
	setName("Nightscale_");
	baseSprite = Sprite::createWithSpriteFrameName("SaurianNightscale_0001.png");
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