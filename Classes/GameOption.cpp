#include "GameOption.h"
#include "GameScene.h"
#include "TransitionGame.h"
#include "GameView.h"
#include "SoundManager.h"
#include "PlayerStateMenu.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

void ::GameOption::initOption()
{
	option = Sprite::create();
	auto chain_left = Sprite::createWithSpriteFrameName("options_chain.png");
	chain_left->setAnchorPoint(Point(1,0));
	chain_left->setPosition(Point(-190,200));
	option->addChild(chain_left);

	auto chain_right = Sprite::createWithSpriteFrameName("options_chain.png");
	chain_right->setAnchorPoint(Point(0,0));
	chain_right->setPosition(Point(190,200));
	option->addChild(chain_right);
	for(int j =-40;j<=40;j++)
	{
		/*auto mid_center = Sprite::createWithSpriteFrameName("options_tileMid_center.png");*/
		auto mid_center = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()
			->getSpriteFrameByName("options_tileMid_center.png"));
		mid_center->setPosition(Point(8.5*j,-56));
		option->addChild(mid_center);
	}
	for(int j =-40;j<=40;j++)
	{
		auto mid_center = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()
			->getSpriteFrameByName("options_tileMid_center.png"));
	/*	auto mid_center = Sprite::createWithSpriteFrameName("options_tileMid_center.png");*/
		mid_center->setPosition(Point(8.5*j,+56));
		option->addChild(mid_center);
	}
	for(int j =-7;j<=7;j++)
	{
		auto top_center = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()
			->getSpriteFrameByName("options_tileTop_center.png"));
		/*auto top_center = Sprite::createWithSpriteFrameName("options_tileTop_center.png");*/
		top_center->setPosition(Point(32*j,+161));
		option->addChild(top_center);
	}

	for(int j =-7;j<=7;j++)
	{
		auto top_center = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()
			->getSpriteFrameByName("options_tileTop_center.png"));
		/*auto top_center = Sprite::createWithSpriteFrameName("options_tileTop_center.png");*/
		top_center->setPosition(Point(32*j,-161));
		top_center->setFlippedY(true);
		option->addChild(top_center);
	}
	auto mid_left1 = Sprite::createWithSpriteFrameName("options_tileMid_left.png");
	mid_left1->setPosition(Point(-369,-56));
	option->addChild(mid_left1);
	auto mid_left2 = Sprite::createWithSpriteFrameName("options_tileMid_left.png");
	mid_left2->setPosition(Point(-369,56));
	option->addChild(mid_left2);
	auto mid_right1 = Sprite::createWithSpriteFrameName("options_tileMid_right.png"); 
	mid_right1->setPosition(Point(369,-56));
	option->addChild(mid_right1);
	auto mid_right2 = Sprite::createWithSpriteFrameName("options_tileMid_right.png"); 
	mid_right2->setPosition(Point(369,56));
	option->addChild(mid_right2);


	auto top_left1 = Sprite::createWithSpriteFrameName("options_tileTop_left.png");
	top_left1->setPosition(Point(-347,161));
	option->addChild(top_left1);

	auto top_left2 = Sprite::createWithSpriteFrameName("options_tileTop_left.png");
	top_left2->setFlippedY(true);
	top_left2->setPosition(Point(-347,-161));
	option->addChild(top_left2);

	auto top_right1 = Sprite::createWithSpriteFrameName("options_tileTop_left.png");
	top_right1->setPosition(Point(347,-161));
	top_right1->setFlippedX(true);
	top_right1->setFlippedY(true);
	option->addChild(top_right1);

	auto top_right2 = Sprite::createWithSpriteFrameName("options_tileTop_left.png");
	top_right2->setPosition(Point(347,161));
	top_right2->setFlippedX(true);
	option->addChild(top_right2);

	auto top_left_deco = Sprite::createWithSpriteFrameName("options_tileTop_deco.png");
	top_left_deco->setPosition(Point(220,161));
	option->addChild(top_left_deco);

	auto down_left_deco = Sprite::createWithSpriteFrameName("options_tileTop_deco.png");
	down_left_deco->setFlippedY(true);
	down_left_deco->setPosition(Point(220,-161));
	option->addChild(down_left_deco);

	auto top_right_deco = Sprite::createWithSpriteFrameName("options_tileTop_deco.png");
	top_right_deco->setFlippedX(true);
	top_right_deco->setPosition(Point(-220,161));
	option->addChild(top_right_deco);

	auto down_right_deco = Sprite::createWithSpriteFrameName("options_tileTop_deco.png");
	down_right_deco->setFlippedX(true);
	down_right_deco->setFlippedY(true);
	down_right_deco->setPosition(Point(-220,-161));
	option->addChild(down_right_deco);

	auto top_left_cut = Sprite::createWithSpriteFrameName("options_tileTop_cut.png");
	top_left_cut->setPosition(Point(-266,161));
	option->addChild(top_left_cut);

	auto down_left_cut = Sprite::createWithSpriteFrameName("options_tileTop_cut.png");
	down_left_cut->setFlippedY(true);
	down_left_cut->setPosition(Point(-266,-161));
	option->addChild(down_left_cut);

	auto top_right_cut = Sprite::createWithSpriteFrameName("options_tileTop_cut.png");
	top_right_cut->setFlippedX(true);
	top_right_cut->setPosition(Point(266,161));
	option->addChild(top_right_cut);

	auto down_right_cut = Sprite::createWithSpriteFrameName("options_tileTop_cut.png");
	down_right_cut->setFlippedX(true);
	down_right_cut->setFlippedY(true);
	down_right_cut->setPosition(Point(266,-161));
	option->addChild(down_right_cut);

	option->setPosition(Point(Director::getInstance()->getWinSize().width/2,Director::getInstance()->getWinSize().height/2+20));
	addChild(option);
}

void ::GameOption::initButton()
{
	auto close = MenuItemSprite::create(Sprite::createWithSpriteFrameName("options_close_0001.png"),
		Sprite::createWithSpriteFrameName("options_close_0002.png"));
	close->setCallback([&](Ref *pSender){
		SoundManager::playClickEffect();
		/*Director::getInstance()->resume();
		this->runAction(Sequence::create(
			MoveBy::create(0.2f,Point(0,500))
			,CallFuncN::create(CC_CALLBACK_0(Layer::removeFromParent, this))
			,NULL));*/
		static_cast<PlayerStateMenu*>(this->getParent())->removeGameOption();
		
	});
	close->setPosition(Point(337,156));

	auto restart = Sprite::createWithSpriteFrameName("options_buttons_0003.png");
	restart->setPosition(Point(-145,-100));
	restart->setTag(0);

	auto exit = Sprite::createWithSpriteFrameName("options_buttons_0001.png");
	exit->setPosition(Point(145,-100));
	exit->setTag(1);
	auto music_bak = Sprite::createWithSpriteFrameName("options_butBg_0001.png");
	music_bak->setPosition(Point(-200,50));

	auto effect_bak = Sprite::createWithSpriteFrameName("options_butBg_0001.png");
	effect_bak->setPosition(Point(0,50));

	auto vibration_bak = Sprite::createWithSpriteFrameName("options_butBg_0001.png");
	vibration_bak->setPosition(Point(200,50));

	auto music = Sprite::createWithSpriteFrameName("options_optButtons_0001.png");
	music->setPosition(Point(music_bak->getContentSize().width/2,music_bak->getContentSize().height/2));
	music->setTag(1);
	if(UserDefault::getInstance()->getIntegerForKey("backmusic",1)==0){//0表示禁止BGM，1表示开启
		addOff(music);
	}
	music_bak->addChild(music);

	auto effect = Sprite::createWithSpriteFrameName("options_optButtons_0003.png");
	effect->setPosition(Point(effect_bak->getContentSize().width/2,effect_bak->getContentSize().height/2));
	effect->setTag(2);
	if(UserDefault::getInstance()->getIntegerForKey("backeffect",1)==0){//0表示禁止BGM，1表示开启
		addOff(effect);	
	}
	effect_bak->addChild(effect);

	auto vibration = Sprite::createWithSpriteFrameName("options_optButtons_0005.png");
	vibration->setPosition(Point(vibration_bak->getContentSize().width/2,vibration_bak->getContentSize().height/2));
	vibration->setTag(3);
	vibration_bak->addChild(vibration);

	option->addChild(music_bak);
	option->addChild(effect_bak);
	option->addChild(vibration_bak);
	auto menu = Menu::create(close,NULL);
	menu->setPosition(Vec2::ZERO);
	option->addChild(menu);
	option->addChild(restart);
	option->addChild(exit);


	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch* touch, Event* event){
		
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Point locationInNode = target->convertTouchToNodeSpace(touch);

		Size size = target->getContentSize();
		Rect rect = Rect(0, 0, size.width, size.height);
		if (rect.containsPoint(locationInNode))
		{  	
			SoundManager::playClickEffect();
			target->setScale(0.9f);
			return true;  
		}  
		return false;
	};
	listener->onTouchEnded = [&](Touch* touch, Event* event){
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		target->setScale(1.0f);
		if(target->getChildrenCount() ==0 )
		{
			addOff(target);
			switch (target->getTag())
			{
			case(1):
				SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
				UserDefault::getInstance()->setIntegerForKey("backmusic",0);
				break;
			case(2):
				UserDefault::getInstance()->setIntegerForKey("backeffect",0);
				break;
			case(3):

				break;
			default:
				break;
			}
		}else{
			target->removeAllChildren();
			switch (target->getTag())
			{
			case(1):
				SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
				UserDefault::getInstance()->setIntegerForKey("backeffect",1);
				break;
			case(2):
				UserDefault::getInstance()->setIntegerForKey("backmusic",1);
				break;
			case(3):

				break;
			default:
				break;
			}
		}
	};
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,music);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),effect);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),vibration);

	auto listener2 = EventListenerTouchOneByOne::create();
	listener2->setSwallowTouches(true);
	listener2->onTouchBegan = CC_CALLBACK_2(GameOption::onTouchBegan, this);
	listener2->onTouchEnded = CC_CALLBACK_2(GameOption::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2,restart);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2->clone(),exit);
}

void GameOption::addOff(Sprite* target)
{
	auto off = Sprite::createWithSpriteFrameName("options_optButtons_off.png");
	off->setPosition(Point(95,85));
	target->addChild(off);
}

void GameOption::onTouchEnded(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	target->setScale(1.0f);
	switch (target->getTag())
	{
	case(0)://重新开始
	{
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(TransitionGame::create(1.0f, GameScene::playGame(level,difficult)));
	}
		break;
	case(1)://退出
	{
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(TransitionGame::create(1.0f, GameView::createScene()));
	}
		break;
	default:
		break;
	}
}

bool GameOption::onTouchBegan(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());

	Point locationInNode = target->convertTouchToNodeSpace(touch);

	Size size = target->getContentSize();
	Rect rect = Rect(0, 0, size.width, size.height);
	if (rect.containsPoint(locationInNode))
	{  	
		SoundManager::playClickEffect();
		target->setScale(0.9f);
		return true;  
	}  
	return false;
}

bool GameOption::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	
	initOption();
	initButton();
	//option->runAction(Sequence::create(
	//		MoveBy::create(0.2f,Point(0,-500))
	//		,CallFuncN::create(CC_CALLBACK_0(GameOption::pauseGame, this))
	//		,NULL));
	return true;
}

void GameOption::pauseGame()
{
	Director::getInstance()->pause();
}

void GameOption::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
    switch (keycode)
    {
	case EventKeyboard::KeyCode::KEY_BACK:   //返回键听
		SoundManager::playClickEffect();
		static_cast<PlayerStateMenu*>(this->getParent())->removeGameOption();
		
        break;
    case EventKeyboard::KeyCode::KEY_MENU:      //菜单监听
        break;
    case::EventKeyboard::KeyCode::KEY_HOME:
        break;
    default:
        break;
    }
}