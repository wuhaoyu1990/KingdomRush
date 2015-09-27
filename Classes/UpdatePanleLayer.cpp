#include "UpdatePanleLayer.h"
#include "GameManager.h"
#include "BaseBuildIcon.h"
#include "BaseMap.h"

USING_NS_CC;

bool UpdatePanleLayer::init()
{
    if ( !Sprite::init() )
    {
        return false;
    }
	isBuilt = false;

	planesprite = Sprite::createWithSpriteFrameName("gui_ring.png");
	planesprite->setPosition(Point(0, 0));
	planesprite->setScale(0.5f);
	addChild(planesprite);
	updateIcon = BaseBuildIcon::createIcon(5,0);
	updateIcon->setPosition(Point(0,planesprite->getContentSize().height/2));
	updateIcon->setVisible(false);
	updateIcon->setTag(1);
	addChild(updateIcon);

	sellIcon = SellIcon::create();
	sellIcon->setPosition(Point(0,-planesprite->getContentSize().height/2));
	sellIcon->setVisible(false);
	sellIcon->setTag(2);
	addChild(sellIcon);
	couldUpdate = true;
	lock = Sprite::createWithSpriteFrameName("main_icons_0014.png");
	lock->setPosition(Point(0,planesprite->getContentSize().height/2));
	addChild(lock);
	lock->setVisible(false);
	return true;
}

void UpdatePanleLayer::inAnimation()
{
	SoundManager::playTowerMenu();
	planesprite->runAction(Sequence::create(ScaleTo::create(0.1f,1.0f,1.0f),
		CallFuncN::create(CC_CALLBACK_0(UpdatePanleLayer::addIcons,this)),
		NULL));	
}

void UpdatePanleLayer::addIcons()
{	
	thisLvlCircle = Circle::create();
	nextLvlCircle = Circle::create();

	thisLvlCircle->setScale(tower->getScope()/160.0f);
	addChild(thisLvlCircle,-1);
	nextLvlCircle->setScale((tower->getScope()+20)/160.0f);
	addChild(nextLvlCircle,-1);
	nextLvlCircle->setVisible(false);
	sellIcon->setVisible(true);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(UpdatePanleLayer::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(UpdatePanleLayer::onTouchEnded, this);
 
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, sellIcon);
	if(couldUpdate){
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), updateIcon);
		updateIcon->setVisible(true);
		updateIcon->setUpdateMoney(tower->getUpdateMoney());
	}else{
		lock->setVisible(true);
	}

	
}

bool UpdatePanleLayer::onTouchBegan(Touch *touch, Event *event)
{
	auto target = static_cast<BaseBuildIcon*>(event->getCurrentTarget());
    Point locationInNode = target->convertTouchToNodeSpace(touch);
    Size size = target->baseIcon->getContentSize();
	Rect rect = Rect(0-size.width/2, 0-size.height/2, size.width, size.height);
    if (rect.containsPoint(locationInNode))
    {
		if(target->getIsSelected())//如果已经选中（第二次按下）
		{
			if(target->getIsAble())//如果钱够用
			{
				static_cast<BaseMap*>(this->getParent()->getParent())->playerState->removeTowerInfo();
				switch (target->getTag())
				{
				case(1)://升级
					SoundManager::playTowerUpdate();
					GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY-tower->getUpdateMoney();
					tower->updateTower();
					break;
				case(2)://售出
					SoundManager::playTowerSell();
					GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY+ (tower->getBuildMoney()/2);
					tower->sellTower();
					break;
				}
				this->setVisible(false);
				isBuilt = true;
			}
		}else{//第一次按下
			static_cast<BaseMap*>(this->getParent()->getParent())->playerState->removeTowerInfo();
			updateIcon->setNotSelected();
			sellIcon->setNotSelected();
			target->setSelected();//设置为选中状态
			switch (target->getTag())
				{
				case(1)://升级
					showTowerInfo();
					nextLvlCircle->setVisible(true);
					break;
				case(2)://售出
					nextLvlCircle->setVisible(false);
					break;
				}
		}
        return true;
    }
    return false;
}

void UpdatePanleLayer::showTowerInfo()
{
	switch (tower->getTowerType())
	{
	case(ARCHER_1):
		static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(ARCHER_2);
		break;
	case(ARCHER_2):
		static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(ARCHER_3);
		break;
	case(MAGE_1):
		static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(MAGE_2);
		break;
	case(MAGE_2):
		static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(MAGE_3);
		break;
	case(ARTILLERY_1):
		static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(ARTILLERY_2);
		break;
	case(ARTILLERY_2):
		static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(ARTILLERY_3);
		break;
	default:
		break;
	}
}

void UpdatePanleLayer::onTouchEnded(Touch* touch, Event* event)
{
	if(isBuilt)
	{
		removeFromParent();
	}
}
