#include "Quetzal.h"

USING_NS_CC;


Quetzal* Quetzal::createMonster(std::vector<Point> points)
{
    auto monster = new Quetzal();
    if (monster && monster->init())
    {

        monster->setPointsVector(points);
		monster->setMaxHp(500);
		monster->setCurrHp(500);
		monster->setMoney(20);
		monster->setForce(45);
		monster->setArmor(10);
		monster->setAttackBySoldier(false);
		monster->setRunSpeed(60);
        monster->runNextPoint();       
        monster->autorelease();
        return monster;
    }
    CC_SAFE_DELETE(monster);
    return NULL;
}

bool Quetzal::init()
{
	if (!BaseMonster::init())
	{
		return false;
	}
	setMonsterType(QUETZAL);
	setName("Quetzal_");
	baseSprite = Sprite::createWithSpriteFrameName("SaurianQuetzal_0001.png");
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