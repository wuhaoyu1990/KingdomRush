#include "Mecha.h"
#include "GameManager.h"
#include "Bomb.h"
#include "Missile.h"
#include "Shit.h"

bool Mecha::init()
{
	if (!BaseSoldier::init())
	{
		return false;
	}
	baseSprite = Sprite::createWithSpriteFrameName("Mecha_0001.png");
	shit = Sprite::createWithSpriteFrameName("Mecha_Shitting_0001.png");
	farestMonster1 = NULL;
	farestMonster2 = NULL;
	monsterCount = 0;
	couldShit = true;
	addChild(baseSprite);
	addChild(shit);
	schedule(schedule_selector(Mecha::bombMonster), 1.5f);
	return true;
}

void Mecha::shitCD(float dt)
{
	couldShit = true;
}

void Mecha::shootMissiles()
{
	auto missile = Missile::create();
	missile->setPosition(this->getPosition());
	this->getParent()->addChild(missile);
	missile->setVisible(false);
	baseSprite->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("Mecha_shoot")),
			CallFuncN::create(CC_CALLBACK_0(Missile::setVisible,missile,true)),
			CallFuncN::create(CC_CALLBACK_0(Missile::shoot,missile,farestMonster1,this->getPosition())),
			NULL));
}

void Mecha::bombMonster(float dt)
{
	checkNearestMonster();
	if(couldShit && monsterCount >= 3){
		baseSprite->runAction(Sequence::create(
			Animate::create(AnimationCache::getInstance()->getAnimation("Mecha_shit")),
			CallFuncN::create(CC_CALLBACK_0(Mecha::shitting,this)),
			CallFuncN::create(CC_CALLBACK_0(Mecha::addShit,this)),NULL));		
	}else{
		if(nearestMonster!=NULL && nearestMonster->getCurrHp() > 0 )
		{
			Point shootVector = nearestMonster->baseSprite->getPosition() - this->getParent()->getPosition();
			auto currBullet = MechaBullet();
			if(nearestMonster->baseSprite->getPosition().x - (this->getParent()->getPosition()+this->getPosition()).x>0){
				baseSprite->setFlippedX(false);
				shit->setFlippedX(false);
				currBullet->setPosition(Point(currBullet->getPosition().x-30,currBullet->getPosition().y+30));
			}else{
				baseSprite->setFlippedX(true);
				shit->setFlippedX(true);
				currBullet->setPosition(Point(currBullet->getPosition().x+30,currBullet->getPosition().y+30));
			}

			Point highPoint = Point(shootVector.x,shootVector.y+200);		
			ccBezierConfig bezier;
			bezier.controlPoint_1 = Point(currBullet->getPosition().x,currBullet->getPosition().y+200); 
			bezier.controlPoint_2 = Point(shootVector.x,shootVector.y+200);; 
			bezier.endPosition = shootVector;
			auto action = Spawn::create(BezierTo::create(0.5f, bezier),RotateTo::create(0.5f,540.0f),NULL);
			currBullet->setBulletAction(action);
			currBullet->shoot();
			baseSprite->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("Mecha_attack")),
				NULL));
			currBullet = NULL;
		}else{
			checkFarestMonster();
			if(farestMonster1!=NULL && farestMonster1->getCurrHp()>0){
				Point shootVector = farestMonster1->baseSprite->getPosition() - (this->getParent()->getPosition() + this->getPosition());
				if(shootVector.x>0){
					baseSprite->setFlippedX(false);
					shit->setFlippedX(false);
				}
				else{
					baseSprite->setFlippedX(true);
					shit->setFlippedX(true);
				}
				shootMissiles();
			}else{
				baseSprite->setFlippedX(!(baseSprite->isFlippedX()));
			}
		}

	}
}

void Mecha::addShit()
{
	SoundManager::playMechShit();
	auto shit = Shit::create();
	shit->setPosition(Point(this->getPosition().x,this->getPosition().y - baseSprite->getContentSize().height/2));
	this->getParent()->addChild(shit);
	shit->shoot();
	couldShit = false;
	scheduleOnce(schedule_selector(Mecha::shitCD), 10.0f);
}

void Mecha::shitting()
{
	shit->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("Mecha_shitting")));
}


Bomb* Mecha::MechaBullet()
{
	auto bullet = Bomb::createBombWithType(4);
	bullet->setPosition(this->getPosition());
	this->getParent()->addChild(bullet);
    return bullet;
}

void Mecha::runToLocation(Point point)
{
	stopAllActions();
	baseSprite->stopAllActions();
	unschedule(schedule_selector(Mecha::bombMonster));
	if((point.x - this->getPositionX())>0){
		baseSprite->setFlippedX(false);//ср╠ъ
	}else{
		baseSprite->setFlippedX(true);
	}
	baseSprite->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("Mecha_walk"))));
	float i = caculateTime(point);
	runAction(Sequence::create(
		MoveTo::create(caculateTime(point),point),
		CallFuncN::create(CC_CALLBACK_0(Sprite::stopAllActions,baseSprite)),
		NULL));
	SoundManager::playMechWalk();
	schedule(schedule_selector(Mecha::bombMonster), 1.5f,-1,caculateTime(point));
}

void Mecha::checkNearestMonster()
{
	monsterCount = 0;
	auto instance = GameManager::getInstance();
    auto monsterVector = instance->monsterVector;
    
	auto currMinDistant = 200;
    
	BaseMonster *monsterTemp = NULL;
	for(int i = 0; i < monsterVector.size(); i++)
	{
		auto monster = monsterVector.at(i);
		double distance = (this->getParent()->getPosition()+this->getPosition()).getDistance(monster->baseSprite->getPosition());

		if (distance < currMinDistant && monster->getAttackBySoldier()) {
			currMinDistant = distance;
            monsterTemp = monster;
			monsterCount ++;
		}
	}
    nearestMonster = monsterTemp;
}

void Mecha::checkFarestMonster()
{
	auto instance = GameManager::getInstance();
    auto monsterVector = instance->monsterVector;
    
	auto currMinDistant = 200;
    
	BaseMonster *monsterTemp = NULL;
	for(int i = 0; i < monsterVector.size(); i++)
	{
		auto monster = monsterVector.at(i);
		double distance = this->getParent()->getPosition().getDistance(monster->baseSprite->getPosition());

		if (distance > currMinDistant && monster->getAttackByTower()) {
			currMinDistant = distance;
            monsterTemp = monster;
			break;
		}
	}
    farestMonster1 = monsterTemp;
}