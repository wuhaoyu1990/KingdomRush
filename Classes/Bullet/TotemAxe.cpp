#include "TotemAxe.h"
#include "GameManager.h"

bool TotemAxe::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	sprite = Sprite::createWithSpriteFrameName("TotemAxe_0001.png");
	addChild(sprite);		
	return true;
}

void TotemAxe::shoot()
{
	runAction(Sequence::create(bulletAction,
              CallFuncN::create(CC_CALLBACK_0(TotemAxe::removeBullet, this)),
               NULL));
}

void TotemAxe::removeBullet()
{
	bool isMissed = true;
    GameManager *instance = GameManager::getInstance();
   
	auto bulletRect = Rect(this->getPositionX() +this->getParent()->getPositionX() - this->getContentSize().width /2,
                                this->getPositionY() +this->getParent()->getPositionY() - this->getContentSize().height/2,
								this->sprite->getContentSize().width,
                                this->sprite->getContentSize().height );
	
	auto monsterVector = instance->monsterVector;
    
	for (int j = 0; j < monsterVector.size(); j++)
	{
		auto monster = monsterVector.at(j);
		auto monsterRect = monster->baseSprite->getBoundingBox();
			
		if (monster!=NULL && monsterRect.intersectsRect(bulletRect) && monster->getAttackByTower())
		{
			auto currHp = monster->getCurrHp();

			currHp =  currHp - this->getMaxForce();
                
			if(currHp <= 0){
				currHp = 0;
			}
			monster->setCurrHp( currHp );

			monster->getHpBar()->setPercentage((currHp/monster->getMaxHp())*100);
			monster->getHurt();
            isMissed = false;    
			if(currHp == 0){
				monster->death();
				//instance->monsterVector.eraseObject(monster);
			}
			break;
		}
	}
	if(isMissed){

		sprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("TotemAxe_0002.png"));

		sprite->runAction(Sequence::create(FadeOut::create(1.0f)
										,CallFuncN::create(CC_CALLBACK_0(Bullet::removeFromParent, this))
                                       , NULL));
	}else{
		this->removeFromParent();
	}
}