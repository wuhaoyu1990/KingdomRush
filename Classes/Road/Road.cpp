#include "Road.h"
#include "GameManager.h"

Road::~Road(){}

Road::Road(){}

bool Road::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	auto road_0 = Sprite::createWithSpriteFrameName("mapRoad_1to1_5_0009.png");
	auto road_1 = Sprite::createWithSpriteFrameName("mapRoad_1_5_to2_0013.png");
	auto road_2 = Sprite::createWithSpriteFrameName("mapRoad_2to3_0012.png");
	auto road_3 = Sprite::createWithSpriteFrameName("mapRoad_3to4_0021.png");
	auto road_4 = Sprite::createWithSpriteFrameName("mapRoad_4to5_0141.png");
	auto road_5 = Sprite::createWithSpriteFrameName("mapRoad_5to6_0025.png");
	auto road_6 = Sprite::createWithSpriteFrameName("mapRoad_6to7_0025.png");
	auto road_7 = Sprite::createWithSpriteFrameName("mapRoad_7to8_0022.png");
	auto road_8 = Sprite::createWithSpriteFrameName("mapRoad_8to9_0022.png");
	auto road_9 = Sprite::createWithSpriteFrameName("mapRoad_9to10_0010.png");
	auto road_10 = Sprite::createWithSpriteFrameName("mapRoad_10to11_0013.png");
	auto road_11 = Sprite::createWithSpriteFrameName("mapRoad_11to12_0010.png");
	auto road_12 = Sprite::createWithSpriteFrameName("mapRoad_12to13_0007.png");
	auto road_13 = Sprite::createWithSpriteFrameName("mapRoad_13to14_0010.png");

	roadVector.pushBack(road_0);
	roadVector.pushBack(road_1);
	roadVector.pushBack(road_2);
	roadVector.pushBack(road_3);
	roadVector.pushBack(road_4);
	roadVector.pushBack(road_5);
	roadVector.pushBack(road_6);
	roadVector.pushBack(road_7);
	roadVector.pushBack(road_8);
	roadVector.pushBack(road_9);
	roadVector.pushBack(road_10);
	roadVector.pushBack(road_11);
	roadVector.pushBack(road_12);
	roadVector.pushBack(road_13);

	road_0->setVisible(false);
	road_1->setVisible(false);
	road_2->setVisible(false);
	road_3->setVisible(false);
	road_4->setVisible(false);
	road_5->setVisible(false);
	road_6->setVisible(false);
	road_7->setVisible(false);
	road_8->setVisible(false);
	road_9->setVisible(false);
	road_10->setVisible(false);
	road_11->setVisible(false);
	road_12->setVisible(false);
	road_13->setVisible(false);

	addChild(road_0);
	addChild(road_1);
	addChild(road_2);
	addChild(road_3);
	addChild(road_4);
	addChild(road_5);
	addChild(road_6);
	addChild(road_7);
	addChild(road_8);
	addChild(road_9);
	addChild(road_10);
	addChild(road_11);
	addChild(road_12);
	addChild(road_13);

	setRoadReady();
	initRoadAnimation();
	return true;
}

void Road::setRoadReady()
{
	int hasDone = UserDefault::getInstance()->getIntegerForKey(GameManager::getInstance()->SLOTX_DOWNCOUNT,0);//表示已经通关数
	if(hasDone!=0){
		for(int i=0;i<=hasDone-1;i++)
		{
			roadVector.at(i)->setVisible(true);
		}
	}
}

void Road::buildRoadAnimation(int num)
{
	roadVector.at(num)->setVisible(true);
	roadVector.at(num)->runAction(Animate::create(roadAnimaitonVector.at(num)));
}

void Road::initRoadAnimation()
{
	SpriteFrame* frame0 = NULL;
	Vector<SpriteFrame*> aFrames0;
	for (int len = 1;len <= 7; len++)
	{
		frame0 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("mapRoad_1to1_5_00%02d.png",len)->getCString());
		if(frame0!=nullptr)
			aFrames0.pushBack(frame0);
	}
	roadAnimaitonVector.pushBack(Animation::createWithSpriteFrames(aFrames0,0.1f));

	SpriteFrame* frame1 = NULL;
	Vector<SpriteFrame*> aFrames1;
	for (int len = 1;len <= 13; len++)
	{
		frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("mapRoad_1_5_to2_00%02d.png",len)->getCString());
		if(frame1!=nullptr)
			aFrames1.pushBack(frame1);
	}
	roadAnimaitonVector.pushBack(Animation::createWithSpriteFrames(aFrames1,0.1f));

	SpriteFrame* frame2 = NULL;
	Vector<SpriteFrame*> aFrames2;
	for (int len = 1;len <= 12; len++)
	{
		frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("mapRoad_2to3_00%02d.png",len)->getCString());
		if(frame2!=nullptr)
			aFrames2.pushBack(frame2);
	}
	roadAnimaitonVector.pushBack(Animation::createWithSpriteFrames(aFrames2,0.1f));

	SpriteFrame* frame3 = NULL;
	Vector<SpriteFrame*> aFrames3;
	for (int len = 1;len <= 21; len++)
	{
		frame3 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("mapRoad_3to4_00%02d.png",len)->getCString());
		if(frame3!=nullptr)
			aFrames3.pushBack(frame3);
	}
	roadAnimaitonVector.pushBack(Animation::createWithSpriteFrames(aFrames3,0.07f));

	SpriteFrame* frame4 = NULL;
	Vector<SpriteFrame*> aFrames4;
	for (int len = 1;len <= 141; len++)
	{
		frame4 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("mapRoad_4to5_0%03d.png",len)->getCString());
		if(frame4!=nullptr)
			aFrames4.pushBack(frame4);
	}
	roadAnimaitonVector.pushBack(Animation::createWithSpriteFrames(aFrames4,0.01f));

	SpriteFrame* frame5 = NULL;
	Vector<SpriteFrame*> aFrames5;
	for (int len = 1;len <= 25; len++)
	{
		frame5 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("mapRoad_5to6_00%02d.png",len)->getCString());
		if(frame5!=nullptr)
			aFrames5.pushBack(frame5);
	}
	roadAnimaitonVector.pushBack(Animation::createWithSpriteFrames(aFrames5,0.07f));

	SpriteFrame* frame6 = NULL;
	Vector<SpriteFrame*> aFrames6;
	for (int len = 1;len <= 25; len++)
	{
		frame6 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("mapRoad_6to7_00%02d.png",len)->getCString());
		if(frame6!=nullptr)
			aFrames6.pushBack(frame6);
	}
	roadAnimaitonVector.pushBack(Animation::createWithSpriteFrames(aFrames6,0.07f));

	SpriteFrame* frame7 = NULL;
	Vector<SpriteFrame*> aFrames7;
	for (int len = 1;len <= 22; len++)
	{
		frame7 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("mapRoad_7to8_00%02d.png",len)->getCString());
		if(frame7!=nullptr)
			aFrames7.pushBack(frame7);
	}
	roadAnimaitonVector.pushBack(Animation::createWithSpriteFrames(aFrames7,0.07f));

	SpriteFrame* frame8 = NULL;
	Vector<SpriteFrame*> aFrames8;
	for (int len = 1;len <= 22; len++)
	{
		frame8 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("mapRoad_8to9_00%02d.png",len)->getCString());
		if(frame8!=nullptr)
			aFrames8.pushBack(frame8);
	}
	roadAnimaitonVector.pushBack(Animation::createWithSpriteFrames(aFrames8,0.1f));

	SpriteFrame* frame9 = NULL;
	Vector<SpriteFrame*> aFrames9;
	for (int len = 1;len <= 10; len++)
	{
		frame9 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("mapRoad_9to10_00%02d.png",len)->getCString());
		if(frame9!=nullptr)
			aFrames9.pushBack(frame9);
	}
	roadAnimaitonVector.pushBack(Animation::createWithSpriteFrames(aFrames9,0.1f));

	SpriteFrame* frame10 = NULL;
	Vector<SpriteFrame*> aFrames10;
	for (int len = 1;len <= 13; len++)
	{
		frame10 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("mapRoad_10to11_00%02d.png",len)->getCString());
		if(frame10!=nullptr)
			aFrames10.pushBack(frame10);
	}
	roadAnimaitonVector.pushBack(Animation::createWithSpriteFrames(aFrames10,0.07f));

	SpriteFrame* frame11 = NULL;
	Vector<SpriteFrame*> aFrames11;
	for (int len = 1;len <= 10; len++)
	{
		frame11 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("mapRoad_11to12_00%02d.png",len)->getCString());
		if(frame11!=nullptr)
			aFrames11.pushBack(frame11);
	}
	roadAnimaitonVector.pushBack(Animation::createWithSpriteFrames(aFrames11,0.1f));

	SpriteFrame* frame12 = NULL;
	Vector<SpriteFrame*> aFrames12;
	for (int len = 1;len <= 7; len++)
	{
		frame12 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("mapRoad_12to13_00%02d.png",len)->getCString());
		if(frame12!=nullptr)
			aFrames12.pushBack(frame12);
	}
	roadAnimaitonVector.pushBack(Animation::createWithSpriteFrames(aFrames12,0.1f));

	SpriteFrame* frame13 = NULL;
	Vector<SpriteFrame*> aFrames13;
	for (int len = 1;len <= 7; len++)
	{
		frame13 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("mapRoad_12to13_00%02d.png",len)->getCString());
		if(frame13!=nullptr)
			aFrames13.pushBack(frame13);
	}
	roadAnimaitonVector.pushBack(Animation::createWithSpriteFrames(aFrames13,0.1f));
}