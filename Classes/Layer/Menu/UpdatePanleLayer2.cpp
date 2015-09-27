#include "UpdatePanleLayer2.h"
#include "GameManager.h"
#include "BaseBuildIcon.h"
#include "TouchLayer.h"
#include "BaseMap.h"

USING_NS_CC;

UpdatePanleLayer2* UpdatePanleLayer2::createPanle(int icon1,int icon2,int money1,int money2)
{
    auto updatePanleLayer2 = new UpdatePanleLayer2();
 
    if (updatePanleLayer2 && updatePanleLayer2->initWithIcons(icon1,icon2,money1,money2))
    {
        updatePanleLayer2->autorelease();
        return updatePanleLayer2;
    }
    CC_SAFE_DELETE(updatePanleLayer2);
    return NULL;
}


bool UpdatePanleLayer2::initWithIcons(int icon1,int icon2,int money1,int money2)
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
	lock1->setPosition(Point(planesprite->getContentSize().width/4 + 20,planesprite->getContentSize().height/4+30));
	addChild(lock1);

	lock2 = Sprite::createWithSpriteFrameName("main_icons_0014.png");
	lock2->setPosition(Point(-planesprite->getContentSize().width/4 - 20,planesprite->getContentSize().height/4+30));
	addChild(lock2);
	lock1->setVisible(false);
	lock2->setVisible(false);

	return true;
}

void UpdatePanleLayer2::inAnimation()
{
	SoundManager::playTowerMenu();
	planesprite->runAction(Sequence::create(
		ScaleTo::create(0.1f,1.0f,1.0f),
		CallFuncN::create(CC_CALLBACK_0(UpdatePanleLayer2::addIcons,this)),
		NULL));	
}

void UpdatePanleLayer2::addIcons()
{	
	thisLvlCircle = Circle::create();
	nextLvlCircle = Circle::create();

	thisLvlCircle->setScale(tower->getScope()/160.0f);
	addChild(thisLvlCircle,-1);
	nextLvlCircle->setScale((tower->getScope()+40)/160.0f);
	addChild(nextLvlCircle,-1);
	nextLvlCircle->setVisible(false);
	sellIcon->setVisible(true);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(UpdatePanleLayer2::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(UpdatePanleLayer2::onTouchEnded, this);
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

bool UpdatePanleLayer2::onTouchBegan(Touch *touch, Event *event)
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
				case(1):
					SoundManager::playTowerSell();
					GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY-tower->getUpdateMoney();
					tower->update1();
					break;
				case(2):
					SoundManager::playTowerUpdate();
					GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY-tower->getUpdateMoney();
					tower->update2();
					break;
				case(3)://售出
					SoundManager::playTowerUpdate();
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
					showTowerInfo_1();
					nextLvlCircle->setVisible(true);
					break;
				case(2)://
					showTowerInfo_2();
					nextLvlCircle->setVisible(true);
					break;
				case(3)://
					nextLvlCircle->setVisible(false);
					break;
				}
		}
        return true;
    }
    return false;
}

void UpdatePanleLayer2::onTouchEnded(Touch* touch, Event* event)
{
	if(isBuilt)
	{
		removeFromParent();
	}
}

void UpdatePanleLayer2::showTowerInfo_2()
{
	switch (tower->getTowerType())
	{
	case(ARCHER_3):
		static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(TOTEMTOWER);
		break;
	case(ARTILLERY_3):
		static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(MECHS);
		break;
	case(MAGE_3):
		static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(ARCHMAGE);
		break;
	default:
		break;
	}
}

void UpdatePanleLayer2::showTowerInfo_1()
{
	switch (tower->getTowerType())
	{
	case(ARCHER_3):
		static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(COSSBOW);
		break;
	case(ARTILLERY_3):
		static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(EARTHQUAKE);
		break;
	case(MAGE_3):
		static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(NEC);
		break;
	default:
		break;
	}
}