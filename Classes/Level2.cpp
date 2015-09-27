#include "Level2.h"
USING_NS_CC;

Level2::Level2()
{};

Level2::~Level2(){};

bool Level2::initWithDifficulty(int difficulty)
{
    if ( !Layer::init() )
    {
        return false;
    }
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level2_2-hd.plist");
	setLevel(2);
	this->difficulty = difficulty;
	initMap();
	//road0为上边的路
	std::vector<Point> points;
	points.push_back(Point(678,950));
	points.push_back(Point(1160,270));
	addWaveProgressBars(points);
	waveFlags.at(0)->restartWaveFlag();
	waveFlags.at(1)->restartWaveFlag();
	SoundManager::playDesertBattle();
	return true;
}

Level2* Level2::createGame(int difficulty)
{  
    auto layer = new Level2();
	if(layer && layer->initWithDifficulty(difficulty)){
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

    return NULL;
}

void Level2::addOrnament()
{

}

void Level2::onExit()
{
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_level2_2-hd.plist");
}

void Level2::addTerrains()
{
	auto terrain14= Terrain::createTerrain(1);
	terrain14->setPosition(Point(700,730));//中上沿边第四个
	terrain14->setTag(14);
	addChild(terrain14,3);

	auto terrain12= Terrain::createTerrain(1);
	terrain12->setPosition(Point(580,660));//中上沿边第二个
	terrain12->setTag(12);
	addChild(terrain12,4);

	auto terrain13= Terrain::createTerrain(1);
	terrain13->setPosition(Point(700,660));//中上沿边第三个
	terrain13->setTag(13);
	addChild(terrain13,4);

	auto terrain11= Terrain::createTerrain(1);
	terrain11->setPosition(Point(430,650));//中上沿边第一个
	terrain11->setTag(11);
	addChild(terrain11,4);

	auto terrain2 = Terrain::createTerrain(1);
	terrain2->setPosition(Point(280,550));//上一个右边
	terrain2->setTag(2);
	addChild(terrain2,5);

	auto terrain1 = Terrain::createTerrain(1);
	terrain1->setPosition(Point(160,530));//左边下
	terrain1->setTag(1);
	addChild(terrain1,5);

	auto terrain7= Terrain::createTerrain(1);
	terrain7->setPosition(Point(620,470));//中间左起第三个
	terrain7->setTag(7);
	addChild(terrain7,6);

	auto terrain8= Terrain::createTerrain(1);
	terrain8->setPosition(Point(720,470));//中间左起第四个
	terrain8->setTag(8);
	addChild(terrain8,6);

	auto terrain6 = Terrain::createTerrain(1);
	terrain6->setPosition(Point(520,460));//中间左起第二个
	terrain6->setTag(6);
	addChild(terrain6,6);

	auto terrain5 = Terrain::createTerrain(1);
	terrain5->setPosition(Point(440,420));//中间左起第一个
	terrain5->setTag(5);
	addChild(terrain5,6);

	auto terrain10= Terrain::createTerrain(1);
	terrain10->setPosition(Point(960,380));//右边左起第二个
	terrain10->setTag(10);
	addChild(terrain10,7);

	auto terrain9= Terrain::createTerrain(1);
	terrain9->setPosition(Point(850,370));//右边左起第一个
	terrain9->setTag(9);
	addChild(terrain9,7);

	auto terrain4 = Terrain::createTerrain(1);
	terrain4->setPosition(Point(620,300));//上一个上边一点
	terrain4->setTag(4);
	addChild(terrain4,7);


}