#include "NecrBolt.h"
#include "Skeleton.h"

bool NecrBolt::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	sprite = Sprite::createWithSpriteFrameName("necromancer_bolt_0001.png");
	addChild(sprite);
	return true;
}

void NecrBolt::shoot()
{
	scheduleUpdate();
	runAction(Sequence::create(bulletAction,
                               CallFuncN::create(CC_CALLBACK_0(NecrBolt::removeBullet, this)),
                               NULL));
}

void NecrBolt::removeBullet()
{
    GameManager *instance = GameManager::getInstance();

	auto bulletRect = Rect(this->getPositionX() +this->getParent()->getPositionX() - this->getContentSize().width /2 ,
                                this->getPositionY() +this->getParent()->getPositionY() - this->getContentSize().height/2,
								this->sprite->getContentSize().width,
                                this->sprite->getContentSize().height );

	auto monsterVector = instance->monsterVector;
    
	for (int j = 0; j < monsterVector.size(); j++)
	{
		auto monster = monsterVector.at(j);
		auto monsterRect = monster->baseSprite->getBoundingBox();
			
		if (monster!=NULL && monsterRect.intersectsRect(bulletRect)&& monster->getAttackByTower())
		{
			auto currHp = monster->getCurrHp();

			currHp =  currHp - this->getMaxForce();
                
			if(currHp <= 0){
				currHp = 0;
			}
			monster->setCurrHp( currHp );

			monster->getHpBar()->setPercentage((currHp/monster->getMaxHp())*100);
			monster->getHurt();
			if(currHp == 0){
				auto skeleton = Skeleton::createSkeleton(monster->baseSprite->getPosition()-this->getParent()->getPosition());
				this->getParent()->addChild(skeleton);
				monster->death();
				//instance->monsterVector.eraseObject(monster);
			}
			break;
		}
	}
	this->removeFromParent();
}

