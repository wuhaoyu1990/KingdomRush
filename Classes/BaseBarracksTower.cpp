#include "BaseBarracksTower.h"
#include "BarrackSoldier.h"
#include "GameManager.h"
#include "BaseMap.h"
#include "UpdatePanleLayerWithFlag.h"
#include "UpdatePanleLayer2WithFlag.h"
#include "SimplePanleLayer.h"
#include "Assassin.h"
#include "Templar.h"
#include "SimplePanleLayerWithFlag.h"

void BaseBarracksTower::addTerrain()
{
	terrain = Sprite::createWithSpriteFrameName("terrain_barrack_0004.png");
	terrain->setAnchorPoint(Point(0.5,1));
	addChild(terrain,-1);
}

void BaseBarracksTower::initTower()
{
	towerBase = Sprite::createWithSpriteFrameName(String::createWithFormat("tower_barracks_lvl%d_layer1_0001.png",level)->getCString());
	door = Sprite::createWithSpriteFrameName(String::createWithFormat("tower_barracks_lvl%d_layer2_0001.png",level)->getCString());

	addChild(towerBase);
	addChild(door);
	
	auto Soldier_1 = BarrackSoldier::createSoldier(Point(40,-30),level);


	auto Soldier_2 = BarrackSoldier::createSoldier(Point(-40,-30),level);


	auto Soldier_3 = BarrackSoldier::createSoldier(Point(0,-40),level);


	Soldiers.pushBack(Soldier_1);
	Soldiers.pushBack(Soldier_2);
	Soldiers.pushBack(Soldier_3);


	addChild(Soldier_1);
	addChild(Soldier_2);
	addChild(Soldier_3);
	SoundManager::playBarrackOpendoor();
	door->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(String::createWithFormat("level%d_barracks_opendoor",getLevel())->getCString())));

	schedule(schedule_selector(BaseBarracksTower::cureSoldiers), 10.0f,-1,10.0f);
}

void BaseBarracksTower::sellTower()
{
	static_cast<BaseMap*>(this->getParent()->getParent())->playerState->removeTowerInfo();
	static_cast<Terrain*>(this->getParent())->terrain->setVisible(true);
	for(int i = 0;i<Soldiers.size();i++){
		if(Soldiers.at(i)!=NULL){
			if(Soldiers.at(i)->nearestMonster!=NULL && Soldiers.at(i)->nearestMonster->getState()!=stateDeath)
				Soldiers.at(i)->nearestMonster->restartWalking();	
			Soldiers.at(i)->stopAllActions();
			Soldiers.at(i)->unscheduleAllCallbacks();
		}
	}
	static_cast<Terrain*>(this->getParent())->smokeEffect();
	this->unscheduleAllCallbacks();
	this->removeAllChildren();
	this->removeFromParent();
}

void BaseBarracksTower::cureSoldiers(float dt)
{
	for(int i = 0;i<Soldiers.size();i++)
	{
		auto Soldier = Soldiers.at(i);
		if(Soldier->getState() == SoldierStateWait){
			Soldier->setCurrHp(Soldier->getMaxHp());
			Soldier->setHpPercentage(100);
			Soldier->getHpBar()->setPercentage(100);
		}
		else if(Soldier->getState() == SoldierStateDeath){
			if(level <= 3){
				SoundManager::playBarrackOpendoor();
				door->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(String::createWithFormat("level%d_barracks_opendoor",getLevel())->getCString())));
				auto point = Soldier->getLocation();
				Soldier ->removeFromParent();
				Soldier = NULL;
				auto newSoldier = BarrackSoldier::createSoldier(point,level);
				Soldiers.replace(i,newSoldier);
				addChild(newSoldier);
			}else if(level == 4){
				SoundManager::playBarrackOpendoor();
				door->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(String::createWithFormat("level%d_barracks_opendoor",getLevel())->getCString())));
				auto point = Soldier->getLocation();
				Soldier ->removeFromParent();
				Soldier = NULL;
				auto asssaain = Assassin::createAssassin(point);

				Soldiers.replace(i,asssaain);
				addChild(asssaain);
				asssaain->cheakState();
			}else if(level == 5){
				SoundManager::playBarrackOpendoor();
				door->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(String::createWithFormat("level%d_barracks_opendoor",getLevel())->getCString())));
				auto point = Soldier->getLocation();
				Soldier ->removeFromParent();
				Soldier = NULL;
				auto templar = Templar::createTemplar(point);

				Soldiers.replace(i,templar);
				addChild(templar);
				templar->cheakState();
			}
		}
	}
}

bool BaseBarracksTower::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setTowerType(BARAACKS_1);
	setLevel(1);
	addTerrain();
	
	
	setScope(160);
	setUpdateMoney(100);
	setBuildMoney(100);
	isUpdateMenuShown = false;
	return true;
}

void BaseBarracksTower::buildingAnimation()
{
	auto building = Sprite::create();
	auto constructing = Sprite::createWithSpriteFrameName("tower_constructing_0002.png");
	auto hpBgSprite = Sprite::createWithSpriteFrameName("buildbar_bg.png");
	hpBgSprite->setPosition(Point(constructing->getContentSize().width / 2, constructing->getContentSize().height /2+10));
	auto hpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("buildbar.png"));
	hpBar->setType(ProgressTimer::Type::BAR);
	hpBar->setMidpoint(Point(0, 0.5f));
	hpBar->setBarChangeRate(Point(1, 0));
	hpBar->setPercentage(0);
    hpBar->setPosition(Point(hpBgSprite->getContentSize().width / 2, hpBgSprite->getContentSize().height / 2 ));
    hpBgSprite->addChild(hpBar);
	constructing->addChild(hpBgSprite);
	building->addChild(constructing);
	addChild(building);

	hpBar->runAction(Sequence::create(ProgressTo::create(0.5f, 100)
		, CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, building))
                                           , NULL));
	scheduleOnce(schedule_selector(BaseBarracksTower::buildingSmokeAnimation),0.5f);
}

void BaseBarracksTower::buildingSmokeAnimation(float dt)
{
	auto smoke = Sprite::createWithSpriteFrameName("effect_buildSmoke_0001.png");
	addChild(smoke,99);
	smoke->runAction(Sequence::create(
		Animate::create(AnimationCache::getInstance()->getAnimation("build_smoke")),
		CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, smoke)),NULL));
	SoundManager::playBarrackReady();
	initTower();
	setListener();

}

void BaseBarracksTower::showUpdateMenu()
{
	if(level < 3){
		auto updatePanleLayer = UpdatePanleLayerWithFlag::create();
		updatePanleLayer->setTag(myTerrain->getTag()+100);
		updatePanleLayer->setTower(this);
		updatePanleLayer->setPosition(this->getParent()->getPosition());
		static_cast<BaseMap*>(this->getParent()->getParent())->mTouchLayer->addChild(updatePanleLayer);
		if(level == 1 && GameManager::getInstance()->LEVEL ==0){
			updatePanleLayer->couldUpdate = false;
		}else if(level == 2 && GameManager::getInstance()->LEVEL <=1){
			updatePanleLayer->couldUpdate = false;
		}
		updatePanleLayer->inAnimation();
		isUpdateMenuShown = true;
	}else if(level == 3){
		auto updatePanleLayer = UpdatePanleLayer2WithFlag::createPanle(24,23,230,230);
		updatePanleLayer->setTag(myTerrain->getTag()+100);
		updatePanleLayer->setTower(this);
		updatePanleLayer->setPosition(this->getParent()->getPosition());
		static_cast<BaseMap*>(this->getParent()->getParent())->mTouchLayer->addChild(updatePanleLayer);
		if(GameManager::getInstance()->LEVEL <=2){
		updatePanleLayer->couldUpdate1 = false;
		}
		if(GameManager::getInstance()->LEVEL <=3){
			updatePanleLayer->couldUpdate2 = false;
		}
		updatePanleLayer->inAnimation();
		isUpdateMenuShown = true;
	}else{	
		auto updatePanleLayer = SimplePanleLayerWithFlag::create();
		updatePanleLayer->setTag(myTerrain->getTag()+100);
		updatePanleLayer->setTower(this);
		updatePanleLayer->setPosition(this->getParent()->getPosition());
		static_cast<BaseMap*>(this->getParent()->getParent())->mTouchLayer->addChild(updatePanleLayer);
		updatePanleLayer->inAnimation();
		isUpdateMenuShown = true;
	}
}

void BaseBarracksTower::update1()
{
	level = 4;
	setTowerType(ASSASSIN);
	buildMoney = buildMoney + 230;
	towerBase -> setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tower_assasins_layer1_0001.png"));
	door->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tower_assasins_layer2_0001.png"));
	for(int i = 0; i< Soldiers.size() ;i++)
	{
		auto assassin = Assassin::createAssassin(Soldiers.at(i)->getLocation());
		assassin->setPosition(Soldiers.at(i)->getPosition());
		if(Soldiers.at(i)->nearestMonster!=NULL)
			assassin->nearestMonster = Soldiers.at(i)->nearestMonster;
		Soldiers.at(i)->removeFromParent();
		Soldiers.replace(i,assassin);
		addChild(assassin);
		assassin->cheakState();
	}
	isUpdateMenuShown = false;
}

void BaseBarracksTower::update2()
{
	level = 5;
	setTowerType(TEMPLAR);
	buildMoney = buildMoney + 230;
	towerBase -> setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tower_templars_layer1_0001.png"));
	door->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tower_templars_layer2_0001.png"));
	auto fire1 = Sprite::createWithSpriteFrameName("TemplarTower_Fire_0001.png");
	fire1->setPosition(Point(20,-20));
	addChild(fire1);
	fire1->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("level5_barracks_fire"))));
	auto fire2 = Sprite::createWithSpriteFrameName("TemplarTower_Fire_0001.png");
	fire2->setPosition(Point(-20,-20));
	addChild(fire2);
	fire2->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("level5_barracks_fire"))));
	for(int i = 0; i< Soldiers.size() ;i++)
	{
		auto templar = Templar::createTemplar(Soldiers.at(i)->getLocation());
		templar->setPosition(Soldiers.at(i)->getPosition());
		if(Soldiers.at(i)->nearestMonster!=NULL)
			templar->nearestMonster = Soldiers.at(i)->nearestMonster;
		Soldiers.at(i)->removeFromParent();
		Soldiers.replace(i,templar);
		addChild(templar);
		templar->cheakState();
	}
	isUpdateMenuShown = false;
}

void BaseBarracksTower::updateTower()
{
	level ++;
	if(level == 2){
		SoundManager::playBarrack2Ready();
		setTowerType(BARAACKS_2);
	}
	if(level == 3){
		SoundManager::playBarrack3Ready();
		setTowerType(BARAACKS_3);
	}
	buildMoney = buildMoney + 100;
	towerBase -> setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("tower_barracks_lvl%d_layer1_0001.png",level)->getCString()));
	door->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("tower_barracks_lvl%d_layer2_0001.png",level)->getCString()));
	for(int i = 0; i< Soldiers.size() ;i++)
	{
		Soldiers.at(i)->updateSoldier(level);
	}
	isUpdateMenuShown = false;
}

void BaseBarracksTower::setRallyPoint(Point point)
{
	if(level == 1||level == 2||level ==3)
		SoundManager::playBarrackMove();
	else if(level == 4 )
		SoundManager::playAssassinMove();
	auto rally = point - this->getParent()->getPosition();

	Soldiers.at(0)->setLocation(Point(rally.x + 20,rally.y - 20));
	Soldiers.at(1)->setLocation(Point(rally.x - 20,rally.y - 20));
	Soldiers.at(2)->setLocation(Point(rally.x ,rally.y + 20));

	for(int i = 0; i< Soldiers.size()&& Soldiers.at(i)!=NULL && Soldiers.at(i)->getState()!=SoldierStateDeath;i++)
	{
		if(Soldiers.at(i)->nearestMonster!=NULL && Soldiers.at(i)->nearestMonster->getState()!=stateDeath)
			Soldiers.at(i)->nearestMonster->restartWalking();			
		Soldiers.at(i)->runToLocation(Soldiers.at(i)->getLocation());
	}
}