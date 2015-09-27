#include "Bomb.h"

Bomb* Bomb::createBombWithType(int level)
{
    auto bomb = new Bomb();
 
    if (bomb && bomb->initWithType(level))
    {
        bomb->autorelease();
        return bomb;
    }
    CC_SAFE_DELETE(bomb);
    return NULL;
}

bool Bomb::initWithType(int type)
{
	if (!Sprite::init())
	{
		return false;
	}
	switch (type)
	{
	case(1):{
		sprite = Sprite::createWithSpriteFrameName("bombs_0001.png");
		setMaxForce(20);
		}
		break;
	case(2):{
		sprite = Sprite::createWithSpriteFrameName("bombs_0002.png");
		setMaxForce(30);
		}
		break;
	case(3):{
		sprite = Sprite::createWithSpriteFrameName("bombs_0003.png");
		setMaxForce(40);
		}
		break;
	case(4):{
		sprite = Sprite::createWithSpriteFrameName("bombs_0006.png");
		setMaxForce(30);
		}
		break;
	}
	addChild(sprite);
	return true;
}

void Bomb::shoot()
{
	runAction(Sequence::create(bulletAction,
              CallFuncN::create(CC_CALLBACK_0(Bomb::removeBullet, this)),
               NULL));
}

void Bomb::removeBullet()
{
	auto instance = GameManager::getInstance();
  
	auto bombPostion = this->getPosition() + this->getParent()->getPosition();

	auto monsterVector = instance->monsterVector;

	for (int j = 0; j < monsterVector.size(); j++)
	{
		auto monster = monsterVector.at(j);
		auto monsterPosition = monster->baseSprite->getPosition();

		if(monster!=NULL && bombPostion.distance(monsterPosition)<= 50  && monster->getAttackBySoldier())
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
			}
		}		
	}	
	sprite->runAction(Sequence::create(
		Animate::create(AnimationCache::getInstance()->getAnimation("bomb")),
		CallFuncN::create(CC_CALLBACK_0(Bullet::removeFromParent, this))
		,NULL));
}
