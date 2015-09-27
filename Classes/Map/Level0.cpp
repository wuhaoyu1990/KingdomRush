#include "Level0.h"
#include "BeginAnimation.h"

USING_NS_CC;

Level0::Level0()
{};

Level0::~Level0(){
	int i = 0;
};

bool Level0::initWithDifficulty(int difficulty)
{
    if ( !Layer::init() )
    {
        return false;
    }
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level_0_2-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level0-hd.plist");
	
	setLevel(0);
	this->difficulty = difficulty;
	initMap();
	Size visibleSize = Director::getInstance() -> getVisibleSize();
	color = LayerColor::create(Color4B::BLACK, 1200, 1000);
    addChild(color,999);
	SoundManager::playDesertBattle();
	return true;
}

Level0* Level0::createGame(int difficulty)
{  
	auto layer = new Level0();
	if(layer && layer->initWithDifficulty(difficulty)){
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

    return NULL;
}

void Level0::addOrnament()
{
	auto hammer = Sprite::createWithSpriteFrameName("Stage1_Hammer.png");
	hammer->setPosition(Point(593,547));
	addChild(hammer,5);
	auto wall = Sprite::createWithSpriteFrameName("Stage1_OverWall.png");
	wall->setPosition(Point(19,583));
	addChild(wall,999);
}

void Level0::startAfterStory()
{
	color->removeFromParent();
	std::vector<Point> points;
	points.push_back(Point(1160,545));
	points.push_back(Point(1160,505));
	addWaveProgressBars(points);
	waveFlags.at(0)->restartWaveFlag();
	waveFlags.at(1)->restartWaveFlag();
	GameManager::getInstance()->MONEY = startGold;
	GameManager::getInstance()->LIFE = maxLife;
	playerState->setGold(startGold);
	playerState->setLife(maxLife);
	playerState->setWave(0,maxWave);
	playerState->startProgressTimers();
	scheduleUpdate();
	schedule(schedule_selector(Level0::addWaves), 0.5f);
}

void Level0::onEnterTransitionDidFinish()
{
	auto story = BeginAnimation::create();
	story->game = this;
	playerState->addChild(story,99);
}


void Level0::onExit()
{
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_level_0_2-hd.plist");
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_level0-hd.plist");
}

void Level0::addTerrains()
{
	auto terrain1 = Terrain::createTerrain(1);
	terrain1->setPosition(Point(600,780));//左边下
	terrain1->setTag(1);
	addChild(terrain1,3);
	
	auto terrain9 = Terrain::createTerrain(1);
	terrain9->setPosition(Point(320,690));
	terrain9->setTag(9);
	addChild(terrain9,4);

	auto terrain4 = Terrain::createTerrain(1);
	terrain4->setPosition(Point(520,610));//左边上
	terrain4->setTag(4);
	addChild(terrain4,4);

	auto terrain5 = Terrain::createTerrain(1);
	terrain5->setPosition(Point(675,610));//右边上
	terrain5->setTag(5);
	addChild(terrain5,4);

	auto terrain6 = Terrain::createTerrain(1);
	terrain6->setPosition(Point(475,530));//左边
	terrain6->setTag(6);
	addChild(terrain6,5);

	auto terrain7 = Terrain::createTerrain(1);
	terrain7->setPosition(Point(720,530));//右边
	terrain7->setTag(7);
	addChild(terrain7,5);

	auto terrain2 = Terrain::createTerrain(1);
	terrain2->setPosition(Point(520,445));//最上面的
	terrain2->setTag(2);
	addChild(terrain2,6);

	auto terrain3 = Terrain::createTerrain(1);
	terrain3->setPosition(Point(675,445));//右边下
	terrain3->setTag(3);
	addChild(terrain3,6);

	auto terrain10 = Terrain::createTerrain(1);
	terrain10->setPosition(Point(320,340));
	terrain10->setTag(10);
	addChild(terrain10,7);

	auto terrain8 = Terrain::createTerrain(1);
	terrain8->setPosition(Point(600,270));//最下面的
	terrain8->setTag(8);
	addChild(terrain8,8);

}