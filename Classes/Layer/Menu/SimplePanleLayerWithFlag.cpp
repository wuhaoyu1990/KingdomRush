#include "SimplePanleLayerWithFlag.h"
#include "GameManager.h"
#include "BaseBuildIcon.h"
#include "TouchLayer.h"

USING_NS_CC;

bool SimplePanleLayerWithFlag::init()
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

	return true;
}

void SimplePanleLayerWithFlag::inAnimation()
{
	SoundManager::playTowerMenu();
	planesprite->runAction(Sequence::create(ScaleTo::create(0.1f,1.0f,1.0f),
		CallFuncN::create(CC_CALLBACK_0(SimplePanleLayerWithFlag::addIcons,this)),
		NULL));	
}

void SimplePanleLayerWithFlag::addIcons()
{	
	sellIcon->setVisible(true);
	flag->setVisible(true);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(SimplePanleLayerWithFlag::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(SimplePanleLayerWithFlag::onTouchEnded, this);
 
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, sellIcon);

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



bool SimplePanleLayerWithFlag::onTouchBegan(Touch *touch, Event *event)
{
	auto target = static_cast<BaseBuildIcon*>(event->getCurrentTarget());
    Point locationInNode = target->convertTouchToNodeSpace(touch);
    Size size = target->baseIcon->getContentSize();
	Rect rect = Rect(0-size.width/2, 0-size.height/2, size.width, size.height);
    if (rect.containsPoint(locationInNode))
    {
		if(target->getIsSelected())//如果已经选中（第二次按下）
		{
			SoundManager::playTowerSell();
			GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY+ (tower->getBuildMoney()/2);
			tower->sellTower();
			this->setVisible(false);
			isBuilt = true;
		}else{//第一次按下
			target->setSelected();//设置为选中状态
		}
        return true;
    }
    return false;
}

void SimplePanleLayerWithFlag::onTouchEnded(Touch* touch, Event* event)
{
	if(isBuilt)
	{
		removeFromParent();
	}
}
