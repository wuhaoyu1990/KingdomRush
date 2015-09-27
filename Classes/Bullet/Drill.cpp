#include "Drill.h"

bool Drill::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	drill = Sprite::createWithSpriteFrameName("EarthquakeTower_drill_0001.png");
	monsterToBeDrilled = NULL;
	addChild(drill);		
	return true;
}

void Drill::shoot()
{	
	auto instance = GameManager::getInstance();
 
	auto monsterVector = instance->monsterVector;
	for (int j = 0; j < monsterVector.size(); j++)
	{
		auto monster = monsterVector.at(j);

		if(monster!=NULL && monster->getCurrHp()>0 && monster->getAttackBySoldier())
		{
			monsterToBeDrilled = monster;
			break;
		}

	}
	if(monsterToBeDrilled!=NULL){
		scheduleOnce(schedule_selector(Drill::DrillMonster), 0.5f);
		drill->setPosition(monsterToBeDrilled->baseSprite->getPosition());
		drill->runAction(Sequence::create(
			Animate::create(AnimationCache::getInstance()->getAnimation("EarthquakeTower_drill")),
			CallFuncN::create(CC_CALLBACK_0(Drill::removeBullet, this)),
			NULL));
	}else{
		removeBullet();
	}
}



void Drill::DrillMonster(float dt)
{
	SoundManager::playEarthquakeDrillOut();
	if(monsterToBeDrilled!=NULL){
		auto currHp = monsterToBeDrilled->getCurrHp() - 100;
		if(currHp <= 0){
			currHp = 0;
		}
		monsterToBeDrilled->setCurrHp(currHp);

		monsterToBeDrilled->getHpBar()->setPercentage((currHp/monsterToBeDrilled->getMaxHp())*100);
  
		if(currHp == 0){
			unschedule(schedule_selector(Drill::DrillMonster));
			monsterToBeDrilled->death();
		}
	}else{
		removeBullet();
	}
}

void Drill::removeBullet()
{
	this->removeFromParent();
}