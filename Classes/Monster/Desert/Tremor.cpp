#include "Tremor.h"

USING_NS_CC;


Tremor* Tremor::createMonster(std::vector<Point> points)
{
    auto monster = new Tremor();
    if (monster && monster->init())
    {

        monster->setPointsVector(points);
		monster->setMaxHp(35);
		monster->setCurrHp(35);
		monster->setMoney(10);
		monster->setForce(4);
		monster->setArmor(0);
		monster->setForce(8);
		monster->setAttackByTower(false);
		monster->setAttackBySoldier(true);
		monster->setRunSpeed(50);
        monster->runNextPoint();       
        monster->autorelease();
        return monster;
    }
    CC_SAFE_DELETE(monster);
    return NULL;
}

bool Tremor::init()
{
	if (!BaseMonster::init())
	{
		return false;
	}
	setMonsterType(TREMOR);
	setName("Tremor_");
	baseSprite = Sprite::createWithSpriteFrameName("tremor_0001.png");
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

void Tremor::update(float dt)
{
	//Èô×´Ì¬¸üÐÂ
	if(lastState!=getState()){
		//¸ù¾Ý×´Ì¬ÅÐ¶Ï
		switch (getState())
		{
		case(stateWalkRight):{
			setAttackByTower(false);
			hpBgSprite->setVisible(false);
			lastState = stateWalkRight;
			//Í£Ö¹Ö®Ç°¶¯»­
			stopMonsterAnimation();
			baseSprite->setFlippedX(false);
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"runright")));
			action->setTag(stateWalkRight);
			baseSprite->runAction(action);}
			break;
		case(stateWalkLeft):{
			setAttackByTower(false);
			hpBgSprite->setVisible(false);
			lastState = stateWalkLeft;
			stopMonsterAnimation();
			baseSprite->setFlippedX(true);
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"runleft")));
			action->setTag(stateWalkLeft);
			baseSprite->runAction(action);}
			break;
		case(stateWalkUp):{
			setAttackByTower(false);
			hpBgSprite->setVisible(false);
			lastState = stateWalkUp;
			stopMonsterAnimation();
			baseSprite->setFlippedX(false);
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"runup")));
			action->setTag(stateWalkUp);
			baseSprite->runAction(action);}
			break;
		case(stateWalkDown):{
			setAttackByTower(false);
			lastState = stateWalkDown;
			hpBgSprite->setVisible(false);
			stopMonsterAnimation();
			baseSprite->setFlippedX(false);
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"rundown")));
			action->setTag(stateWalkDown);
			baseSprite->runAction(action);}
			break;
		case(stateAttackRight):{
			setAttackByTower(true);
			hpBgSprite->setVisible(true);
			//Ä¬ÈÏÏòÓÒ±ß¹¥»÷
			lastState = stateAttackRight;
			stopMonsterAnimation();
			baseSprite->setFlippedX(false);
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"attack")));
			action->setTag(stateAttackRight);
			baseSprite->runAction(action);}
			break;
		case(stateAttackLeft):{
			setAttackByTower(true);
			hpBgSprite->setVisible(true);
			lastState = stateAttackLeft;
			stopMonsterAnimation();
			baseSprite->setFlippedX(true);
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"attack")));
			action->setTag(stateAttackLeft);
			baseSprite->runAction(action);}
			break;
		}
	}
}

void Tremor::stopWalking()
{
	tempState = lastState;
	baseSprite->stopAllActions();
}

void Tremor::restartWalking()
{
	baseSprite->stopAllActions();
	setState(tempState);

	auto tempCurrPoint = baseSprite->getPosition();
	auto duration =  tempCurrPoint.getDistance(tempNextPoint) / getRunSpeed() ;
	baseSprite->runAction(Sequence::create(MoveTo::create(duration, tempNextPoint)
                                           , CallFuncN::create(CC_CALLBACK_0(Tremor::runNextPoint, this))
                                         , NULL));
}