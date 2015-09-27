#include "MechaBomb.h"
#include "GameManager.h"

bool MechaBomb::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	sprite = Sprite::createWithSpriteFrameName("Bombs_0006.png");
	setMaxForce(20);
	setRotation(-360.0f);
	addChild(sprite);
	return true;
}

void MechaBomb::shoot()
{
	runAction(Sequence::create(bulletAction,
              CallFuncN::create(CC_CALLBACK_0(MechaBomb::removeBullet, this)),
               NULL));
}

void MechaBomb::removeBullet()
{
	auto instance = GameManager::getInstance();

	auto MechaBombPostion = this->getPosition() + this->getParent()->getPosition();

	auto monsterVector = instance->monsterVector;

	for (int j = 0; j < monsterVector.size(); j++)
	{
		auto monster = monsterVector.at(j);
		auto monsterPosition = monster->baseSprite->getPosition();

		if(monster!=NULL && MechaBombPostion.distance(monsterPosition)<= 50 && monster->getAttackBySoldier())
		{
			SoundManager::playBomb();
			auto currHp = monster->getCurrHp();

			currHp =  currHp - this->getMaxForce();
                
			if(currHp <= 0){
				currHp = 0;
			}
			monster->setCurrHp( currHp );

			monster->getHpBar()->setPercentage((currHp/monster->getMaxHp())*100);
  
			if(currHp == 0){
				monster->explosion();
				instance->monsterVector.eraseObject(monster);
			}
		}		
	}	
	sprite->runAction(Sequence::create(
		Animate::create(AnimationCache::getInstance()->getAnimation("MechaBomb")),
		CallFuncN::create(CC_CALLBACK_0(Bullet::removeFromParent, this))
		,NULL));
}
