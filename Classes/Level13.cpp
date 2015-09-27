#include "Level13.h"

USING_NS_CC;

Level13::Level13()
{};

Level13::~Level13(){};

bool Level13::initWithDifficulty(int difficulty)
{
    if ( !Layer::init() )
    {
        return false;
    }
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_Level13-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_Level13_2-hd.plist");
	setLevel(13);
	this->difficulty = difficulty;
	initMap();

	std::vector<Point> points;
	points.push_back(Point(980,40));
	points.push_back(Point(40,270));
	addWaveProgressBars(points);
	waveFlags.at(1)->restartWaveFlag();

	SoundManager::playDesertBattle();
	return true;
}

Level13* Level13::createGame(int difficulty)
{  
    auto layer = new Level13();
	if(layer && layer->initWithDifficulty(difficulty)){
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

    return NULL;
}

void Level13::addOrnament()
{

}

void Level13::onExit()
{
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_Level13-hd.plist");
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_Level13_2-hd.plist");
}

void Level13::addTerrains()
{
	
}
