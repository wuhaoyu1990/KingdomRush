#include "Gorilla.h"

USING_NS_CC;


Gorilla* Gorilla::createMonster(std::vector<Point> points)
{
    auto monster = new Gorilla();
    if (monster && monster->init())
    {

        monster->setPointsVector(points);
		monster->setMaxHp(2500);
		monster->setCurrHp(2500);
		monster->setMoney(500);
		monster->setForce(60);
		monster->setArmor(0);
		monster->setAttackBySoldier(true);
		monster->setRunSpeed(30);
        monster->runNextPoint();       
        monster->autorelease();
        return monster;
    }
    CC_SAFE_DELETE(monster);
    return NULL;
}

bool Gorilla::init()
{
	if (!BaseMonster::init())
	{
		return false;
	}
	setMonsterType(GORILLA);
	setName("Gorilla_");
	baseSprite = Sprite::createWithSpriteFrameName("Gorilla_0001.png");
	addChild(baseSprite);
	createAndSetHpBar();
	blood = Sprite::createWithSpriteFrameName("fx_blood_splat_red_0001.png");
	blood->setPosition(Point(baseSprite->getContentSize().width/2,baseSprite->getContentSize().height/2));
	baseSprite->addChild(blood);
	blood->setVisible(false);
	lastState = stateNone;
	scheduleUpdate();
	setListener();
	return true;
}