#include "ArchMageBolt.h"

bool ArchMageBolt::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	sprite = Sprite::createWithSpriteFrameName("proy_archbolt_0001.png");
	addChild(sprite);
	round();
	return true;
}
void ArchMageBolt::shoot()
{
	runAction(Sequence::create(bulletAction,
              CallFuncN::create(CC_CALLBACK_0(ArchMageBolt::removeBullet, this)),
               NULL));
}
void ArchMageBolt::round()
{
	sprite->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("proy_archbolt"))));
}
void ArchMageBolt::removeBullet()
{
    auto instance = GameManager::getInstance();

	auto bulletRect = Rect(this->getPositionX() +this->getParent()->getPositionX() - this->getContentSize().width /2,
                                this->getPositionY() + this->getParent()->getPositionY() - this->getContentSize().height/2 ,
								this->sprite->getContentSize().width,
                                this->sprite->getContentSize().height );

	auto monsterVector = instance->monsterVector;
    
	for (int j = 0; j < monsterVector.size(); j++)
	{
		auto monster = monsterVector.at(j);
		auto monsterRect = monster->baseSprite->getBoundingBox();
			
		if (monsterRect.intersectsRect(bulletRect))
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
			}
			break;
		}
	}
     this->removeFromParent();
	
}