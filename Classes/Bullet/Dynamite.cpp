#include "Dynamite.h"
#include "GameManager.h"

bool Dynamite::init()
{
	if(!Sprite::init()){
		return false;
	}
	sprite = Sprite::createWithSpriteFrameName("dynamite.png");
	addChild(sprite);
	return true;
}

void Dynamite::shoot(Point point)
{
	setPosition(point);

	sprite->runAction(Spawn::create(
		Sequence::create(MoveBy::create(0.5f,Point(0,50)),
			MoveBy::create(0.5f,Point(0,-50)),
			Animate::create(AnimationCache::getInstance()->getAnimation("bomb")),
			CallFuncN::create(CC_CALLBACK_0(Dynamite::removeBullet, this)),NULL),
				RotateBy::create(1.0f,1080.0f),NULL));
}

void Dynamite::removeBullet()
{
	auto instance = GameManager::getInstance();
    auto monsterVector = instance->monsterVector;
	SoundManager::playBomb();
	for(int i = 0; i < monsterVector.size(); i++)
	{
		auto monster = monsterVector.at(i);
		double distance = (this->getPosition()).getDistance(monster->baseSprite->getPosition());

		if (monster!=NULL && distance < 50) {
			auto currHp = monster->getCurrHp();

			currHp =  currHp -500;
                
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
	this->removeFromParent();
}