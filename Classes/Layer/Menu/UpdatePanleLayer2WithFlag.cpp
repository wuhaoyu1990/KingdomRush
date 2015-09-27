#include "UpdatePanleLayer2WithFlag.h"
#include "GameManager.h"
#include "BaseBuildIcon.h"
#include "TouchLayer.h"
#include "BaseMap.h"

USING_NS_CC;

UpdatePanleLayer2WithFlag* UpdatePanleLayer2WithFlag::createPanle(int icon1,int icon2,int money1,int money2)
{
    auto updatePanleLayer2WithFlag = new UpdatePanleLayer2WithFlag();
 
    if (updatePanleLayer2WithFlag && updatePanleLayer2WithFlag->initWithIcons(icon1,icon2,money1,money2))
    {
        updatePanleLayer2WithFlag->autorelease();
        return updatePanleLayer2WithFlag;
    }
    CC_SAFE_DELETE(updatePanleLayer2WithFlag);
    return NULL;
}


bool UpdatePanleLayer2WithFlag::initWithIcons(int icon1,int icon2,int money1,int money2)
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
	updateIcon1 = BaseBuildIcon::createIcon(icon1,money1);
	updateIcon1->setPosition(Point(planesprite->getContentSize().width/4 + 20,planesprite->getContentSize().height/4+30));
	updateIcon1->setVisible(false);
	updateIcon1->setTag(1);
	addChild(updateIcon1);

	updateIcon2 = BaseBuildIcon::createIcon(icon2,money2);
	updateIcon2->setPosition(Point(-planesprite->getContentSize().width/4 - 20,planesprite->getContentSize().height/4+30));
	updateIcon2->setVisible(false);
	updateIcon2->setTag(2);
	addChild(updateIcon2);

	sellIcon = SellIcon::create();
	sellIcon->setPosition(Point(0,-planesprite->getContentSize().height/2));
	sellIcon->setVisible(false);
	sellIcon->setTag(3);
	addChild(sellIcon);
	couldUpdate1 = true;
	couldUpdate2 = true;
	lock1 = Sprite::createWithSpriteFrameName("main_icons_0014.png");
	lock1->setPosition(Point(0,planesprite->getContentSize().height/2));
	addChild(lock1);

	lock2 = Sprite::createWithSpriteFrameName("main_icons_0014.png");
	lock2->setPosition(Point(0,planesprite->getContentSize().height/2));
	addChild(lock2);
	lock1->setVisible(false);
	lock2->setVisible(false);

	flag = Sprite::createWithSpriteFrameName("sub_icons_0001.png");
	flag->setPosition(Point(planesprite->getContentSize().width/4 + 15 ,-planesprite->getContentSize().height/3 + 5));
	flag->setVisible(false);
	flag->setTag(4);
	addChild(flag);

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
	return true;
}

void UpdatePanleLayer2WithFlag::inAnimation()
{
	SoundManager::playTowerMenu();
	planesprite->runAction(Sequence::create(ScaleTo::create(0.1f,1.0f,1.0f),
		CallFuncN::create(CC_CALLBACK_0(UpdatePanleLayer2WithFlag::addIcons,this)),
		NULL));	
}

void UpdatePanleLayer2WithFlag::addIcons()
{	
	flag->setVisible(true);
	sellIcon->setVisible(true);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(UpdatePanleLayer2WithFlag::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(UpdatePanleLayer2WithFlag::onTouchEnded, this);
 
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, sellIcon);
	if(couldUpdate1){
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), updateIcon1);
		updateIcon1->setVisible(true);
		updateIcon1->setUpdateMoney(tower->getUpdateMoney());
	}else{
		lock1->setVisible(true);
	}
	if(couldUpdate2){
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), updateIcon2);
		updateIcon2->setVisible(true);
		updateIcon2->setUpdateMoney(tower->getUpdateMoney());
	}else{
		lock2->setVisible(true);
	}
}

bool UpdatePanleLayer2WithFlag::onTouchBegan(Touch *touch, Event *event)
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
				switch (target->getTag())
				{
				case(1):
					SoundManager::playTowerUpdate();
					GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY-tower->getUpdateMoney();
					tower->update1();
					break;
				case(2):
					SoundManager::playTowerUpdate();
					GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY-tower->getUpdateMoney();
					tower->update2();
					break;
				case(3)://售出
					SoundManager::playTowerSell();
					GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY+ (tower->getBuildMoney()/2);
					tower->sellTower();
					break;
				}
				this->setVisible(false);
				isBuilt = true;
			}
		}else{//第一次按下
			updateIcon1->setNotSelected();
			updateIcon2->setNotSelected();
			sellIcon->setNotSelected();
			target->setSelected();//设置为选中状态
			switch (target->getTag())
			{
				case(1)://
					static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(ASSASSIN);
					break;
				case(2)://
					static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(TEMPLAR);
					break;
			}
		}
        return true;
    }
    return false;
}

void UpdatePanleLayer2WithFlag::onTouchEnded(Touch* touch, Event* event)
{
	if(isBuilt)
	{
		removeFromParent();
	}
}
