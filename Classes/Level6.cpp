#include "Level6.h"

USING_NS_CC;

Level6::Level6()
{};

Level6::~Level6(){};

bool Level6::initWithDifficulty(int difficulty)
{
    if ( !Layer::init() )
    {
        return false;
    }

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level6-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level6_2-hd.plist");
	setLevel(6);
	this->difficulty = difficulty;
	initMap();
	
	std::vector<Point> points;
	points.push_back(Point(40,360));
	points.push_back(Point(40,610));
	points.push_back(Point(756,940));
	points.push_back(Point(1145,560));
	addWaveProgressBars(points);
	waveFlags.at(0)->restartWaveFlag();
	waveFlags.at(1)->restartWaveFlag();
	waveFlags.at(2)->restartWaveFlag();
	waveFlags.at(3)->restartWaveFlag();
	SoundManager::playJungleBattle();
	return true;
}

Level6* Level6::createGame(int difficulty)
{  
    auto layer = new Level6();
	if(layer && layer->initWithDifficulty(difficulty)){
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

    return NULL;
}

void Level6::addOrnament()
{

}

void Level6::onExit()
{
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_Level6-hd.plist");
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_Level6_2-hd.plist");
}

void Level6::addTerrains()
{
	auto terrain1 = Terrain::createTerrain(2);
	terrain1->setPosition(Point(350,690));
	terrain1->setTag(1);
	addChild(terrain1,4);

	auto terrain2 = Terrain::createTerrain(2);
	terrain2->setPosition(Point(815,750));
	terrain2->setTag(2);
	addChild(terrain2,3);

	auto terrain3 = Terrain::createTerrain(2);
	terrain3->setPosition(Point(275,510));
	terrain3->setTag(3);
	addChild(terrain3,5);

	auto terrain4 = Terrain::createTerrain(2);
	terrain4->setPosition(Point(670,520));
	terrain4->setTag(4);
	addChild(terrain4,5);

	auto terrain5 = Terrain::createTerrain(2);
	terrain5->setPosition(Point(960,575));
	terrain5->setTag(5);
	addChild(terrain5,5);

	auto terrain6 = Terrain::createTerrain(2);
	terrain6->setPosition(Point(750,450));
	terrain6->setTag(6);
	addChild(terrain6,6);

	auto terrain7 = Terrain::createTerrain(2);
	terrain7->setPosition(Point(535,350));
	terrain7->setTag(7);
	addChild(terrain7,7);

	auto terrain8 = Terrain::createTerrain(2);
	terrain8->setPosition(Point(820,380));
	terrain8->setTag(8);
	addChild(terrain8,7);

	auto terrain9 = Terrain::createTerrain(2);
	terrain9->setPosition(Point(1080,370));
	terrain9->setTag(9);
	addChild(terrain9,7);

	auto terrain10 = Terrain::createTerrain(2);
	terrain10->setPosition(Point(810,190));
	terrain10->setTag(10);
	addChild(terrain10,9);

}
