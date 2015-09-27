#include "SimpleArrowTowerlvl3.h"
#include "UpdatePanleLayer2.h"
#include "BaseMap.h"
#include "GameManager.h"
#include "Arrow.h"
#include "CossbowHunterTower.h"
#include "TotemTower.h"

bool SimpleArrowTowerlvl3::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setTowerType(ARCHER_3);
	setLevel(3);
	addTerrain();
	initTower(3);
	setListener();
	setScope(240.0f);
	setUpdateMoney(230);
	setBuildMoney(320);
	isUpdateMenuShown = false;
	schedule(schedule_selector(SimpleArrowTowerlvl3::shoot), 1.0f);
	SoundManager::playArcher3Ready();
	return true;
}

void SimpleArrowTowerlvl3::updateTower()
{}

void SimpleArrowTowerlvl3::showUpdateMenu()
{
	auto updatePanleLayer = UpdatePanleLayer2::createPanle(25,26,230,230);
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

Bullet* SimpleArrowTowerlvl3::ArrowTowerBullet()
{
	auto bullet = Arrow::create();
	bullet->setRotation(90.0f);
	bullet->setMaxForce(16);
	this->getParent()->addChild(bullet);
    return bullet;
}

void SimpleArrowTowerlvl3::update1()
{
	auto cossbowHunterTower = CossbowHunterTower::create();
	cossbowHunterTower->setMyTerrain(myTerrain);
	cossbowHunterTower->setTag(myTerrain->getTag());
	cossbowHunterTower->setPosition(Point(0,20));
	myTerrain->addChild(cossbowHunterTower);
	this->removeTower();
}

void SimpleArrowTowerlvl3::update2()
{
	auto totemTower = TotemTower::create();
	totemTower->setMyTerrain(myTerrain);
	totemTower->setTag(myTerrain->getTag());
	totemTower->setPosition(Point(0,20));
	myTerrain->addChild(totemTower);
	this->removeTower();
}