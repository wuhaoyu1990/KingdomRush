#include "FireBall.h"
#include "GameManager.h"
#include "Smoke.h"

bool FireBall::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	sprite = Sprite::createWithSpriteFrameName("fireball_proyectile_0001.png");
	addChild(sprite);
	this->setMaxForce(500);

	round();
	schedule(schedule_selector(FireBall::smoke), 0.01f);
	return true;
}

void FireBall::shoot(Point location)
{
	setPosition(location);
	auto move = MoveBy::create(0.5f,Point(0,-320));
	runAction(Sequence::create(move,
                               CallFuncN::create(CC_CALLBACK_0(FireBall::removeBullet, this)),
                               NULL));
}
void FireBall::round()
{
	auto repeat=RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("fireBall_fire")));
	sprite->setRotation(90.f);
	repeat->setTag(0);
	sprite->runAction(repeat);
}

void FireBall::removeBullet()
{
	SoundManager::playFireballHit();
	auto instance = GameManager::getInstance();
  
	auto bombPostion = this->getPosition() + this->getParent()->getPosition();

	auto monsterVector = instance->monsterVector;

	for (int j = 0; j < monsterVector.size(); j++)
	{
		auto monster = monsterVector.at(j);
		auto monsterPosition = monster->baseSprite->getPosition();

		if(monster!=NULL && bombPostion.distance(monsterPosition)<= 50  && monster->getAttackByTower())
		{
			SoundManager::playBomb();
			auto currHp = monster->getCurrHp();

			currHp =  currHp - this->getMaxForce() + monster->getArmor();
                
			if(currHp <= 0){
				currHp = 0;
			}
			monster->setCurrHp( currHp );

			monster->getHpBar()->setPercentage((currHp/monster->getMaxHp())*100);
  
			if(currHp == 0){
				monster->explosion();
				//instance->monsterVector.eraseObject(monster);
			}
		}		
	}	
	sprite->runAction(Sequence::create(
		Animate::create(AnimationCache::getInstance()->getAnimation("fireBall_explosion")),
		CallFuncN::create(CC_CALLBACK_0(FireBall::removeFromParent, this))
		,NULL));

}
void FireBall::smoke(float dt)
{
	auto smoke=Smoke::create();
	this->getParent()->addChild(smoke);
	smoke->setPosition(this->getPosition());
	smoke->fadeSmoke(AnimationCache::getInstance()->getAnimation("fireBall_smoke"),0);
	
	smoke=NULL;
}
void FireBall::explosion()
{
	unschedule(schedule_selector(FireBall::smoke));
	sprite->stopAllActions();
	sprite->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("fireBall_explosion")));
}
