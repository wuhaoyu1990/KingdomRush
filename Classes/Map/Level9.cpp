#include "Level9.h"

USING_NS_CC;

Level9::Level9()
{};

Level9::~Level9(){};

bool Level9::initWithDifficulty(int difficulty)
{
    if ( !Layer::init() )
    {
        return false;
    }
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level9_2-hd.plist");
	setLevel(9);
	this->difficulty = difficulty;
	initMap();

	std::vector<Point> points;
	points.push_back(Point(830,960));
	points.push_back(Point(1140,300));
	addWaveProgressBars(points);
	waveFlags.at(0)->restartWaveFlag();
	waveFlags.at(1)->restartWaveFlag();
	SoundManager::playJungleBattle();
	return true;
}

Level9* Level9::createGame(int difficulty)
{  
    auto layer = new Level9();
	if(layer && layer->initWithDifficulty(difficulty)){
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

    return NULL;
}

void Level9::addOrnament()
{

}

void Level9::onExit()
{
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_level9_2-hd.plist");
}

void Level9::addTerrains()
{
	auto terrain1 = Terrain::createTerrain(2);
	terrain1->setPosition(Point(650,800));
	terrain1->setTag(1);
	addChild(terrain1,2);

	auto terrain2 = Terrain::createTerrain(2);
	terrain2->setPosition(Point(435,735));
	terrain2->setTag(2);
	addChild(terrain2,3);

	auto terrain3 = Terrain::createTerrain(2);
	terrain3->setPosition(Point(815,690));
	terrain3->setTag(3);
	addChild(terrain3,4);

	auto terrain4 = Terrain::createTerrain(2);
	terrain4->setPosition(Point(180,610));
	terrain4->setTag(4);
	addChild(terrain4,4);

	auto terrain5 = Terrain::createTerrain(2);
	terrain5->setPosition(Point(440,620));
	terrain5->setTag(5);
	addChild(terrain5,4);

	auto terrain6 = Terrain::createTerrain(2);
	terrain6->setPosition(Point(350,520));
	terrain6->setTag(6);
	addChild(terrain6,5);

	auto terrain7 = Terrain::createTerrain(2);
	terrain7->setPosition(Point(290,350));
	terrain7->setTag(7);
	addChild(terrain7,7);

	auto terrain8 = Terrain::createTerrain(2);
	terrain8->setPosition(Point(460,410));
	terrain8->setTag(8);
	addChild(terrain8,6);

	auto terrain9 = Terrain::createTerrain(2);
	terrain9->setPosition(Point(790,320));
	terrain9->setTag(9);
	addChild(terrain9,7);

	auto terrain10 = Terrain::createTerrain(2);
	terrain10->setPosition(Point(470,240));
	terrain10->setTag(10);
	addChild(terrain10,8);

}
