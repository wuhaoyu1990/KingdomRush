#include "SimpleMageTowerlvl2.h"
#include "SimpleMageTowerlvl3.h"
#include "UpdatePanleLayer.h"
#include "BaseMap.h"
#include "GameManager.h"
#include "MageBolt.h"

bool SimpleMageTowerlvl2::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setTowerType(MAGE_2);
	setLevel(2);
	addTerrain();
	initTower(2);
	setListener();
	setScope(180.0f);
	setUpdateMoney(240);
	setBuildMoney(260);
	isUpdateMenuShown = false;
	schedule(schedule_selector(SimpleMageTowerlvl2::shoot), 2.0f);
	SoundManager::playMageTower2Ready();
	return true;
}

void SimpleMageTowerlvl2::updateTower()
{
	auto simpleMageTowerlvl3 = SimpleMageTowerlvl3::create();
	simpleMageTowerlvl3->setMyTerrain(myTerrain);
	simpleMageTowerlvl3->setTag(myTerrain->getTag());
	simpleMageTowerlvl3->setPosition(Point(0,20));
	myTerrain->addChild(simpleMageTowerlvl3);
	this->removeTower();
}

void SimpleMageTowerlvl2::showUpdateMenu()
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
Bullet* SimpleMageTowerlvl2::MageTowerBullet()
{
	auto bullet = MageBolt::create();
	bullet->setPosition(Point(10,45));
	bullet->setMaxForce(30);
	this->getParent()->addChild(bullet);
    return bullet;
}