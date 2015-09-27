#include "EarthquakeTower.h"
#include "EarthquakeSmoke.h"
#include "GameManager.h"
#include "Drill.h"
#include "SimplePanleLayer.h"
#include "BaseMap.h"

bool EarthquakeTower::init()
{
	if(!Sprite::init()){
		return false;
	}
	setTowerType(EARTHQUAKE);
	addTerrain();
	setScope(220.0f);
	setBuildMoney(550);
	towerBase = Sprite::createWithSpriteFrameName("EarthquakeTower_Base.png");
	addChild(towerBase);
	operation = Sprite::createWithSpriteFrameName("EarthquakeTower_0001.png");
	addChild(operation);
	glow = Sprite::createWithSpriteFrameName("EarthquakeTower_Glow_0001.png");
	glow->setPosition(Point(0,40));
	addChild(glow);
	glow->setVisible(false);
	hitSmoke = EarthquakeSmoke::create();
	addChild(hitSmoke);

	lava = Lava::create();
	addChild(lava);
	HitDecal = Sprite::createWithSpriteFrameName("EarthquakeTower_HitDecal3.png");
	addChild(HitDecal);
	HitDecal->setVisible(false);
	light = Sprite::createWithSpriteFrameName("EarthquakeTower_lights_0001.png");
	addChild(light);

	attackCount = 0;
	schedule(schedule_selector(EarthquakeTower::shoot), 2.5f);
	SoundManager::playEarthquakeReady();
	setListener();
	return true;
}

void EarthquakeTower::addTerrain()
{
	terrain = Sprite::createWithSpriteFrameName("terrain_specials_0004.png");
	terrain->setAnchorPoint(Point(0.5,1));
	addChild(terrain,-1);
}

void EarthquakeTower::shoot(float dt)
{
	checkNearestMonster();
	HitDecal->setScale(1.0f);
	if(nearestMonster!=NULL && nearestMonster->getCurrHp() > 0)
    {
		attackCount ++;
		if( attackCount != 3){
			SoundManager::playEarthquakeHit();
			HitDecal->runAction(Sequence::create(
				DelayTime::create(1.0f),
				CallFuncN::create(CC_CALLBACK_0(Sprite::setVisible,HitDecal,true)),
				ScaleTo::create(0.5f,3.5f,3.5f),
				CallFuncN::create(CC_CALLBACK_0(Sprite::setVisible,HitDecal,false)),
				NULL));
			operation->runAction(Sequence::create(			
				Animate::create(AnimationCache::getInstance()->getAnimation("EarthquakeTower_operation_down")),
				CallFuncN::create(CC_CALLBACK_0(EarthquakeSmoke::shoot,hitSmoke)),
				CallFuncN::create(CC_CALLBACK_0(EarthquakeTower::attackMonsters,this,60)),
				Animate::create(AnimationCache::getInstance()->getAnimation("EarthquakeTower_operation_up")),
				NULL));
		}
		else if(attackCount == 3){
			SoundManager::playEarthquakeLava();
			HitDecal->runAction(Sequence::create(
				DelayTime::create(1.0f),
				CallFuncN::create(CC_CALLBACK_0(Sprite::setVisible,HitDecal,true)),
				ScaleTo::create(0.5f,3.5f,3.5f),
				CallFuncN::create(CC_CALLBACK_0(Sprite::setVisible,HitDecal,false)),
				NULL));
			operation->runAction(Sequence::create(			
				Animate::create(AnimationCache::getInstance()->getAnimation("EarthquakeTower_operation_down")),
				CallFuncN::create(CC_CALLBACK_0(Lava::shoot,lava)),
				CallFuncN::create(CC_CALLBACK_0(EarthquakeTower::attackMonsters,this,100)),
				Animate::create(AnimationCache::getInstance()->getAnimation("EarthquakeTower_operation_up")),
				NULL));
			glow->runAction(Sequence::create(
				CallFuncN::create(CC_CALLBACK_0(Sprite::setVisible,glow,true)),
				Repeat::create(Animate::create(AnimationCache::getInstance()->getAnimation("EarthquakeTower_glow")),3),
				CallFuncN::create(CC_CALLBACK_0(Sprite::setVisible,glow,false)),
				NULL));
			attackCount = 0;
		}		
	}else{
		bool shouldDrill = false;
		auto monsterVector = GameManager::getInstance()->monsterVector;
		for (int j = 0; j < monsterVector.size(); j++){
			auto monster = monsterVector.at(j);

			if(monster!=NULL && monster->getCurrHp()>0 && monster->getAttackBySoldier()){
				shouldDrill = true;
				break;
			}
		}
		if(shouldDrill){
			SoundManager::playEarthquakeDrillin();
			auto drill = Drill::create();
			this->getParent()->getParent()->addChild(drill);
			light->runAction(
				Repeat::create(Animate::create(AnimationCache::getInstance()->getAnimation("EarthquakeTower_light")),10));
			
			operation->runAction(Sequence::create(
				Animate::create(AnimationCache::getInstance()->getAnimation("EarthquakeTower_drilling")),
				CallFuncN::create(CC_CALLBACK_0(Drill::shoot,drill)),
				NULL));
		}
	}
}

void EarthquakeTower::attackMonsters(int force)
{
	auto monsterVector = GameManager::getInstance()->monsterVector;
	auto towerPosition = this->getParent()->getPosition();
	for (int j = 0; j < monsterVector.size(); j++)
	{
		auto monster = monsterVector.at(j);
		auto monsterPosition = monster->baseSprite->getPosition();
		if(towerPosition.distance(monsterPosition)<= 220 && monster->getAttackBySoldier() )
		{
			auto currHp = monster->getCurrHp();
			monster->slowRunSpeed(2.0f,5);
			currHp =  currHp - force;
                
			if(currHp <= 0){
				currHp = 0;
			}
			monster->setCurrHp( currHp );

			monster->getHpBar()->setPercentage((currHp/monster->getMaxHp())*100);
  
			if(currHp == 0){
				monster->explosion();
				//GameManager::getInstance()->monsterVector.eraseObject(monster);
			}
		}
	}
}

void EarthquakeTower::showUpdateMenu()
{
	auto updatePanleLayer = SimplePanleLayer::create();
	updatePanleLayer->setTag(myTerrain->getTag()+100);
	updatePanleLayer->setTower(this);
	updatePanleLayer->setPosition(this->getParent()->getPosition());
	static_cast<BaseMap*>(this->getParent()->getParent())->mTouchLayer->addChild(updatePanleLayer);
	updatePanleLayer->inAnimation();
	isUpdateMenuShown = true;
}

void EarthquakeTower::checkNearestMonster()
{
    auto instance = GameManager::getInstance();
    auto monsterVector = instance->monsterVector;
    
	auto currMinDistant = this->scope;
    
	BaseMonster *monsterTemp = NULL;
	for(int i = 0; i < monsterVector.size(); i++)
	{
		auto monster = monsterVector.at(i);
		double distance = this->getParent()->getPosition().getDistance(monster->baseSprite->getPosition());

		if (distance < currMinDistant && monster->getAttackBySoldier() ) {
			currMinDistant = distance;
            monsterTemp = monster;
		}
	}
    nearestMonster = monsterTemp;
}