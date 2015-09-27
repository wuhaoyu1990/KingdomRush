#include "Level8.h"

USING_NS_CC;

Level8::Level8()
{};

Level8::~Level8(){};

bool Level8::initWithDifficulty(int difficulty)
{
    if ( !Layer::init() )
    {
        return false;
    }
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level8-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level8_2-hd.plist");
	setLevel(8);
	this->difficulty = difficulty;
	initMap();

	std::vector<Point> points;
	points.push_back(Point(526,960));
	points.push_back(Point(40,540));
	points.push_back(Point(1140,530));
	
	addWaveProgressBars(points);
	waveFlags.at(0)->restartWaveFlag();
	waveFlags.at(1)->restartWaveFlag();
	waveFlags.at(2)->restartWaveFlag();

	SoundManager::playJungleBattle();
	return true;
}

Level8* Level8::createGame(int difficulty)
{  
    auto layer = new Level8();
	if(layer && layer->initWithDifficulty(difficulty)){
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

    return NULL;
}

void Level8::addOrnament()
{

}

void Level8::onExit()
{
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_Level8-hd.plist");
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_Level8_2-hd.plist");
}

void Level8::addTerrains()
{
	auto terrain1 = Terrain::createTerrain(2);
	terrain1->setPosition(Point(500,760));
	terrain1->setTag(1);
	addChild(terrain1,3);

	auto terrain2 = Terrain::createTerrain(2);
	terrain2->setPosition(Point(400,730));
	terrain2->setTag(2);
	addChild(terrain2,3);

	auto terrain3 = Terrain::createTerrain(2);
	terrain3->setPosition(Point(245,620));
	terrain3->setTag(3);
	addChild(terrain3,4);

	auto terrain4 = Terrain::createTerrain(2);
	terrain4->setPosition(Point(485,570));
	terrain4->setTag(4);
	addChild(terrain4,5);

	auto terrain5 = Terrain::createTerrain(2);
	terrain5->setPosition(Point(675,600));
	terrain5->setTag(5);
	addChild(terrain5,4);

	auto terrain6 = Terrain::createTerrain(2);
	terrain6->setPosition(Point(540,460));
	terrain6->setTag(6);
	addChild(terrain6,6);

	auto terrain7 = Terrain::createTerrain(2);
	terrain7->setPosition(Point(290,430));
	terrain7->setTag(7);
	addChild(terrain7,6);

	auto terrain8 = Terrain::createTerrain(2);
	terrain8->setPosition(Point(750,350));
	terrain8->setTag(8);
	addChild(terrain8,7);

	auto terrain9 = Terrain::createTerrain(2);
	terrain9->setPosition(Point(645,510));
	terrain9->setTag(9);
	addChild(terrain9,6);

	auto terrain10 = Terrain::createTerrain(2);
	terrain10->setPosition(Point(540,230));
	terrain10->setTag(10);
	addChild(terrain10,8);

}
