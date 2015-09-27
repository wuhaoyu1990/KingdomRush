#include "SimpleMageTowerlvl3.h"
#include "ArchMageTower.h"
#include "UpdatePanleLayer2.h"
#include "BaseMap.h"
#include "GameManager.h"
#include "MageBolt.h"
#include "NecromancerTower.h"
#include "ArchMageTower.h"

bool SimpleMageTowerlvl3::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setTowerType(MAGE_3);
	setLevel(3);
	addTerrain();
	initTower(3);
	setListener();
	setScope(250.0f);
	setUpdateMoney(230);
	setBuildMoney(500);
	isUpdateMenuShown = false;
	schedule(schedule_selector(SimpleMageTowerlvl3::shoot), 2.0f);
	SoundManager::playMageTower3Ready();
	return true;
}
void SimpleMageTowerlvl3::updateTower()
{
	auto ArchMageTower = ArchMageTower::create();
	ArchMageTower->setMyTerrain(myTerrain);
	ArchMageTower->setTag(myTerrain->getTag());
	ArchMageTower->setPosition(Point(0,20));
	myTerrain->addChild(ArchMageTower);
	this->removeFromParent();
}


void SimpleMageTowerlvl3::showUpdateMenu()
{
	auto updatePanleLayer = UpdatePanleLayer2::createPanle(21,22,230,230);
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
Bullet* SimpleMageTowerlvl3::MageTowerBullet()
{
	auto bullet = MageBolt::create();
	bullet->setPosition(Point(10,45));
	bullet->setMaxForce(60);
	this->getParent()->addChild(bullet);
    return bullet;
}

void SimpleMageTowerlvl3::update1()
{
	auto necromancerTower = NecromancerTower::create();
	necromancerTower->setMyTerrain(myTerrain);
	necromancerTower->setTag(myTerrain->getTag());
	necromancerTower->setPosition(Point(0,20));
	myTerrain->addChild(necromancerTower);
	this->removeTower();
}

void SimpleMageTowerlvl3::update2()
{
	auto archMageTower = ArchMageTower::create();
	archMageTower->setMyTerrain(myTerrain);
	archMageTower->setTag(myTerrain->getTag());
	archMageTower->setPosition(Point(0,20));
	myTerrain->addChild(archMageTower);
	this->removeTower();
}