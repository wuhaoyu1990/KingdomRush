#include "TouchLayer.h"
#include "GameManager.h"
#include "RallyCircle.h"
#include "BaseMap.h"
#include "RallyCircle.h"
#include "ReinforceSoldier1.h"
#include "ReinforceSoldier2.h"
#include "Freeze.h"
#include "Dynamite.h"
#include "FireBall.h"
#include "PlayerStateMenu.h"

void TouchLayer::setTouchShield()
{
	touchlistener = EventListenerTouchOneByOne::create();
	touchlistener->onTouchBegan = CC_CALLBACK_2(TouchLayer::onTouchBegan, this);
	touchlistener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onTouchEnded, this);
	touchlistener->onTouchMoved = CC_CALLBACK_2(TouchLayer::onTouchMoved, this);
	touchlistener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithFixedPriority(touchlistener,-1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener,this);
}

void TouchLayer::removeTouchShield()
{
	if(touchlistener!=NULL)
		_eventDispatcher->removeEventListener(touchlistener);
}

bool TouchLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	winSize = Director::getInstance()->getWinSize();
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> aFrames;
	Soldierlistener = NULL;
	Freezelistener = NULL;
	Dynamitelistener = NULL;
	FiereBalllistener = NULL;

	for (int len = 1;len <= 30; len++)
	{
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("rally_feedback_00%2d.png",len)->getCString());
		if(frame!=nullptr)
			aFrames.pushBack(frame);
	}
	AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(aFrames,0.04f),"rally_flag");
	isFlag = false;
	setTouchShield();
	
	isMoved = false;
	return true;
}

void TouchLayer::setFireBallTouchShield()
{
	//调用此方法创建陨石技能触摸时间
	FiereBalllistener = EventListenerTouchOneByOne::create();
	FiereBalllistener->onTouchBegan = CC_CALLBACK_2(TouchLayer::onFireBallTouchBegan, this);
	FiereBalllistener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onFireBallTouchEnded, this);
	FiereBalllistener->setSwallowTouches(true);
	//设置比移动触摸事件高即可
	_eventDispatcher->addEventListenerWithFixedPriority(FiereBalllistener,1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(FiereBalllistener,this);
}

void TouchLayer::removeFireBallTouchShield()
{
	//使用技能完毕去除此监听时间
	if(FiereBalllistener!=NULL)
		_eventDispatcher->removeEventListener(FiereBalllistener);
}

bool TouchLayer::onFireBallTouchBegan(Touch* touch, Event* event)
{
	//直接返回TRUE，拦截其他时间
	return true;
}

void TouchLayer::onFireBallTouchEnded(Touch* touch, Event* event)
{
	//播放音效
	SoundManager::playFireballUnleash();
	//创建3个陨石
	auto fireBall1 = FireBall::create();
	addChild(fireBall1);
	fireBall1->shoot(static_cast<TouchLayer*>(event->getCurrentTarget())->convertTouchToNodeSpace(touch)+Point(-30,300));
	auto fireBall2 = FireBall::create();
	addChild(fireBall2);
	fireBall2->shoot(static_cast<TouchLayer*>(event->getCurrentTarget())->convertTouchToNodeSpace(touch)+Point(0,350));
	auto fireBall3 = FireBall::create();
	addChild(fireBall3);
	fireBall3->shoot(static_cast<TouchLayer*>(event->getCurrentTarget())->convertTouchToNodeSpace(touch)+Point(30,280));
	//陨石坠落之后获取父类的玩家状态层，调用startStone,重新开始计时并且重置ProgressTimer遮盖层
	static_cast<BaseMap*>(this->getParent())->playerState->startStone();
	//移除此监听事件
	removeFireBallTouchShield();
}

void TouchLayer::setDynamiteTouchShield()
{
	Dynamitelistener = EventListenerTouchOneByOne::create();
	Dynamitelistener->onTouchBegan = CC_CALLBACK_2(TouchLayer::onDynamiteTouchBegan, this);
	Dynamitelistener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onDynamiteTouchEnded, this);
	Dynamitelistener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Dynamitelistener,this);
}

void TouchLayer::removeDynamiteTouchShield()
{
	if(Dynamitelistener!=NULL)
		_eventDispatcher->removeEventListener(Dynamitelistener);
}

bool TouchLayer::onDynamiteTouchBegan(Touch* touch, Event* event)
{
	return true;
}
void TouchLayer::onDynamiteTouchEnded(Touch* touch, Event* event)
{
	auto dynamite = Dynamite::create();
	this->getParent()->addChild(dynamite);
	dynamite->shoot(static_cast<TouchLayer*>(event->getCurrentTarget())->convertTouchToNodeSpace(touch));
	removeDynamiteTouchShield();
}

void TouchLayer::setFreezeTouchShield()
{
	Freezelistener = EventListenerTouchOneByOne::create();
	Freezelistener->onTouchBegan = CC_CALLBACK_2(TouchLayer::onFreezeTouchBegan, this);
	Freezelistener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onFreezeTouchEnded, this);
	Freezelistener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Freezelistener,this);
}
	
void TouchLayer::removeFreezeTouchShield()
{
	if(Freezelistener!=NULL)
		_eventDispatcher->removeEventListener(Freezelistener);
}

bool TouchLayer::onFreezeTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void TouchLayer::onFreezeTouchEnded(Touch* touch, Event* event)
{
	SoundManager::playFreeze();
	auto freeze = Freeze::create();
	this->getParent()->addChild(freeze);
	freeze->shoot(static_cast<TouchLayer*>(event->getCurrentTarget())->convertTouchToNodeSpace(touch));
	removeFreezeTouchShield();
}

void TouchLayer::setRallyFlagTouchShield()
{
	rallyCircle = RallyCircle::create();
	rallyCircle->setPosition(tower->getParent()->getPosition());
	rallyCircle->setTag(1001);
	addChild(rallyCircle);
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TouchLayer::onRallyFlagTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onRallyFlagTouchEnded, this);
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}

void TouchLayer::removeRallyFlagTouchShield()
{
	removeChildByTag(1001);
	if(listener!=NULL)
		_eventDispatcher->removeEventListener(listener);
}

void TouchLayer::setSoldierTouchShield()
{
	Soldierlistener = EventListenerTouchOneByOne::create();
	Soldierlistener->onTouchBegan = CC_CALLBACK_2(TouchLayer::onSoldierTouchBegan, this);
	Soldierlistener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onSoldierTouchEnded, this);
	Soldierlistener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Soldierlistener,this);
}

void TouchLayer::removeSoldierTouchShield()
{
	_eventDispatcher->removeEventListener(Soldierlistener);
}

bool TouchLayer::onSoldierTouchBegan(Touch* touch, Event* event)
{	
	return true;
}

void TouchLayer::removeAllListener()
{
	removeFireBallTouchShield();
	removeFreezeTouchShield();
	removeSoldierTouchShield();
	removeRallyFlagTouchShield();
	removeDynamiteTouchShield();
}


void TouchLayer::onSoldierTouchEnded(Touch* touch, Event* event)
{
	SoundManager::playReinforcement();
	auto target = static_cast<TouchLayer*>(event->getCurrentTarget());
	Point locationInNode = target->convertTouchToNodeSpace(touch);

	auto feedBack = Sprite::createWithSpriteFrameName("confirm_feedback_layer2_0001.png");
	feedBack->setPosition(locationInNode);
	addChild(feedBack);
	feedBack->runAction(Sequence::create(FadeOut::create(1.0f),
				CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, feedBack))
                ,NULL));

	auto reinforceSoldier1 = ReinforceSoldier1::createReinforceSoldier(Point(locationInNode.x+15,locationInNode.y+20));
	this->getParent()->addChild(reinforceSoldier1);

	auto reinforceSoldier2 = ReinforceSoldier2::createReinforceSoldier(Point(locationInNode.x-15,locationInNode.y+20));
	this->getParent()->addChild(reinforceSoldier2);
	static_cast<BaseMap*>(this->getParent())->playerState->startParatrooper();
	removeSoldierTouchShield();
}

bool TouchLayer::onRallyFlagTouchBegan(Touch* touch, Event* event)
{
	auto target = static_cast<TouchLayer*>(event->getCurrentTarget());
	Point locationInNode = target->convertTouchToNodeSpace(touch);
	if(locationInNode.distance(tower->getParent()->getPosition())<160 && locationInNode.distance(tower->getParent()->getPosition())>80){
		addRallyFlag(locationInNode);
		tower->setRallyPoint(locationInNode);
		SoundManager::playRallyPointPlaced();
		isFlag = true;
	}else{
		addWrongPlace(static_cast<TouchLayer*>(event->getCurrentTarget())->convertTouchToNodeSpace(touch));
	}
	return true;
}

void TouchLayer::onRallyFlagTouchEnded(Touch* touch, Event* event)
{
	if(isFlag){
		removeRallyFlagTouchShield();
		isFlag = false;
	}
}

void TouchLayer::addRallyFlag(Point location)
{
	auto flag = Sprite::createWithSpriteFrameName("rally_feedback_0015.png");
	flag->setPosition(location);
	addChild(flag);
	flag->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("rally_flag"))
										,CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, flag))
                                       , NULL));
}

void TouchLayer::addWrongPlace(Point location)
{
	auto wrong = Sprite::createWithSpriteFrameName("error_feedback_0001.png");
	wrong->setPosition(location);
	wrong->runAction(Sequence::create(FadeOut::create(1.0f)
										,CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, wrong))
                                       , NULL));
	addChild(wrong);
}

bool TouchLayer::onTouchBegan(Touch* touch, Event* event)
{
	touchlistener->setSwallowTouches(false);
	return true;
}

void TouchLayer::onTouchEnded(Touch* touch, Event* event)
{
	touchlistener->setSwallowTouches(isMoved);
	if(!isMoved){
		static_cast<BaseMap*>(this->getParent())->playerState->removeTowerInfo();
		static_cast<BaseMap*>(this->getParent())->playerState->removeMonsterInfo();
	}
	isMoved = false;
}

void TouchLayer::onTouchMoved(Touch* touch, Event* event)
{
        // 计算滑动过程中的滑动增量
        auto diff = touch->getDelta(); 

		//手指移动修正，因为手指触摸不像鼠标触摸那么固定
		if(abs(diff.x) >5|| abs(diff.y) >5){
			isMoved = true;
		}
			// 得到当前bgSprite的位置
			auto currentPos = this->getParent()->getPosition();
			// 得到滑动后bgSprite应该所在的位置
			auto pos = currentPos + diff;

			//边界控制，约束pos的位置
			pos.x = MIN(pos.x, 0);
			pos.x = MAX(pos.x, -1200 + winSize.width);
			pos.y = MIN(pos.y, 0);
			pos.y = MAX(pos.y, -1000 + winSize.height);
			// 重设bgSprite位置

			this->getParent()->setPosition(pos);
}
