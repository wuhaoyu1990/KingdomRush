#include "MapFlag.h"
#include "GameView.h"
#include "TransitionGame.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "Level1.h"
#include "GameScene.h"
#include "ChooseDifficulty.h"

MapFlag::~MapFlag(){}

MapFlag::MapFlag(){}

bool MapFlag::initWithLevel(int level)
{
	instance = GameManager::getInstance();
	setLevel(level);
	if (!Sprite::init())
	{
		return false;
	}
	switch (UserDefault::getInstance()->getIntegerForKey(String::createWithFormat(instance->LEVELX_STARNUM,getLevel())->getCString(),0))
	{
	case(0)://得星个数为0，为完成
		setType(0);
		flag = Sprite::createWithSpriteFrameName("mapFlag_0022.png");
		break;
	case(4)://得星个数为4
		setType(2);
		flag = Sprite::createWithSpriteFrameName("mapFlag_0112.png");
		break;
	case(5)://得星个数为5
		setType(3);
		wings = Sprite::createWithSpriteFrameName("mapFlag_wings_0015.png");
		addChild(wings);
		flag = Sprite::createWithSpriteFrameName("mapFlag_0112.png");
		break;
	default:
		setType(1);
		flag = Sprite::createWithSpriteFrameName("mapFlag_0094.png");
		break;
	}
	addChild(flag);
	initStar();
	addStar();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MapFlag::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(MapFlag::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,flag);
	
	return true;
}

void MapFlag::onTouchEnded(Touch* touch, Event* event)
{
	Director::getInstance()->pushScene(ChooseDifficulty::createSceneWithLevel(getLevel()));
	switch (type)
	{
		case(1):
			flag->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mapFlag_0094.png"));
			break;
		case(0):
			flag->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mapFlag_0022.png"));
			break;
		case(2)://得星个数为4
			flag->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mapFlag_0112.png"));
			break;
		case(3)://得星个数为5
			flag->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mapFlag_0112.png"));

			break;
		default:
			break;
	}
}

bool MapFlag::onTouchBegan(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());

	Point locationInNode = target->convertTouchToNodeSpace(touch);

	Size size = target->getContentSize();
	Rect rect = Rect(0, size.height/3, size.width, size.height/2);
	if (rect.containsPoint(locationInNode))
	{  	
		SoundManager::playClickEffect();
		switch (type)
		{
		case(1):
			flag->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mapFlag_0096.png"));
			break;
		case(0):
			flag->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mapFlag_0023.png"));
			break;
		case(2)://得星个数为4
			flag->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mapFlag_0117.png"));
			break;
		case(3)://得星个数为5
			flag->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mapFlag_0117.png"));

			break;
		default:
			break;
		}
		return true;  
	}  
	return false;  
}

MapFlag* MapFlag::createWithLevel(int level)
{
    auto mapFlag = new MapFlag();
 
    if (mapFlag && mapFlag->initWithLevel(level))
    {
        mapFlag->autorelease();
        return mapFlag;
    }
    CC_SAFE_DELETE(mapFlag);
    return NULL;
}

void MapFlag::changeType(int type)
{

	switch (type)
	{
	case(1):
		flag->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mapFlag_0095.png"));
		break;
	case(0):
		flag->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mapFlag_0022.png"));
		break;
	default:
		break;
	}
}

void MapFlag::initStar()
{
	star_0 = Sprite::createWithSpriteFrameName("mapFlag_star_0001.png");
	star_0->setPosition(Point(-25,45));

	star_1 = Sprite::createWithSpriteFrameName("mapFlag_star_0001.png");
	star_1->setPosition(Point(0,43));

	star_2 = Sprite::createWithSpriteFrameName("mapFlag_star_0001.png");
	star_2->setPosition(Point(25,41));

	starVector.pushBack(star_0);
	starVector.pushBack(star_1);
	starVector.pushBack(star_2);

	/*SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> aFrames;

	for (int len = 1;len <= 18; len++)
	{
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("mapFlag_star_00%02d.png",len)->getCString());

		if(frame!=nullptr)
			aFrames.pushBack(frame);
	}
	AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(aFrames,0.04f), "shine");*/
}

void MapFlag::startDropdownAnimation()
{
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> aFrames;

	for (int len = 1;len <= 22; len++)
	{
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("mapFlag_0%03d.png",len)->getCString());

		if(frame!=nullptr)
			aFrames.pushBack(frame);
	}
	flag->runAction(Animate::create(Animation::createWithSpriteFrames(aFrames,0.04f)));
}

void MapFlag::addStar()
{
	if(type!=0){
		addChild(star_0);
		addChild(star_1);
		addChild(star_2);
		int shiningNum = UserDefault::getInstance()->getIntegerForKey(String::createWithFormat(instance->LEVELX_STARNUM,getLevel())->getCString(),0);
		if( shiningNum>0)
		{
			for(int i=0;i<=shiningNum-1&&i<3;i++)
			{
				starVector.at(i)->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mapFlag_star_0018.png"));
			}
		}
	}
}

void MapFlag::startSuccessAnimation()
{
	/*SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> aFrames;

	for (int len = 23;len <= 95; len++)
	{
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("mapFlag_0%03d.png",len)->getCString());

		if(frame!=nullptr)
			aFrames.pushBack(frame);
	}*/
	//播放动画
	flag->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("succeed")),
		CallFunc::create(this,callfunc_selector(MapFlag::starAnimation)),NULL));
	setType(1);
}

void MapFlag::starAnimation()
{
	SoundManager::playWinStars();
	addChild(star_0);
	addChild(star_1);
	addChild(star_2);
	int shiningNum = UserDefault::getInstance()->getIntegerForKey(String::createWithFormat(instance->LEVELX_STARNUM,getLevel())->getCString(),0);
	if( shiningNum>0)
	{
		for(int i=0;i<=shiningNum-1;i++)
		{
			setStarShine(i);
		}
	}
}

void MapFlag::setStarShine(int num)
{
	starVector.at(num)->runAction(Sequence::create(DelayTime::create(num*0.3),
		Animate::create(AnimationCache::getInstance()->getAnimation("shine")),
				NULL));
}

void MapFlag::setStarClose()
{
	star_0->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mapFlag_star_0001.png"));
	star_1->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mapFlag_star_0001.png"));
	star_2->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mapFlag_star_0001.png"));
}