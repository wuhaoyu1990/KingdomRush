#include "SimpleArrowTowerlvl2.h"
#include "SimpleArrowTowerlvl3.h"
#include "UpdatePanleLayer.h"
#include "BaseMap.h"
#include "GameManager.h"
#include "Arrow.h"

bool SimpleArrowTowerlvl2::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setTowerType(ARCHER_2);
	setLevel(2);
	addTerrain();
	initTower(2);
	setListener();
	setScope(200.0f);
	setUpdateMoney(150);
	setBuildMoney(170);
	setNextScope(220.0f);
	isUpdateMenuShown = false;
	schedule(schedule_selector(SimpleArrowTowerlvl2::shoot), 1.0f);
	SoundManager::playArcher2Ready();
	return true;
}

void SimpleArrowTowerlvl2::updateTower()
{
	auto simpleArrowTowerlvl3 = SimpleArrowTowerlvl3::create();
	simpleArrowTowerlvl3->setMyTerrain(myTerrain);
	simpleArrowTowerlvl3->setTag(myTerrain->getTag());
	simpleArrowTowerlvl3->setPosition(Point(0,20));
	myTerrain->addChild(simpleArrowTowerlvl3);
	this->removeTower();
}

void SimpleArrowTowerlvl2::showUpdateMenu()
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

Bullet* SimpleArrowTowerlvl2::ArrowTowerBullet()
{
	auto bullet = Arrow::create();
	bullet->setRotation(90.0f);
	bullet->setMaxForce(12);
	this->getParent()->addChild(bullet);
    return bullet;
}