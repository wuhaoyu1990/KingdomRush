#include "UpdatePanleLayerWithFlag.h"
#include "GameManager.h"
#include "BaseBuildIcon.h"
#include "TouchLayer.h"
#include "BaseMap.h"

USING_NS_CC;

bool UpdatePanleLayerWithFlag::init()
{
    if ( !Layer::init() )
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

	flag = Sprite::createWithSpriteFrameName("sub_icons_0001.png");
	flag->setPosition(Point(planesprite->getContentSize().width/4 + flag->getContentSize().width/2 ,-planesprite->getContentSize().height/3.2));
	flag->setVisible(false);
	flag->setTag(3);
	addChild(flag);

	couldUpdate = true;
	lock = Sprite::createWithSpriteFrameName("main_icons_0014.png");
	lock->setPosition(Point(0,planesprite->getContentSize().height/2));
	addChild(lock);
	lock->setVisible(false);
	return true;
}

void UpdatePanleLayerWithFlag::showTowerInfo()
{
	switch (tower->getTowerType())
	{
	case(BARAACKS_1):
		static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(BARAACKS_2);
		break;
	case(BARAACKS_2):
		static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(BARAACKS_3);
		break;
	default:
		break;
	}
}

void UpdatePanleLayerWithFlag::inAnimation()
{
	SoundManager::playTowerMenu();
	planesprite->runAction(Sequence::create(
		ScaleTo::create(0.1f,1.0f,1.0f),
		CallFuncN::create(CC_CALLBACK_0(UpdatePanleLayerWithFlag::addIcons,this)),
		NULL));	
}

void UpdatePanleLayerWithFlag::addIcons()
{	
	sellIcon->setVisible(true);
	flag->setVisible(true);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(UpdatePanleLayerWithFlag::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(UpdatePanleLayerWithFlag::onTouchEnded, this);
 
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, sellIcon);
	if(couldUpdate){
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), updateIcon);
		updateIcon->setVisible(true);
		updateIcon->setUpdateMoney(tower->getUpdateMoney());
	}else{
		lock->setVisible(true);
	}
	auto flaglistener = EventListenerTouchOneByOne::create();
	flaglistener->onTouchBegan = [&](Touch* touch, Event* event){
		
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Point locationInNode = target->convertTouchToNodeSpace(touch);

		Size size = target->getContentSize();
		Rect rect = Rect(0, 0, size.width, size.height);
		if (rect.containsPoint(locationInNode))
		{  	
			return true;  
		}  
		return false;
	};
	flaglistener->onTouchEnded = [&](Touch* touch, Event* event){
		static_cast<TouchLayer*>(this->getParent())->tower = this->getTower();
		static_cast<TouchLayer*>(this->getParent())->setRallyFlagTouchShield();
		tower->isUpdateMenuShown = false;
		this->removeFromParent();
	};
	flaglistener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(flaglistener,flag);

}

bool UpdatePanleLayerWithFlag::onTouchBegan(Touch *touch, Event *event)
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
			showTowerInfo();
			updateIcon->setNotSelected();
			sellIcon->setNotSelected();
			target->setSelected();//设置为选中状态
		}
        return true;
    }
    return false;
}

void UpdatePanleLayerWithFlag::onTouchEnded(Touch* touch, Event* event)
{
	if(isBuilt)
	{
		removeFromParent();
	}
}
