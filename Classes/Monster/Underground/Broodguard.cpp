#include "Broodguard.h"

USING_NS_CC;


Broodguard* Broodguard::createMonster(std::vector<Point> points)
{
    auto monster = new Broodguard();
    if (monster && monster->init())
    {

        monster->setPointsVector(points);
		monster->setMaxHp(400);
		monster->setCurrHp(400);
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

bool Broodguard::init()
{
	if (!BaseMonster::init())
	{
		return false;
	}
	setMonsterType(BROODGUARD);
	setName("Broodguard_");
	baseSprite = Sprite::createWithSpriteFrameName("SaurianBroodguard_0001.png");
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