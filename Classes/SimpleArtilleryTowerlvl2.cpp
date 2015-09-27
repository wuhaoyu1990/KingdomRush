#include "SimpleArtilleryTowerlvl2.h"
#include "SimpleArtilleryTowerlvl3.h"
#include "UpdatePanleLayer.h"
#include "GameManager.h"
#include "BaseMap.h"

bool SimpleArtilleryTowerlvl2::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setTowerType(ARTILLERY_2);
	setLevel(2);
	addTerrain();
	initTower(2);
	setListener();
	setScope(180.0f);
	setUpdateMoney(150);
	setBuildMoney(270);
	isUpdateMenuShown = false;
	schedule(schedule_selector(SimpleArtilleryTowerlvl2::shoot), 3.0f);
	SoundManager::playArtillery2Ready();
	return true;
}

void SimpleArtilleryTowerlvl2::updateTower()
{
	auto simpleArtilleryTowerlvl3 = SimpleArtilleryTowerlvl3::create();
	simpleArtilleryTowerlvl3->setMyTerrain(myTerrain);
	simpleArtilleryTowerlvl3->setTag(myTerrain->getTag());
	simpleArtilleryTowerlvl3->setPosition(Point(0,20));
	myTerrain->addChild(simpleArtilleryTowerlvl3);
	this->removeTower();
}

void SimpleArtilleryTowerlvl2::showUpdateMenu()
{
	auto updatePanleLayer = UpdatePanleLayer::create();
	updatePanleLayer->setTag(myTerrain->getTag()+100);
	updatePanleLayer->setTower(this);
	updatePanleLayer->setPosition(this->getParent()->getPosition());
	static_cast<BaseMap*>(this->getParent()->getParent())->mTouchLayer->addChild(updatePanleLayer);
	if(GameManager::getInstance()->LEVEL <=1){
		updatePanleLayer->couldUpdate = false;
	}
	updatePanleLayer->inAnimation();
	isUpdateMenuShown = true;
}