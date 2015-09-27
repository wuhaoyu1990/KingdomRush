#include "Shield.h"

USING_NS_CC;


Shield* Shield::createMonster(std::vector<Point> points)
{
    auto monster = new Shield();
    if (monster && monster->init())
    {

        monster->setPointsVector(points);
		monster->setMaxHp(480);
		monster->setCurrHp(480);
		monster->setMoney(50);
		monster->setForce(30);
		monster->setArmor(0);
		monster->setAttackBySoldier(true);
		monster->setRunSpeed(35);
        monster->runNextPoint();       
        monster->autorelease();
        return monster;
    }
    CC_SAFE_DELETE(monster);
    return NULL;
}

bool Shield::init()
{
	if (!BaseMonster::init())
	{
		return false;
	}
	setMonsterType(SHIELD);
	setName("Shield_");
	baseSprite = Sprite::createWithSpriteFrameName("CanibalShamanShield_0001.png");
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