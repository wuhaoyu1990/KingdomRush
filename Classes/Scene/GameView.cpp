#include "GameView.h"
#include "TransitionGame.h"
#include "WelcomeScene.h"
#include "MapFlag.h"
#include "Road.h"
#include "GameViewMenu.h"
#include "GameManager.h"
#include "RespirationSprite.h"
#include "SoundManager.h"

USING_NS_CC;

Scene* GameView::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GameView::create();

	auto menuLayer = GameViewMenu::create();

    scene->addChild(layer);
	scene->addChild(menuLayer);

    return scene;
}

bool GameView::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	instance = GameManager::getInstance();

	//下行测试用
	//UserDefault::getInstance()->setIntegerForKey(instance->LEVELX_DOWNCOUNT,0);

	winSize = Director::getInstance()->getWinSize();
	bgSprite = Sprite::createWithSpriteFrameName("MapBackground.png");
	bgSprite->setAnchorPoint(Vec2::ZERO);
	bgSprite->setPosition(Vec2::ZERO);

	mapFlagPointVector.push_back(Point(375,775));
	mapFlagPointVector.push_back(Point(495,735));
	mapFlagPointVector.push_back(Point(510,620));
	mapFlagPointVector.push_back(Point(370,575));
	mapFlagPointVector.push_back(Point(205,505));
	mapFlagPointVector.push_back(Point(455,305));
	mapFlagPointVector.push_back(Point(690,420));
	mapFlagPointVector.push_back(Point(855,254));
	mapFlagPointVector.push_back(Point(1020,340));
	mapFlagPointVector.push_back(Point(934,490));
	mapFlagPointVector.push_back(Point(830,560));
	mapFlagPointVector.push_back(Point(795,710));
	mapFlagPointVector.push_back(Point(910,770));
	mapFlagPointVector.push_back(Point(1015,770));

	addChild(bgSprite);
	//添加道路
	addRoad();
	//添加旗帜
	addMapFlag();
	

	//this->setPosition(Point(0,winSize.height-bgSprite->getContentSize().height));

	int newReady = UserDefault::getInstance()->getIntegerForKey(instance->LEVELX_NEWDOWN,0);

	Point location = Point();
	location.x = winSize.width/2 - mapFlagPointVector.at(newReady).x;
	location.y = winSize.height/2 - mapFlagPointVector.at(newReady).y;
	auto bgSpriteCurrSize = bgSprite->getBoundingBox().size;
	location.x = MIN(location.x,0);
    location.x = MAX(location.x, -bgSpriteCurrSize.width + winSize.width);
    location.y = MIN(location.y,0);
    location.y = MAX(location.y, -bgSpriteCurrSize.height + winSize.height);
	this->setPosition(location);

	

	auto listener = EventListenerTouchAllAtOnce::create();
	// 2 绑定触摸事件
	listener->onTouchesBegan = CC_CALLBACK_2(GameView::onTouchesBegan, this);// 触摸开始时触发
	listener->onTouchesMoved = CC_CALLBACK_2(GameView::onTouchesMoved, this);// 触摸移动时触发
	// 3 添加监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, bgSprite);

	auto listenerkeyPad = EventListenerKeyboard::create();  
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(GameView::onKeyReleased, this);  
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this); 
	SoundManager::playGameTheme1();
    return true;
}

void GameView::onEnterTransitionDidFinish()
{
	int newReady = UserDefault::getInstance()->getIntegerForKey(instance->LEVELX_NEWDOWN,0);
	if(newReady<=12){//最多13关
		if(UserDefault::getInstance()->getIntegerForKey(instance->SLOTX_DOWNCOUNT,0)!=newReady){
			UserDefault::getInstance()->setIntegerForKey(instance->SLOTX_DOWNCOUNT,newReady);
			mapFlagVector.at(newReady-1)->changeType(0);
			auto sequence = Sequence::create(
				CallFuncN::create(CC_CALLBACK_0(MapFlag::startSuccessAnimation, mapFlagVector.at(newReady-1)))
				,CallFuncN::create(CC_CALLBACK_0(Road::buildRoadAnimation, road,newReady-1))
				,DelayTime::create(1.5f)
				,CallFuncN::create(CC_CALLBACK_0(GameView::addNewMapFlag,this ,newReady))
				,NULL);
			runAction(sequence);
		}
	}
}

void GameView::addNewMapFlag(int num)
{
	auto mapFlag = MapFlag::createWithLevel(num);
	mapFlag->setPosition(mapFlagPointVector.at(num));
	addChild(mapFlag);
	mapFlagVector.pushBack(mapFlag);
	mapFlag->startDropdownAnimation();
}

void GameView::addRoad()
{
	road = Road::create();
	road->setPosition(Point(635,500));
	addChild(road);
}

void GameView::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
	if(touches.size() == 1)        // 单点进行移动
    {
        // 单点时，touches中只有一个Touch对象，所以通过touches[0]就可以得到触摸对象
        auto touch = touches[0];
        // 计算滑动过程中的滑动增量
        auto diff = touch->getDelta();       
        // 得到当前bgSprite的位置
        auto currentPos = this->getPosition();
        // 得到滑动后bgSprite应该所在的位置
        auto pos = currentPos + diff;
        // 得到此刻bgSprite的尺寸
        auto bgSpriteCurrSize = bgSprite->getBoundingBox().size;
 
        //边界控制，约束pos的位置
        pos.x = MIN(pos.x, bgSpriteCurrSize.width * bgSprite->getAnchorPoint().x);
        pos.x = MAX(pos.x, -bgSpriteCurrSize.width + winSize.width + bgSpriteCurrSize.width * bgSprite->getAnchorPoint().x);
        pos.y = MIN(pos.y, bgSpriteCurrSize.height * bgSprite->getAnchorPoint().y);
        pos.y = MAX(pos.y, -bgSpriteCurrSize.height + winSize.height + bgSpriteCurrSize.height * bgSprite->getAnchorPoint().y);

        this->setPosition(pos);
	
    }
}

void GameView::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event)
{

}

void GameView::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	if(keycode==EventKeyboard::KeyCode::KEY_BACK)
	{
		auto scene = WelcomeScene::createScene();
		Director::getInstance()->replaceScene(TransitionGame::create(2.0f,scene));
	}
}

void GameView::addMapFlag()
{
	int count = UserDefault::getInstance()->getIntegerForKey(instance->SLOTX_DOWNCOUNT,0);
	for(int i=0;i<= count;i++)
	{
		auto mapFlag = MapFlag::createWithLevel(i);
		mapFlag->setPosition(mapFlagPointVector.at(i));
		mapFlagVector.pushBack(mapFlag);
		if(i == count)
		{
			mapFlag->setStarClose();
		}
		addChild(mapFlag);
	}
	if(UserDefault::getInstance()->getIntegerForKey(instance->LEVELX_NEWDOWN,0)==0){
		auto respirationSprite = RespirationSprite::createRespirationSprite("mapBalloon_starthere.png");
		respirationSprite->setPosition(Point(375,855));
		addChild(respirationSprite);
	}
}