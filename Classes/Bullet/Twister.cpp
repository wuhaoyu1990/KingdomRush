#include "Twister.h"
#include "GameManager.h"


bool Twister::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	sprite = Sprite::createWithSpriteFrameName("ArchMageTwister_0001.png");
	addChild(sprite);
	nearestMonster = NULL;
	scheduleOnce(schedule_selector(Twister::removeTwisterAction), 5.0f);
	return true;
}
void Twister::round()
{
	sprite->runAction(Sequence::create( 
			Animate::create(AnimationCache::getInstance()->getAnimation("ArchMageTwister_create")),
			CallFuncN::create(CC_CALLBACK_0(Twister::attackMon,this))
			,NULL));
}

void Twister::attackMon()
{
	SoundManager::playArchmageTwister();
	sprite->stopAllActions();
	sprite->runAction(
			RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("ArchMageTwister_twist"))));
	schedule(schedule_selector(Twister::hitMon), 0.5f);
	schedule(schedule_selector(Twister::move), 1.0f);
}
void Twister::removeTwisterAction(float dt)
{   
	unscheduleAllCallbacks();
	sprite->stopAllActions();
	sprite->runAction(Sequence::create(
		Animate::create(AnimationCache::getInstance()->getAnimation("ArchMageTwister_end")),
		CallFuncN::create(CC_CALLBACK_0(Twister::removeTwister, this))
		,NULL));
}

void Twister::checkNearestMonster()
{
    auto instance = GameManager::getInstance();
    auto monsterVector = instance->monsterVector;
    
	auto currMinDistant = 500;
    
	BaseMonster *monsterTemp = NULL;
	for(int i = 0; i < monsterVector.size(); i++)
	{
		auto monster = monsterVector.at(i);
		double distance = this->getParent()->getPosition().getDistance(monster->baseSprite->getPosition());

		if (monster!=NULL && distance < currMinDistant && monster->getAttackByTower() ) {
			currMinDistant = distance;
            monsterTemp = monster;
		}
	}
    nearestMonster = monsterTemp;
}

void Twister::move(float dt)
{
	checkNearestMonster();
	if(nearestMonster!=NULL && nearestMonster->getCurrHp()>10 && nearestMonster->getAttackByTower()){

			runAction(MoveBy::create(1.0f,
				nearestMonster->baseSprite->getPosition() - (this->getPosition() + this->getParent()->getPosition())));

	}
}

void Twister::removeTwister()
{
	this->removeFromParent();
}

void Twister::hitMon(float dt)
{
	GameManager *instance = GameManager::getInstance();

	auto bulletRect = Rect(this->getPositionX() +this->getParent()->getPositionX() - this->getContentSize().width /2,
                                this->getPositionY() +this->getParent()->getPositionY() - this->getContentSize().height/2 ,
								this->sprite->getContentSize().width,
                                this->sprite->getContentSize().height );

	auto monsterVector = instance->monsterVector;
    
	for (int j = 0; j < monsterVector.size(); j++)
	{
		auto monster = monsterVector.at(j);
		auto monsterRect = monster->baseSprite->getBoundingBox();
			
		if (monsterRect.intersectsRect(bulletRect)  && monster->getAttackByTower())
		{
			auto currHp = monster->getCurrHp();

			currHp =  currHp - this->getMaxForce();
                
			if(currHp <= 0){
				currHp = 0;
			}
			monster->setCurrHp( currHp );

			monster->getHpBar()->setPercentage((currHp/monster->getMaxHp())*100);
 
			if(currHp == 0){
				monster->death();
				//instance->monsterVector.eraseObject(monster);
			}
		}
	}
}