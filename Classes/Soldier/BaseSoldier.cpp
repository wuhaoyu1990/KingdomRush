#include "BaseSoldier.h"
#include "GameManager.h"

void BaseSoldier::createAndSetHpBar()
{
    hpBgSprite = Sprite::createWithSpriteFrameName("lifebar_bg_small.png");

    hpBgSprite->setPosition(Point(baseSprite->getContentSize().width / 2, baseSprite->getContentSize().height /3*2));
    baseSprite->addChild(hpBgSprite);
    
	hpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("lifebar_small.png"));
	hpBar->setType(ProgressTimer::Type::BAR);
	hpBar->setMidpoint(Point(0, 0.5f));
	hpBar->setBarChangeRate(Point(1, 0));
	hpBar->setPercentage(100);
    hpBar->setPosition(Point(hpBgSprite->getContentSize().width / 2, hpBgSprite->getContentSize().height / 2 ));
    hpBgSprite->addChild(hpBar);
}

void BaseSoldier::runToMonster()
{
	Point destination;
	if (!checkDirectionForMonster()){//¹ÖÔÚÓÒ±ß
		destination.x = nearestMonster->baseSprite->getPositionX() + nearestMonster->baseSprite->getContentSize().width/2 - this->getParent()->getParent()->getPositionX()- this->baseSprite->getContentSize().width/2;
		destination.y = nearestMonster->baseSprite->getPositionY() - this->getParent()->getParent()->getPositionY() - this->baseSprite->getContentSize().height/4;
	}else{//×ó±ß
		destination.x = nearestMonster->baseSprite->getPositionX() - nearestMonster->baseSprite->getContentSize().width/2 - this->getParent()->getParent()->getPositionX()+ this->baseSprite->getContentSize().width/2;
		destination.y = nearestMonster->baseSprite->getPositionY() - this->getParent()->getParent()->getPositionY() - this->baseSprite->getContentSize().height/4;
	}
	setState(SoldierStateRun);
	runAction(Sequence::create(MoveTo::create(caculateTime(destination),destination) , NULL));
	schedule(schedule_selector(BaseSoldier::attackMonster), 1.0f,-1,caculateTime(destination));
}

void BaseSoldier::runToLocation(Point point)
{
	if(getState()!=stateDeath){
		unscheduleAllCallbacks();
		scheduleUpdate();
		stopAllActions();
		if((point.x - this->getPositionX())>0){
			baseSprite->setFlippedX(false);//ÓÒ±ß
		}else{
			baseSprite->setFlippedX(true);
		}
		setState(SoldierStateRun);
		runAction(Sequence::create(MoveTo::create(caculateTime(point),point),
			CallFuncN::create(CC_CALLBACK_0(BaseSoldier::setState, this,SoldierStateWait)),
			NULL));
		schedule(schedule_selector(BaseSoldier::lookingForMonsters), 1.0f,-1,caculateTime(point));
	}
}

bool BaseSoldier::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	nearestMonster = NULL;
	return true;
}

void BaseSoldier::lookingForMonsters(float dt)
{
	setState(SoldierStateWait);
	baseSprite->setFlippedX(!(baseSprite->isFlippedX()));
	checkNearestMonster();
	if(nearestMonster!=NULL && nearestMonster->getCurrHp()>0)
	{
		attack();
	}
}

void BaseSoldier::checkNearestMonster()
{
	auto instance = GameManager::getInstance();
    auto monsterVector = instance->monsterVector;
    nearestMonster = NULL;
	for(int i = 0; i < monsterVector.size(); i++)
	{
		auto monster = monsterVector.at(i);
		double distance = (this->getParent()->getParent()->getPosition()+this->getPosition()).getDistance(monster->baseSprite->getPosition());

		if (monster->getAttackBySoldier() && distance < 50 && (!monster->getIsAttacking())) {
            nearestMonster = monster;
			nearestMonster->stopWalking();
			nearestMonster->setIsAttacking(true);
			break;
		}
	}
}

bool BaseSoldier::checkDirectionForMonster()
{
	if((nearestMonster->baseSprite->getPositionX() - (this->getParent()->getParent()->getPositionX() + this->getPositionX()))>0){
		baseSprite->setFlippedX(false);
		return false;
	}else{
		baseSprite->setFlippedX(true);
		return true;
	}
}

float BaseSoldier::caculateTime(Point point)
{
	return point.getDistance(this->getPosition())/100;
}

void BaseSoldier::stopSoldierAnimation()
{
	for(int i = 1 ;i <= 8;i++)
	{
		baseSprite->stopActionByTag(i);
	}
}

void BaseSoldier::attack()
{
	unschedule(schedule_selector(BaseSoldier::lookingForMonsters));
	runToMonster();
}
