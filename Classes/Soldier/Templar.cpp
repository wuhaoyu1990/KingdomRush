#include "Templar.h"
#include "GameManager.h"

Templar* Templar::createTemplar(Point point)
{
    auto templar = new Templar();
    if (templar && templar->initTemplar())
    {

        templar->setLocation(point);
		templar->setMaxHp(200);
		templar->setCurrHp(200); 
		templar->setForce(20);
		templar->setState(SoldierStateNone);
        templar->autorelease();
		templar->attackCount = 1;
        return templar;
    }
	CC_SAFE_DELETE(templar);
    return NULL;
}

void Templar::cheakState()
{
	if(nearestMonster!=NULL){
		scheduleUpdate();
		schedule(schedule_selector(Templar::attackMonster), 1.5f,-1,0);
	}else{
		runToLocation(getLocation());
	}
}

void Templar::update(float dt)
{
	//若状态更新
	if(lastState!=getState()){
		//根据状态判断
		switch (getState())
		{
		case(SoldierStateRun):{
			lastState = SoldierStateRun;
			//停止之前动画
			stopSoldierAnimation();
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("Templar_run")));
			action->setTag(SoldierStateRun);
			baseSprite->runAction(action);}
			break;
		case(SoldierStateHit):{
			lastState = SoldierStateHit;
			stopSoldierAnimation();
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("Templar_attack")));
			action->setTag(SoldierStateHit);
			baseSprite->runAction(action);}
			break;
		case(SoldierStateWait):{
			lastState = SoldierStateWait;
			stopSoldierAnimation();
			baseSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Templar_0001.png"));}
			break;
		case(SoldierStateSkill1):{//我砍
			lastState = SoldierStateSkill1;
			stopSoldierAnimation();
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("Templar_skill1")));
			action->setTag(SoldierStateSkill1);
			baseSprite->runAction(action);}
			break;
		case(SoldierStateSkill2):{//治疗
			lastState = SoldierStateSkill2;
			stopSoldierAnimation();
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("Templar_skill2")));
			action->setTag(SoldierStateSkill2);
			baseSprite->runAction(action);}
			break;
		}
	}
}

void Templar::createAndSetHpBar()
{
    hpBgSprite = Sprite::createWithSpriteFrameName("lifebar_bg_small.png");

    hpBgSprite->setPosition(Point(baseSprite->getContentSize().width / 2, baseSprite->getContentSize().height ));
    baseSprite->addChild(hpBgSprite);
    
	hpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("lifebar_small.png"));
	hpBar->setType(ProgressTimer::Type::BAR);
	hpBar->setMidpoint(Point(0, 0.5f));
	hpBar->setBarChangeRate(Point(1, 0));
	hpBar->setPercentage(100);
    hpBar->setPosition(Point(hpBgSprite->getContentSize().width / 2, hpBgSprite->getContentSize().height / 2 ));
    hpBgSprite->addChild(hpBar);
}

bool Templar::initTemplar()
{
	if (!BaseSoldier::init())
	{
		return false;
	}
	
	baseSprite = Sprite::createWithSpriteFrameName("Templar_0002.png");
	addChild(baseSprite);
	createAndSetHpBar();
	lastState = SoldierStateNone;
	return true;
}


void Templar::attackMonster(float dt)
{
	if(nearestMonster!=NULL && nearestMonster->getCurrHp()>0){
		if (!checkDirectionForMonster()){
			nearestMonster->setState(stateAttackLeft);
		}else{
			nearestMonster->setState(stateAttackRight);
		}
		auto monsterCurrHp = nearestMonster->getCurrHp();
		auto SoldierHp = this->getCurrHp();
		int i = 5 % attackCount;
		switch(i)
		{
		case(0):
			setState(SoldierStateSkill1);
			monsterCurrHp =  monsterCurrHp - this->getForce() - 30;
			if(nearestMonster->getState()!=stateFrozen)
				SoldierHp =  SoldierHp - nearestMonster->getForce();
			break;
		case(1):
			setState(SoldierStateHit);
			monsterCurrHp =  monsterCurrHp - this->getForce();
			if(nearestMonster->getState()!=stateFrozen)
				SoldierHp =  SoldierHp - nearestMonster->getForce();
			break;
		case(2):
			setState(SoldierStateSkill2);
			this->setCurrHp(this->getMaxHp());
			this->setHpPercentage(100);
			this->getHpBar()->setPercentage(100);
			break;
		}
		attackCount++;
		if(attackCount == 6)
			attackCount = 1;
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
		GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY + 5;
		if(monsterCurrHp == 0){
			unschedule(schedule_selector(Templar::attackMonster));
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
				Animate::create(AnimationCache::getInstance()->getAnimation("Templar_dead"))
				,FadeOut::create(1.0f)
				,NULL));	
		}
	}else{
		unschedule(schedule_selector(Templar::attackMonster));
		if(this->getCurrHp()>0)
			runToLocation(location);
	}

}