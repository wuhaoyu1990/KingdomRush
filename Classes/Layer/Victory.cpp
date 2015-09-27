#include "Victory.h"
#include "TransitionGame.h"
#include "GameView.h"
#include "GameScene.h"
#include "GameManager.h"

USING_NS_CC;

Victory* Victory::createVictory(int star,int gem)
{
    auto layer = Victory::create();  
	layer->initVictory(star,gem);
    return layer;
}

bool Victory::initVictory(int star,int gem)
{
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance() -> getVisibleSize();
    auto color = LayerColor::create(Color4B(0, 0, 0, 60), visibleSize.width, visibleSize.height);
    addChild(color,-1);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch* touch, Event* event){
		return true;
	};
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,color);

	position.x=visibleSize.width/2;
	position.y=visibleSize.height*0.7;

	

	auto ContinueSpriteOff=Sprite::createWithSpriteFrameName("button_continue_0001.png");
	auto ContinueSpriteOn=Sprite::createWithSpriteFrameName("button_continue_0002.png");
	auto RestartSpriteOff=Sprite::createWithSpriteFrameName("button_restart_0001.png");
	auto RestartSpriteOn=Sprite::createWithSpriteFrameName("button_restart_0002.png");
	

	ContinueMenuItem = MenuItemSprite::create(ContinueSpriteOff,ContinueSpriteOn,CC_CALLBACK_1(Victory::OnContinueTouch,this));
	RestartMenuItem=MenuItemSprite::create(RestartSpriteOff,RestartSpriteOn,CC_CALLBACK_1(Victory::OnRestartTouch,this));
	ContinueMenuItem->setPosition(position.x,position.y);
	ContinueMenuItem->setVisible(false);
	RestartMenuItem->setPosition(position.x,position.y-240);
	RestartMenuItem->setVisible(false);

	auto menu = Menu::create(RestartMenuItem,ContinueMenuItem,NULL);   
	menu->setPosition(Vec2::ZERO);
    addChild(menu,1);    
	switch (star)
	{
	case(1):
		VictorySprite = Sprite::createWithSpriteFrameName("victoryBadges_0002.png");
		break;
	case(2):
		VictorySprite = Sprite::createWithSpriteFrameName("victoryBadges_0002.png");
		break;
	case(3):
		VictorySprite = Sprite::createWithSpriteFrameName("victoryBadges_0002.png");
		break;
	case(4):
		VictorySprite = Sprite::createWithSpriteFrameName("victoryBadges_0003.png");
		break;
	case(5):
		VictorySprite = Sprite::createWithSpriteFrameName("victoryBadges_0004.png");
		break;
	default:
		VictorySprite = Sprite::createWithSpriteFrameName("victoryBadges_0001.png");
		break;
	}
	VictorySprite->setPosition(position);
	VictorySprite->setScale(0.2f);
	addChild(VictorySprite,1);

	win_Gnome = Sprite::createWithSpriteFrameName("win_Gnome.png");
	win_Gnome->setPosition(Director::getInstance()->getVisibleSize().width/2,Director::getInstance()->getVisibleSize().height/2+100);
	addChild(win_Gnome,0);
	auto one = Sprite::createWithSpriteFrameName(String::createWithFormat("win_Gnome_Numbers_000%d.png",gem%10)->getCString());
	auto ten = Sprite::createWithSpriteFrameName(String::createWithFormat("win_Gnome_Numbers_000%d.png",(gem/10)%10)->getCString());
	ten->setPosition(Point(160,60));
	one->setPosition(Point(180,50));
	win_Gnome->addChild(one);
	win_Gnome->addChild(ten);
	win_Gnome->setVisible(false);
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> aFrames;

	for (int len = 1;len <= 9; len++)
	{
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("victoryStars_star_00%02d.png",len)->getCString());
		if(frame!=nullptr)
			aFrames.pushBack(frame);
	}
	AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(aFrames,0.04f),"victory_star");

	auto Sequence=Sequence::create(CallFuncN::create(CC_CALLBACK_0(Victory::VSpriteAnimation, this)),
								   DelayTime::create(0.5f),
								   CallFuncN::create(CC_CALLBACK_0(Victory::CItemAnimation, this)),
								   DelayTime::create(0.5f),
								   CallFuncN::create(CC_CALLBACK_0(Victory::RItemAnimation, this)),
								   DelayTime::create(0.5f),
								   CallFuncN::create(CC_CALLBACK_0(Victory::showStar, this,star)),
								   CallFuncN::create(CC_CALLBACK_0(Victory::showGems, this)),
								   NULL);
	runAction(Sequence);
	SoundManager::playQuestCompleted();



    return true;
}

void Victory::showGems()
{
	win_Gnome->setVisible(true);
	win_Gnome->runAction(MoveBy::create(1.0f,Point(300,0)));
}

void Victory::VSpriteAnimation()
{
	VictorySprite->runAction(ScaleTo::create(0.5f,1.0f,1.0f));
}
void Victory::CItemAnimation()
{
	ContinueMenuItem->setVisible(true);
	auto move = MoveTo::create(0.5f,Point( position.x,position.y-240));
	ContinueMenuItem->runAction(move);
}
void Victory::RItemAnimation()
{
	RestartMenuItem->setVisible(true);
	auto move = MoveTo::create(0.5f,Point( position.x,position.y-335));
	RestartMenuItem->runAction(move);

}
void Victory::showStar(int star)
{
	switch (star)
	{
	case(1):{
		auto star = Sprite::createWithSpriteFrameName("victoryStars_star_0001.png");
		star->setPosition(Point(position.x,position.y-100));
		star->setScale(0.0f);
		addChild(star,3);
		star->runAction(ScaleTo::create(0.5f,1,1));
		}
		break;
	case(2):{
		auto star1 = Sprite::createWithSpriteFrameName("victoryStars_star_0001.png");
		star1->setPosition(Point(position.x -25,position.y-100));
		star1->setScale(0.0f);
		addChild(star1,3);
		star1->runAction(ScaleTo::create(0.5f,1,1));
		auto star2 = Sprite::createWithSpriteFrameName("victoryStars_star_0001.png");
		star2->setPosition(Point(position.x + 25,position.y-100));
		star2->setScale(0.0f);
		addChild(star2,3);
		star2->runAction(Sequence::create(DelayTime::create(0.5f),ScaleTo::create(0.5f,1,1),NULL));
		}
		break;
	case(3):{
		auto star1 = Sprite::createWithSpriteFrameName("victoryStars_star_0001.png");
		star1->setPosition(Point(position.x - 50,position.y-100));
		star1->setScale(0.0f);
		addChild(star1,3);
		star1->runAction(ScaleTo::create(0.5f,1,1));
		auto star2 = Sprite::createWithSpriteFrameName("victoryStars_star_0001.png");
		star2->setPosition(Point(position.x ,position.y-100));
		star2->setScale(0.0f);
		addChild(star2,3);
		star2->runAction(Sequence::create(DelayTime::create(0.5f),ScaleTo::create(0.5f,1,1),NULL));
		auto star3 = Sprite::createWithSpriteFrameName("victoryStars_star_0001.png");
		star3->setPosition(Point(position.x + 50,position.y-100));
		star3->setScale(0.0f);
		addChild(star3,3);
		star3->runAction(Sequence::create(DelayTime::create(1.0f),ScaleTo::create(0.5f,1,1),NULL));
		}
		break;
	default:
		break;
	}
	
}

void Victory::OnContinueTouch(Ref* pSpender)
{
	Director::getInstance()->replaceScene(TransitionGame::create(1.0f, GameView::createScene()));

}
void Victory::OnRestartTouch(Ref* pSpender)
{
	Director::getInstance()->replaceScene(TransitionGame::create(1.0f, GameScene::playGame(level,difficult)));
}