#include "Assassin.h"
#include "GameManager.h"

Assassin* Assassin::createAssassin(Point point)
{
    auto assassin = new Assassin();
    if (assassin && assassin->initAssassin())
    {

        assassin->setLocation(point);
		assassin->setMaxHp(150);
		assassin->setCurrHp(150); 
		assassin->setForce(14);
		assassin->setState(SoldierStateNone);
        assassin->autorelease();
		assassin->attackCount = 0;
        return assassin;
    }
	CC_SAFE_DELETE(assassin);
    return NULL;
}

void Assassin::cheakState()
{
	if(nearestMonster!=NULL){
		scheduleUpdate();
		schedule(schedule_selector(Assassin::attackMonster), 1.0f,-1,0);
	}else{
		runToLocation(getLocation());
	}
}

void Assassin::update(float dt)
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
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("Assassin_run")));
			action->setTag(SoldierStateRun);
			baseSprite->runAction(action);}
			break;
		case(SoldierStateHit):{
			lastState = SoldierStateHit;
			stopSoldierAnimation();
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("Assassin_attack")));
			action->setTag(SoldierStateHit);
			baseSprite->runAction(action);}
			break;
		case(SoldierStateWait):{
			lastState = SoldierStateWait;
			stopSoldierAnimation();
			baseSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Soldier_Assassin_0001.png"));}
			break;
		case(SoldierStateSkill1):{//ÖÂÃüÒ»»÷
			lastState = SoldierStateSkill1;
			stopSoldierAnimation();
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("Assassin_skill1")));
			action->setTag(SoldierStateSkill1);
			baseSprite->runAction(action);}
			break;
		case(SoldierStateSkill2):{//ÉÁ±Ü
			lastState = SoldierStateSkill2;
			stopSoldierAnimation();
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("Assassin_skill2")));
			action->setTag(SoldierStateSkill2);
			baseSprite->runAction(action);}
			break;
		}
	}
}

void Assassin::createAndSetHpBar()
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

bool Assassin::initAssassin()
{
	if (!BaseSoldier::init())
	{
		return false;
	}
	
	baseSprite = Sprite::createWithSpriteFrameName("Soldier_Assassin_0001.png");
	addChild(baseSprite);
	createAndSetHpBar();
	lastState = SoldierStateNone;
	nearestMonster = NULL;
	return true;
}

void Assassin::attackMonster(float dt)
{
	if(nearestMonster!=NULL && nearestMonster->getCurrHp()>0){
		auto monsterCurrHp = nearestMonster->getCurrHp();
		auto SoldierHp = this->getCurrHp();
		switch(attackCount)
		{
		case(0):
			setState(SoldierStateHit);
			monsterCurrHp =  monsterCurrHp - this->getForce();
			if(nearestMonster->getState()!=stateFrozen)
				SoldierHp =  SoldierHp - nearestMonster->getForce();
			attackCount = 1;
			break;
		case(1):
			setState(SoldierStateSkill2);
			monsterCurrHp =  monsterCurrHp - this->getForce();
			attackCount = 2;
			break;
		case(2):
			setState(SoldierStateSkill1);
			monsterCurrHp =  monsterCurrHp - this->getForce() - 30;
			if(nearestMonster->getState()!=stateFrozen)
				SoldierHp =  SoldierHp - nearestMonster->getForce();
			attackCount = 0;
			break;
		}
	
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
			unschedule(schedule_selector(Assassin::attackMonster));
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
			if(nearestMonster != NULL && nearestMonster->getCurrHp()>0){
				nearestMonster->restartWalking();
				nearestMonster->setIsAttacking(false);
			}
			baseSprite->runAction(Sequence::create
				(CallFuncN::create(CC_CALLBACK_0(Assassin::setState, this,SoldierStateDeath))
				,Animate::create(AnimationCache::getInstance()->getAnimation("Assassin_dead"))
				,FadeOut::create(1.0f)
				,NULL));	
		}
	}else{
		unschedule(schedule_selector(Assassin::attackMonster));
		if(this->getCurrHp()>0)
			runToLocation(location);
	}

}