#include "ArchMageTower.h"
#include "SimplePanleLayer.h"
#include "BaseMap.h"
#include "GameManager.h"
#include "ArchMageBolt.h"
#include "Twister.h"
#include "SimplePanleLayer.h"

void ArchMageTower::sellTower()
{
	for(int i=0;i<3;i++)
	{
		if(NULL!=DelayBullet[i])
		{
			DelayBullet[i]->removeFromParent();
		}
	}
	static_cast<Terrain*>(this->getParent())->terrain->setVisible(true);
	this->removeFromParent();
}

bool ArchMageTower::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setTowerType(ARCHMAGE);
	DelayBullet[0] = NULL;
	DelayBullet[1] = NULL;
	DelayBullet[2] = NULL;
	setLevel(4);
	addTerrain();
	initTower(4);
	setListener();
	setScope(220.0f);
	setBuildMoney(730);
	isUpdateMenuShown = false;
	SoundManager::playArchmageReady();
	schedule(schedule_selector(ArchMageTower::Attack), 2.0f);
	schedule(schedule_selector(ArchMageTower::AtTwister), 7.0f);
	return true;
}
void ArchMageTower::showUpdateMenu()
{
	auto updatePanleLayer = SimplePanleLayer::create();
	updatePanleLayer->setTag(myTerrain->getTag()+100);
	updatePanleLayer->setTower(this);
	updatePanleLayer->setPosition(this->getParent()->getPosition());
	static_cast<BaseMap*>(this->getParent()->getParent())->mTouchLayer->addChild(updatePanleLayer);
	updatePanleLayer->inAnimation();
	isUpdateMenuShown = true;
}
Bullet* ArchMageTower::MageTowerBullet()
{
	auto bullet = ArchMageBolt::create();
	bullet->setPosition(Point(10,45));
	bullet->setMaxForce(80);
	this->getParent()->addChild(bullet);
    return bullet;
}
void ArchMageTower::buildDelayBullet()
{
	for(int i=0;i<3;i++)
	{
		if(NULL==DelayBullet[i])
		{
			SoundManager::playArchmagePrecharge();
			shooter->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("ArchMageGuy_up")));	
			DelayBullet[i]=ArchMageBolt::create();
			DelayBullet[i]->setMaxForce(100);
			DelayBullet[i]->setPosition(Point(-10,50));
			this->getParent()->addChild(DelayBullet[i]);
			MoveTo* move;
			if(1==i){
				move=MoveTo::create(1.5f,Point(20*i-20,75));
			}else{
				move=MoveTo::create(1.5f,Point(20*i-20,65));	
			}
			auto sequence=Sequence::create(move,DelayTime::create(1.2f),NULL);
			DelayBullet[i]->runAction(sequence);
			break;
		}
		
	}
}
void ArchMageTower::Attack(float dt)
{
	auto instance = GameManager::getInstance();

	checkNearestMonster();
	if(nearestMonster==NULL)
	{
		buildDelayBullet();
	}
	if(nearestMonster!=NULL && nearestMonster->getCurrHp() > 0 )
    {
		SoundManager::playArchmageShot();
		auto currBullet = MageTowerBullet();

		Point shootVector = nearestMonster->baseSprite->getPosition() - this->getParent()->getPosition();
		
		auto rotation=atan2(shootVector.y,shootVector.x);
		currBullet->setRotation(rotation);
		
		if(shootVector.y>0)
		{
			shooter->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("ArchMageGuy_down")));	
		}
		else
		{
			shooter->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("ArchMageGuy_up")));	
		}
		auto actionMove=MoveTo::create(0.5f,shootVector);
		auto action=Spawn::create(actionMove,NULL);
		for(int i=0;i<3;i++)
		{
			if(NULL!=DelayBullet[i])
			{
				DelayBullet[i]->setBulletAction(Spawn::create(MoveTo::create(0.5f,shootVector),NULL));
				DelayBullet[i]->shoot();
				DelayBullet[i]=NULL;
			}
		}
		currBullet->setBulletAction(Spawn::create(MoveTo::create(0.5f,shootVector),NULL));
		currBullet->shoot();
		currBullet = NULL;
	}
}
void ArchMageTower::AtTwister(float dt)
{
	if(nearestMonster!=NULL && nearestMonster->getCurrHp() > 0){
		auto twister=Twister::create();
		Point shootVector = nearestMonster->baseSprite->getPosition() - this->getParent()->getPosition();
		twister->setPosition(shootVector);
		this->getParent()->addChild(twister);
		twister->round();
		twister=NULL;
	}
}
