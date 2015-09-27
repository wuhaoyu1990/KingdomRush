#include "Hunter.h"

USING_NS_CC;


Hunter* Hunter::createMonster(std::vector<Point> points)
{
    auto monster = new Hunter();
    if (monster && monster->init())
    {

        monster->setPointsVector(points);
		monster->setMaxHp(120);
		monster->setCurrHp(120);
		monster->setMoney(20);
		monster->setForce(15);
		monster->setArmor(0);
		monster->setAttackBySoldier(true);
		monster->setRunSpeed(40);
        monster->runNextPoint();       
        monster->autorelease();
        return monster;
    }
    CC_SAFE_DELETE(monster);
    return NULL;
}

bool Hunter::init()
{
	if (!BaseMonster::init())
	{
		return false;
	}
	setMonsterType(HUNTER);
	setName("Hunter_");
	baseSprite = Sprite::createWithSpriteFrameName("CanibalHunter_0001.png");
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