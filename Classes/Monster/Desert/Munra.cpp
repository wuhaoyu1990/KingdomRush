#include "Munra.h"

USING_NS_CC;

Munra* Munra::createMonster(std::vector<Point> points)
{
    auto monster = new Munra();
    if (monster && monster->init())
    {

        monster->setPointsVector(points);
		monster->setMaxHp(800);
		monster->setCurrHp(800);
		monster->setForce(10);
		monster->setMoney(150);
		monster->setRunSpeed(20);
		monster->setArmor(10);
		monster->setAttackBySoldier(true);
        monster->runNextPoint();       
        monster->autorelease();
        return monster;
    }
    CC_SAFE_DELETE(monster);
    return NULL;
}

bool Munra::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setMonsterType(MUNRA);
	setName("Munra_");
	baseSprite = Sprite::createWithSpriteFrameName("desertMunra_0001.png");
	addChild(baseSprite);
	createAndSetHpBar();
	setState(stateNone);
	blood = Sprite::createWithSpriteFrameName("fx_blood_splat_red_0001.png");
	blood->setPosition(Point(baseSprite->getContentSize().width/2,baseSprite->getContentSize().height/2));
	baseSprite->addChild(blood);
	blood->setVisible(false);
	lastState = stateNone;
	scheduleUpdate();
	setListener();
	return true;
}