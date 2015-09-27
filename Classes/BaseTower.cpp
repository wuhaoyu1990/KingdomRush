#include "BaseTower.h"
#include "Terrain.h"
#include "TowerPanleLayer.h"
#include "BaseMap.h"
#include "GameManager.h"

BaseTower::BaseTower()
:isUpdateMenuShown(false)
{}

BaseTower::~BaseTower(){}

bool BaseTower::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	isUpdateMenuShown = false;
	return true;
}

bool BaseTower::onTouchBegan(Touch *touch, Event *event)
{
	return true;
}

void BaseTower::onTouchEnded(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());

	Point locationInNode = target->convertTouchToNodeSpace(touch);

	Size size = target->getContentSize();
	Rect rect = Rect(0, 0, size.width, size.height);
	if (rect.containsPoint(locationInNode))
	{  	
		static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(getTowerType());
		if(isUpdateMenuShown)
		{
			hideUpdateMenu();
		}else{
			showUpdateMenu();
		}
	}else{
		hideUpdateMenu();
	}
}

void BaseTower::showTowerInfo()
{

}

void BaseTower::sellTower()
{
	static_cast<Terrain*>(this->getParent())->terrain->setVisible(true);
	removeTower();
}

void BaseTower::removeTower()
{
	static_cast<BaseMap*>(this->getParent()->getParent())->playerState->removeTowerInfo();
	static_cast<Terrain*>(this->getParent())->smokeEffect();
	this->unscheduleAllCallbacks();
	this->removeAllChildren();
	this->removeFromParent();
}

void BaseTower::setListener()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(BaseTower::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(BaseTower::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,terrain);
}

void BaseTower::checkNearestMonster()
{
    auto instance = GameManager::getInstance();
    auto monsterVector = instance->monsterVector;
    
	auto currMinDistant = this->scope;
    
	BaseMonster *monsterTemp = NULL;
	for(int i = 0; i < monsterVector.size(); i++)
	{
		auto monster = monsterVector.at(i);
		double distance = this->getParent()->getPosition().getDistance(monster->baseSprite->getPosition());

		if (distance < currMinDistant && monster->getAttackByTower()) {
			currMinDistant = distance;
            monsterTemp = monster;
		}
	}
    nearestMonster = monsterTemp;
}

void BaseTower::hideUpdateMenu()
{
	static_cast<BaseMap*>(this->getParent()->getParent())->mTouchLayer->removeChildByTag(getTag()+100);
	isUpdateMenuShown = false;
}