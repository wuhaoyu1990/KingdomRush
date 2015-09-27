#include "Efreeti.h"
#include "GameManager.h"
USING_NS_CC;


Efreeti* Efreeti::createMonster(std::vector<Point> points,int pointCounter)
{
    auto monster = new Efreeti();
    if (monster && monster->init())
    {

        monster->setPointsVector(points);
		monster->setMaxHp(100);
		monster->setCurrHp(100);
		monster->setMoney(20);
		monster->setForce(15);
		monster->setArmor(0);
		monster->setAttackBySoldier(true);
		monster->setAttackByTower(true);
		monster->setRunSpeed(50);
		monster->pointCounter = pointCounter + 10;
        monster->runNextPoint();       
        monster->autorelease();
        return monster;
    }
    CC_SAFE_DELETE(monster);
    return NULL;
}

bool Efreeti::init()
{
	if (!BaseMonster::init())
	{
		return false;
	}
	setMonsterType(EFREETI);
	setName("Efreeti_");
	baseSprite = Sprite::createWithSpriteFrameName("desertEfreeti_0001.png");
	addChild(baseSprite);
	createAndSetHpBar();
	lastState = stateNone;
	scheduleUpdate();
	setListener();
	return true;
}

void Efreeti::getHurt(){}

void Efreeti::death()
{
	if(GameManager::getInstance()->monsterVector.contains(this)){
		GameManager::getInstance()->monsterVector.eraseObject(this);
	}
	if(getState()!=stateDeath){
		setState(stateDeath);
		hpBgSprite->setVisible(false);
		baseSprite->stopAllActions();
		unscheduleUpdate();
		GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY + getMoney();
		baseSprite->runAction(Sequence::create(
			Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"death")),
			CallFuncN::create(CC_CALLBACK_0(BaseMonster::setVisible, this,false))
			,NULL));
	}
}

void Efreeti::explosion()
{
	death();
}