#include "ReinforceSoldier1.h"
#include "GameManager.h"

ReinforceSoldier1* ReinforceSoldier1::createReinforceSoldier(Point point)
{
    auto reinforceSoldier = new ReinforceSoldier1();
    if (reinforceSoldier && reinforceSoldier->init())
    {
        reinforceSoldier->setLocation(point);
		reinforceSoldier->setMaxHp(80);
		reinforceSoldier->setCurrHp(80); 
		reinforceSoldier->setForce(10);
		reinforceSoldier->setState(SoldierStateNone);
		reinforceSoldier->birth(point);
        reinforceSoldier->autorelease();
        return reinforceSoldier;
    }
	CC_SAFE_DELETE(reinforceSoldier);
    return NULL;
}

void ReinforceSoldier1::birth(Point point)
{
	setPosition(point);
	scheduleUpdate();
	schedule(schedule_selector(ReinforceSoldier1::lookingForMonsters), 1.0f,-1,caculateTime(point));
}

bool ReinforceSoldier1::init()
{
	if(!BaseSoldier::init()){
		return false;
	}
	baseSprite = Sprite::createWithSpriteFrameName("reinforce_C0_0001.png");
	addChild(baseSprite);
	createAndSetHpBar();
	lastState = SoldierStateNone;

	return true;
}

void ReinforceSoldier1::attackMonster(float dt)
{
	if(nearestMonster!=NULL && nearestMonster->getCurrHp()>0){
		if (!checkDirectionForMonster()){
			nearestMonster->setState(stateAttackLeft);
		}else{
			nearestMonster->setState(stateAttackRight);
		}
		setState(SoldierStateHit);
		auto monsterCurrHp = nearestMonster->getCurrHp();
		auto SoldierHp = this->getCurrHp();

		monsterCurrHp =  monsterCurrHp - this->getForce();
		if(nearestMonster->getState()!=stateFrozen)
			SoldierHp =  SoldierHp - nearestMonster->getForce();

		if(monsterCurrHp <= 0){
			monsterCurrHp = 0;
		}
		if(SoldierHp <= 0){
			SoldierHp = 0;
		}
		nearestMonster->setCurrHp( monsterCurrHp );
		this->setCurrHp(SoldierHp);

		nearestMonster->getHpBar()->setPercentage((monsterCurrHp/nearestMonster->getMaxHp())*100);
		this->getHpBar()->setPercentage((SoldierHp/this->getMaxHp())*100);

		if(monsterCurrHp == 0){
			unschedule(schedule_selector(ReinforceSoldier1::attackMonster));
			//GameManager::getInstance()->monsterVector.eraseObject(nearestMonster);
			nearestMonster->death();
			if(this->getCurrHp()>0)
				runToLocation(location);
		}
		if(SoldierHp == 0){
			lastState = SoldierStateDeath;
			setState(SoldierStateDeath);
			unscheduleAllCallbacks();
			stopAllActions();
			baseSprite->stopAllActions();
			hpBgSprite->setVisible(false);
			if(nearestMonster != NULL && nearestMonster->getCurrHp()>0){
				nearestMonster->restartWalking();
				nearestMonster->setIsAttacking(false);
			}
			baseSprite->runAction(Sequence::create(
				FadeOut::create(1.0f)
				,CallFuncN::create(CC_CALLBACK_0(ReinforceSoldier1::removeFromParent, this))
				,NULL));
		}
	}else{
		unschedule(schedule_selector(ReinforceSoldier1::attackMonster));
		if(this->getCurrHp()>0)
				runToLocation(location);
	}
}

void ReinforceSoldier1::update(float dt)
{
	//Èô×´Ì¬¸üÐÂ
	if(lastState!=getState()){
		//¸ù¾Ý×´Ì¬ÅÐ¶Ï
		switch (getState())
		{
		case(SoldierStateRun):{
			lastState = SoldierStateRun;
			//Í£Ö¹Ö®Ç°¶¯»­
			stopSoldierAnimation();
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("reinforce1_run")));
			action->setTag(SoldierStateRun);
			baseSprite->runAction(action);}
			break;
		case(SoldierStateHit):{
			lastState = SoldierStateHit;
			stopSoldierAnimation();
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("reinforce1_attack")));
			action->setTag(SoldierStateHit);
			baseSprite->runAction(action);}
			break;
		case(SoldierStateWait):{
			lastState = SoldierStateWait;
			stopSoldierAnimation();
			baseSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("reinforce_C0_0001.png"));}
			break;
		}
	}
}

void ReinforceSoldier1::checkNearestMonster()
{
	auto instance = GameManager::getInstance();
    auto monsterVector = instance->monsterVector;
    nearestMonster = NULL;
	for(int i = 0; i < monsterVector.size(); i++)
	{
		auto monster = monsterVector.at(i);
		double distance = (this->getPosition()).getDistance(monster->baseSprite->getPosition());

		if (monster->getAttackBySoldier() && distance < 50 && (!monster->getIsAttacking())) {
            nearestMonster = monster;
			nearestMonster->stopWalking();
			nearestMonster->setIsAttacking(true);
			break;
		}
	}
}

void ReinforceSoldier1::runToMonster()
{
	Point destination;
	if (!checkDirectionForMonster()){//¹ÖÔÚÓÒ±ß
		destination.x = nearestMonster->baseSprite->getPositionX() + nearestMonster->baseSprite->getContentSize().width/2 - this->baseSprite->getContentSize().width/2;
		destination.y = nearestMonster->baseSprite->getPositionY() + this->baseSprite->getContentSize().height/4;
	}else{//×ó±ß
		destination.x = nearestMonster->baseSprite->getPositionX() - nearestMonster->baseSprite->getContentSize().width/2 + this->baseSprite->getContentSize().width/2;
		destination.y = nearestMonster->baseSprite->getPositionY() + this->baseSprite->getContentSize().height/4;
	}
	setState(SoldierStateRun);
	runAction(Sequence::create(MoveTo::create(caculateTime(destination),destination) , NULL));
	schedule(schedule_selector(ReinforceSoldier1::attackMonster), 1.0f,-1,caculateTime(destination));
}

bool ReinforceSoldier1::checkDirectionForMonster()
{
	if((nearestMonster->baseSprite->getPositionX() - this->getPositionX())>0){
		baseSprite->setFlippedX(false);
		return false;
	}else{
		baseSprite->setFlippedX(true);
		return true;
	}
}