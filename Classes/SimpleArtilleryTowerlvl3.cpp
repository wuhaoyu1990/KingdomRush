#include "SimpleArtilleryTowerlvl3.h"
#include "UpdatePanleLayer.h"
#include "GameManager.h"
#include "BaseMap.h"
#include "EarthquakeTower.h"
#include "UpdatePanleLayer2.h"
#include "MechsTower.h"

bool SimpleArtilleryTowerlvl3::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setTowerType(ARTILLERY_3);
	setLevel(3);
	addTerrain();
	initTower(3);
	setListener();
	setScope(200.0f);
	setUpdateMoney(230);
	setBuildMoney(320);
	isUpdateMenuShown = false;
	schedule(schedule_selector(SimpleArtilleryTowerlvl3::shoot), 3.0f);
	SoundManager::playArtillery3Ready();
	return true;
}

void SimpleArtilleryTowerlvl3::showUpdateMenu()
{
	auto updatePanleLayer = UpdatePanleLayer2::createPanle(27,28,230,230);
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
}

void SimpleArtilleryTowerlvl3::update1()
{
	auto earthquakeTower = EarthquakeTower::create();
	earthquakeTower->setMyTerrain(myTerrain);
	earthquakeTower->setTag(myTerrain->getTag());
	earthquakeTower->setPosition(Point(0,20));
	myTerrain->addChild(earthquakeTower);
	this->removeTower();
}

void SimpleArtilleryTowerlvl3::update2()
{
	auto mechsTower = MechsTower::create();
	mechsTower->setMyTerrain(myTerrain);
	mechsTower->setTag(myTerrain->getTag());
	mechsTower->setPosition(Point(0,30));
	myTerrain->addChild(mechsTower);
	this->removeTower();
}