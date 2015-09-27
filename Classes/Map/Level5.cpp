#include "Level5.h"

USING_NS_CC;

Level5::Level5()
{};

Level5::~Level5(){};

bool Level5::initWithDifficulty(int difficulty)
{
    if ( !Layer::init() )
    {
        return false;
    }
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level5-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level5_2-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level5_3-hd.plist");
	MyAnimation::getInstance()->init_BossEfreeti();
	setLevel(5);
	this->difficulty = difficulty;
	initMap();
	//O为左上1 1为右，2为坐上2,3为上
	std::vector<Point> points;
	points.push_back(Point(40,637));
	points.push_back(Point(1140,490));
	points.push_back(Point(40,450));
	addWaveProgressBars(points);
	waveFlags.at(0)->restartWaveFlag();
	waveFlags.at(1)->restartWaveFlag();
	waveFlags.at(2)->restartWaveFlag();
	SoundManager::playDesertBattle();
	return true;
}

void Level5::beforeBoss()
{
	this->runAction(MoveTo::create(0.5f,Point(0,Director::getInstance()->getVisibleSize().height-1000)));
}

Level5* Level5::createGame(int difficulty)
{  
    auto layer = new Level5();
	if(layer && layer->initWithDifficulty(difficulty)){
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

    return NULL;
}

void Level5::addOrnament()
{
	door = Sprite::createWithSpriteFrameName("Stage5_door_0001.png");
	door->setPosition(Point(670,850));
	addChild(door);
}

void Level5::waveEvent()
{
	if(wave == 1){
		beforeBoss();
		Vector<SpriteFrame*> animFrames1;
		SpriteFrame* frame1=NULL;
		for (int i = 1; i <= 36; i++)
		{
			frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("Stage5_door_00%02d.png",i)->getCString());
			if(frame1!=nullptr)
				animFrames1.pushBack(frame1);
		}
		auto doorAnimation = Animation::createWithSpriteFrames(animFrames1, 0.04f);
		
		door->runAction(Sequence::create(
			CallFuncN::create(CC_CALLBACK_0(Level5::eyeEffect,this)),
			DelayTime::create(4.0f),
			Animate::create(doorAnimation),
			CallFuncN::create(CC_CALLBACK_0(Level5::stonesEffect,this)),
			NULL));
		schedule(schedule_selector(Level5::addMonsters), 1.0f, waveVector.at(wave).size(), 6.0f);
	}else{
		schedule(schedule_selector(Level5::addMonsters), 1.0f, waveVector.at(wave).size(), 0.0f);
	}
}

void Level5::eyeEffect()
{
	auto eyeEffect = Sprite::createWithSpriteFrameName("Stage5_door_eyes_effect_0001.png");
	Vector<SpriteFrame*> animFrames;
	SpriteFrame* frame=NULL;
	for (int i = 1; i <= 94; i++){
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("Stage5_door_eyes_00%02d.png",i)->getCString());
		if(frame!=nullptr)
		animFrames.pushBack(frame);
	}
	auto eyeAnimation = Animation::createWithSpriteFrames(animFrames, 0.04f);
	eyeEffect->setPosition(Point(95,70));
	door->addChild(eyeEffect);
	eyeEffect->runAction(Animate::create(eyeAnimation));
}

void Level5::stonesEffect()
{
	auto stone = Sprite::createWithSpriteFrameName("Stage5_door_stones_0001.png");
	Vector<SpriteFrame*> animFrames;
	SpriteFrame* frame = NULL;
	for (int i = 1; i <= 94; i++){
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("Stage5_door_stones_00%02d.png",i)->getCString());
		if(frame!=nullptr)
		animFrames.pushBack(frame);
	}
	auto stoneAnimation = Animation::createWithSpriteFrames(animFrames, 0.04f);
	stone->setPosition(Point(670,850));
	addChild(stone);
	stone->runAction(Animate::create(stoneAnimation));
}

void Level5::addTerrains()
{
	auto terrain14 = Terrain::createTerrain(1);
	terrain14->setPosition(Point(311,712));
	terrain14->setTag(14);
	addChild(terrain14,3);

	auto terrain3 = Terrain::createTerrain(1);
	terrain3->setPosition(Point(687,606));
	terrain3->setTag(3);
	addChild(terrain3,4);

	auto terrain11 = Terrain::createTerrain(1);
	terrain11->setPosition(Point(435,550));
	terrain11->setTag(11);
	addChild(terrain11,5);

	auto terrain12 = Terrain::createTerrain(1);
	terrain12->setPosition(Point(300,550));
	terrain12->setTag(12);
	addChild(terrain12,5);

	auto terrain13 = Terrain::createTerrain(1);
	terrain13->setPosition(Point(170,550));
	terrain13->setTag(13);
	addChild(terrain13,5);


	auto terrain1 = Terrain::createTerrain(1);
	terrain1->setPosition(Point(858,466));
	terrain1->setTag(1);
	addChild(terrain1,6);

	auto terrain4 = Terrain::createTerrain(1);
	terrain4->setPosition(Point(631,474));
	terrain4->setTag(4);
	addChild(terrain4,6);

	auto terrain8 = Terrain::createTerrain(1);
	terrain8->setPosition(Point(558,390));
	terrain8->setTag(8);
	addChild(terrain8,7);

	auto terrain9 = Terrain::createTerrain(1);
	terrain9->setPosition(Point(446,373));
	terrain9->setTag(9);
	addChild(terrain9,7);

	auto terrain10 = Terrain::createTerrain(1);
	terrain10->setPosition(Point(316,374));
	terrain10->setTag(10);
	addChild(terrain10,7);

	auto terrain5 = Terrain::createTerrain(1);
	terrain5->setPosition(Point(668,343));
	terrain5->setTag(5);
	addChild(terrain5,7);

	auto terrain6 = Terrain::createTerrain(1);
	terrain6->setPosition(Point(747,305));
	terrain6->setTag(6);
	addChild(terrain6,7);

	auto terrain7 = Terrain::createTerrain(1);
	terrain7->setPosition(Point(851,290));
	terrain7->setTag(7);
	addChild(terrain7,8);

}

void Level5::onExit()
{
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_Level5_3-hd.plist");
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_Level5_2-hd.plist");
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_level5-hd.plist");
}
