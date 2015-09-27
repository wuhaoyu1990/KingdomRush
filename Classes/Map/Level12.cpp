#include "Level12.h"

USING_NS_CC;

Level12::Level12()
{};

Level12::~Level12(){};

bool Level12::initWithDifficulty(int difficulty)
{
    if ( !Layer::init() )
    {
        return false;
    }
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_Level12-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_Level12_2-hd.plist");

	setLevel(12);
	this->difficulty = difficulty;
	initMap();

	std::vector<Point> points;
	points.push_back(Point(450,800));
	points.push_back(Point(40,300));
	points.push_back(Point(1091,710));
	addWaveProgressBars(points);
	waveFlags.at(0)->restartWaveFlag();
	waveFlags.at(1)->restartWaveFlag();
	waveFlags.at(2)->restartWaveFlag();

	SoundManager::playDesertBattle();
	return true;
}

Level12* Level12::createGame(int difficulty)
{  
    auto layer = new Level12();
	if(layer && layer->initWithDifficulty(difficulty)){
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

    return NULL;
}

void Level12::addOrnament()
{

}

void Level12::onExit()
{
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_Level12-hd.plist");
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_Level12_2-hd.plist");
}

void Level12::addTerrains()
{
	auto terrain1 = Terrain::createTerrain(3);
	terrain1->setPosition(Point(230,630));
	terrain1->setTag(1);
	addChild(terrain1,7);

	auto terrain2 = Terrain::createTerrain(3);
	terrain2->setPosition(Point(320,630));
	terrain2->setTag(2);
	addChild(terrain2,7);

	auto terrain3 = Terrain::createTerrain(3);
	terrain3->setPosition(Point(436,630));
	terrain3->setTag(3);
	addChild(terrain3,7);

	auto terrain4 = Terrain::createTerrain(3);
	terrain4->setPosition(Point(518,690));
	terrain4->setTag(4);
	addChild(terrain4,7);

	auto terrain5 = Terrain::createTerrain(3);
	terrain5->setPosition(Point(589,603));
	terrain5->setTag(5);
	addChild(terrain5,7);

	auto terrain6 = Terrain::createTerrain(3);
	terrain6->setPosition(Point(363,440));
	terrain6->setTag(6);
	addChild(terrain6,5);

	auto terrain7 =Terrain::createTerrain(3);
	terrain7->setPosition(Point(502,420));
	terrain7->setTag(7);
	addChild(terrain7,5);

	auto terrain8 = Terrain::createTerrain(3);
	terrain8->setPosition(Point(270,320));
	terrain8->setTag(8);
	addChild(terrain8,4);

	auto terrain9 = Terrain::createTerrain(3);
	terrain9->setPosition(Point(510,230));
	terrain9->setTag(9);
	addChild(terrain9,3);

	auto terrain10 = Terrain::createTerrain(3);
	terrain10->setPosition(Point(677,290));
	terrain10->setTag(10);
	addChild(terrain10,3);

	auto terrain11 = Terrain::createTerrain(3);
	terrain11->setPosition(Point(890,160));
	terrain11->setTag(11);
	addChild(terrain11,2);

	auto terrain12 = Terrain::createTerrain(3);
	terrain12->setPosition(Point(922,330));
	terrain12->setTag(12);
	addChild(terrain12,4);

	auto terrain13 = Terrain::createTerrain(3);
	terrain13->setPosition(Point(715,450));
	terrain13->setTag(13);
	addChild(terrain13,5);

	auto terrain14 = Terrain::createTerrain(3);
	terrain14->setPosition(Point(792,520));
	terrain14->setTag(14);
	addChild(terrain14,6);

	auto terrain15 = Terrain::createTerrain(3);
	terrain15->setPosition(Point(967,520));
	terrain15->setTag(15);
	addChild(terrain15,6);
}
