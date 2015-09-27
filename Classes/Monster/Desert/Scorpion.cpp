#include "Scorpion.h"

USING_NS_CC;


Scorpion* Scorpion::createMonster(std::vector<Point> points)
{
    auto monster = new Scorpion();
    if (monster && monster->init())
    {

        monster->setPointsVector(points);
		monster->setMaxHp(400);
		monster->setCurrHp(400);
		monster->setMoney(100);
		monster->setRunSpeed(40);
		monster->setArmor(20);
		monster->setForce(20);
		monster->setAttackBySoldier(true);
        monster->runNextPoint();       
        monster->autorelease();
        return monster;
    }
    CC_SAFE_DELETE(monster);
    return NULL;
}

bool Scorpion::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setMonsterType(SCORPION);
	setName("Scorpion_");
	baseSprite = Sprite::createWithSpriteFrameName("scorpion_0001.png");
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