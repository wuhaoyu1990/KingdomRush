#include "WaspHornet.h"

USING_NS_CC;

WaspHornet* WaspHornet::createMonster(std::vector<Point> points)
{
    auto monster = new WaspHornet();
    if (monster && monster->init())
    {

        monster->setPointsVector(points);
		monster->setMaxHp(70);
		monster->setCurrHp(70);
		monster->setRunSpeed(50);
        monster->runNextPoint(); 
		monster->setArmor(10);
		monster->setAttackBySoldier(false);
		monster->setMoney(30);
        monster->autorelease();
        return monster;
    }
    CC_SAFE_DELETE(monster);
    return NULL;
}

void WaspHornet::frozen()
{
	if(getState()!=stateFrozen){
		tempState = lastState;
		setState(stateFrozen);
		baseSprite->stopAllActions();
		ice = Sprite::createWithSpriteFrameName("freeze_creepFlying_0009.png");
		ice->setPosition(Point(baseSprite->getContentSize().width/2,baseSprite->getContentSize().height/4));
		baseSprite->addChild(ice);
		ice->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("freeze_creepFlying")));
		scheduleOnce(schedule_selector(WaspHornet::refrozen),8.0f);
	}else{
		unschedule(schedule_selector(WaspHornet::refrozen));
		scheduleOnce(schedule_selector(WaspHornet::refrozen),8.0f);
		ice->stopAllActions();
		ice->removeFromParent();
		ice = Sprite::createWithSpriteFrameName("freeze_creepFlying_0009.png");
		ice->setPosition(Point(baseSprite->getContentSize().width/2,baseSprite->getContentSize().height/4));
		baseSprite->addChild(ice);
		ice->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("freeze_creepFlying")));
	}
}

void WaspHornet::refrozen(float dt)
{
	ice->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("refreeze_creep"))
										,CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, ice))
										,CallFuncN::create(CC_CALLBACK_0(WaspHornet::restartWalking, this))
                                       , NULL));
}

bool WaspHornet::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setMonsterType(WASPHORNET);
	setName("WaspHornet_");
	baseSprite = Sprite::createWithSpriteFrameName("wasp_hornet_0001.png");
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