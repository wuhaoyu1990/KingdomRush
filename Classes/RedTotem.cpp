#include "RedTotem.h"
#include "GameManager.h"

RedTotem* RedTotem::createRedTotem(Point point)
{
	auto redTotem = new RedTotem();
 
    if (redTotem && redTotem->init())
    {
        redTotem->autorelease();
		redTotem->shoot(point);
        return redTotem;
    }
    CC_SAFE_DELETE(redTotem);
    return NULL;
}

bool RedTotem::init()
{
	if(!Sprite::init()){
		return false;
	}
	sprite = Sprite::createWithSpriteFrameName("TotemTower_RedTotem_0001.png");
	addChild(sprite);
	return true;
}

void RedTotem::shoot(Point point)
{
	this->setPosition(point);
	sprite->runAction(Sequence::create(
		Animate::create(AnimationCache::getInstance()->getAnimation("TotemTower_RedTotem")),
		CallFuncN::create(CC_CALLBACK_0(RedTotem::boom,this)),
		CallFuncN::create(CC_CALLBACK_0(RedTotem::removeBullet,this)),NULL));
}

void RedTotem::boom()
{
	auto instance = GameManager::getInstance();
  
	auto bombPostion = this->getPosition() + this->getParent()->getPosition();

	auto monsterVector = instance->monsterVector;

	for (int j = 0; j < monsterVector.size(); j++)
	{
		auto monster = monsterVector.at(j);
		auto monsterPosition = monster->baseSprite->getPosition();

		if(monster!=NULL && bombPostion.distance(monsterPosition)<= 80 && monster->getAttackByTower())
		{
			auto currHp = monster->getCurrHp();

			currHp =  currHp - 100;
                
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
}

void RedTotem::removeBullet()
{
	this->removeFromParent();
}