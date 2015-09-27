#include "Executioner.h"

USING_NS_CC;

Executioner* Executioner::createMonster(std::vector<Point> points)
{
    auto monster = new Executioner();
    if (monster && monster->init())
    {
        monster->setPointsVector(points);
		monster->setMaxHp(4000);
		monster->setCurrHp(4000);
		monster->setMoney(800);
		monster->setRunSpeed(15);
        monster->runNextPoint();
		monster->setArmor(20);
        monster->autorelease();
        return monster;
    }
    CC_SAFE_DELETE(monster);
    return NULL;
}

bool Executioner::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setMonsterType(EXECUTIONER);
	setName("Executioner_");
	baseSprite = Sprite::createWithSpriteFrameName("desertExecutioner_0001.png");
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