#include "Level7.h"

USING_NS_CC;

Level7::Level7()
{};

Level7::~Level7(){};

bool Level7::initWithDifficulty(int difficulty)
{
    if ( !Layer::init() )
    {
        return false;
    }
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level7-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level7_2-hd.plist");
	setLevel(7);
	this->difficulty = difficulty;
	initMap();

	std::vector<Point> points;
	points.push_back(Point(1160,340));
	points.push_back(Point(1160,680));
	addWaveProgressBars(points);
	waveFlags.at(0)->restartWaveFlag();
	waveFlags.at(1)->restartWaveFlag();

	SoundManager::playJungleBattle();
	return true;
}

Level7* Level7::createGame(int difficulty)
{  
    auto layer = new Level7();
	if(layer && layer->initWithDifficulty(difficulty)){
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

    return NULL;
}

void Level7::addOrnament()
{
	auto bridge=Sprite::createWithSpriteFrameName("Stage6_Bridge_0001.png");
	bridge->setPosition(Point(760,670));
	addChild(bridge);
}

void Level7::onExit()
{
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_Level7-hd.plist");
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_Level7_2-hd.plist");
}

void Level7::addTerrains()
{
	auto terrain1 = Terrain::createTerrain(2);
	terrain1->setPosition(Point(325,770));
	terrain1->setTag(1);
	addChild(terrain1,3);

	auto terrain2 = Terrain::createTerrain(2);
	terrain2->setPosition(Point(535,765));
	terrain2->setTag(2);
	addChild(terrain2,3);

	auto terrain3 = Terrain::createTerrain(2);
	terrain3->setPosition(Point(410,600));
	terrain3->setTag(3);
	addChild(terrain3,4);

	auto terrain4 = Terrain::createTerrain(2);
	terrain4->setPosition(Point(570,600));
	terrain4->setTag(4);
	addChild(terrain4,4);

	auto terrain5 = Terrain::createTerrain(2);
	terrain5->setPosition(Point(930,600));
	terrain5->setTag(5);
	addChild(terrain5,4);

	auto terrain6 = Terrain::createTerrain(2);
	terrain6->setPosition(Point(290,460));
	terrain6->setTag(6);
	addChild(terrain6,6);

	auto terrain7 =Terrain::createTerrain(2);
	terrain7->setPosition(Point(475,355));
	terrain7->setTag(7);
	addChild(terrain7,7);

	auto terrain8 = Terrain::createTerrain(2);
	terrain8->setPosition(Point(685,420));
	terrain8->setTag(8);
	addChild(terrain8,6);

	auto terrain9 = Terrain::createTerrain(2);
	terrain9->setPosition(Point(920,420));
	terrain9->setTag(9);
	addChild(terrain9,6);

	auto terrain10 = Terrain::createTerrain(2);
	terrain10->setPosition(Point(630,220));
	terrain10->setTag(10);
	addChild(terrain10,8);


}
