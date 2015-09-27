#include "Missile.h"
#include "GameManager.h"

bool Missile::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	sprite = Sprite::createWithSpriteFrameName("mech_missile_0001.png");
	addChild(sprite);	
	setMaxForce(100);
	return true;
}

void Missile::shoot(BaseMonster* monster,Point mechaPosition)
{
	monsterToBeDrilled = monster;
	float startAngle = sprite->getRotation();
	float endAngle = 0;
	if(monster->getHpBar()->getPercentage()<20.0f){
		auto instance = GameManager::getInstance();

		auto monsterVector = instance->monsterVector;

		for (int j = 0; j < monsterVector.size(); j++)
		{
			if(monster!=NULL && monsterVector.at(j)->getHpBar()->getPercentage()>20.0f && (monster->getAttackBySoldier()||monster->getAttackByTower())){
				monster = monsterVector.at(j);
				break;
			}
		}
	}

	auto shootVector = monster->baseSprite->getPosition() - this->getParent()->getPosition() - mechaPosition;
	auto pVectr = this->getPosition()-shootVector;
    float angleRadians=atan(pVectr.y/pVectr.x);
    float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
	if(shootVector.x<0)
		angleDegrees = 180 + angleDegrees;
	sprite->setRotation(-angleDegrees);
	sprite->runAction(Sequence::create(
		MoveTo::create(1.0f,Point(shootVector)),
		CallFuncN::create(CC_CALLBACK_0(Missile::removeBullet, this,monster))
		,NULL));
}

void Missile::removeBullet(BaseMonster* monster)
{
	if(monster!=NULL && monster->getCurrHp()>0){
		auto currHp = monster->getCurrHp();
		SoundManager::playBomb();
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
	sprite->runAction(Sequence::create(
		Animate::create(AnimationCache::getInstance()->getAnimation("bomb")),
		CallFuncN::create(CC_CALLBACK_0(Missile::removeFromParent, this))
		,NULL));
}