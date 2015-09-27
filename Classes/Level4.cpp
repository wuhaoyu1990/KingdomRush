#include "Level4.h"
USING_NS_CC;

Level4::Level4()
{};

Level4::~Level4(){};

bool Level4::initWithDifficulty(int difficulty)
{
    if ( !Layer::init() )
    {
        return false;
    }
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level4-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level4_2-hd.plist");

	setLevel(4);
	this->difficulty = difficulty;
	initMap();

	std::vector<Point> points;
	points.push_back(Point(700,767));
	points.push_back(Point(740,767));
	addWaveProgressBars(points);
	waveFlags.at(0)->restartWaveFlag();
	waveFlags.at(1)->restartWaveFlag();
	SoundManager::playDesertBattle();
	return true;
}

Level4* Level4::createGame(int difficulty)
{  
    auto layer = new Level4();
	if(layer && layer->initWithDifficulty(difficulty)){
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

    return NULL;
}

void Level4::addOrnament()
{
	auto ship=Sprite::createWithSpriteFrameName("Stage4_OverShip.png");
	ship->setPosition(Point(825,865));
	addChild(ship,99);

	doorSprite=Sprite::createWithSpriteFrameName("Stage4_ShipDoor_0001.png");
	doorSprite->setPosition(Point(730,820));
	mapSprite->addChild(doorSprite,0);

		//树下方的植被加入地图
	for(int i=0;i<4;i++)
	{
		treeTerrains[i]=Sprite::createWithSpriteFrameName(String::createWithFormat("Stage4_Trees_Terrains_000%d.png",i+1)->getCString());
		treeTerrains[i]->setPosition(Point(985,530));
	}
	for(int i=3;i>=0;i--)
		mapSprite->addChild(treeTerrains[i],0);
	//将树加入地图
	for(int i=0;i<4;i++)
		for(int j=0;j<3;j++)
			TreeSprite[i][j]=NULL;

	TreeSprite[0][0]=Sprite::createWithSpriteFrameName("Stage4_Trees_0001.png");
	TreeSprite[0][0]->setPosition(Point(1060,590));
	mapSprite->addChild(TreeSprite[0][0],1);

	TreeSprite[0][1]=Sprite::createWithSpriteFrameName("Stage4_Trees_0001.png");
	TreeSprite[0][1]->setPosition(Point(1140,590));
	mapSprite->addChild(TreeSprite[0][1],1);

	TreeSprite[0][2]=Sprite::createWithSpriteFrameName("Stage4_Trees_0001.png");
	TreeSprite[0][2]->setPosition(Point(1130,560));
	mapSprite->addChild(TreeSprite[0][2],1);

	TreeSprite[1][0]=Sprite::createWithSpriteFrameName("Stage4_Trees_0001.png");
	TreeSprite[1][0]->setPosition(Point(920,620));
	mapSprite->addChild(TreeSprite[1][0],1);

	TreeSprite[1][1]=Sprite::createWithSpriteFrameName("Stage4_Trees_0001.png");
	TreeSprite[1][1]->setPosition(Point(990,590));
	mapSprite->addChild(TreeSprite[1][1],1);

	TreeSprite[1][2]=Sprite::createWithSpriteFrameName("Stage4_Trees_0001.png");
	TreeSprite[1][2]->setPosition(Point(960,550));
	mapSprite->addChild(TreeSprite[1][2],1);

	TreeSprite[2][0]=Sprite::createWithSpriteFrameName("Stage4_Trees_0001.png");
	TreeSprite[2][0]->setPosition(Point(885,580));
	mapSprite->addChild(TreeSprite[2][0],1);

	TreeSprite[3][0]=Sprite::createWithSpriteFrameName("Stage4_Trees_0001.png");
	TreeSprite[2][0]->setPosition(Point(860,525));
	mapSprite->addChild(TreeSprite[2][0],1);
}

void Level4::onExit()
{
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_level4_2-hd.plist");
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_level4-hd.plist");
}

void Level4::waveEvent()
{
	if(wave == 0){
		SoundManager::playShipOpen();
		Vector<SpriteFrame*> animFrames;
		SpriteFrame* frame=NULL;
		for (int i = 1; i <= 9; i++)
		{
			frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("Stage4_ShipDoor_00%02d.png",i)->getCString());
			if(frame!=nullptr)
				animFrames.pushBack(frame);
		}
		auto animation=Animation::createWithSpriteFrames(animFrames, 0.1f);
		doorSprite->runAction(Animate::create(animation));
		schedule(schedule_selector(Level4::addMonsters), 1.0f, waveVector.at(wave).size(), 1.0f);
	}else{
		schedule(schedule_selector(Level4::addMonsters), 1.0f, waveVector.at(wave).size(), 0);
	}
}

void Level4::addTerrains()
{
	auto terrain1 = Terrain::createTerrain(1);
	terrain1->setPosition(Point(690,654));
	terrain1->setTag(1);
	addChild(terrain1,4);

	auto terrain5 = Terrain::createTerrain(1);
	terrain5->setPosition(Point(471,642));
	terrain5->setTag(5);
	addChild(terrain5,4);

	auto terrain2 = Terrain::createTerrain(1);
	terrain2->setPosition(Point(650,574));
	terrain2->setTag(2);
	addChild(terrain2,5);

	auto terrain6 = Terrain::createTerrain(1);
	terrain6->setPosition(Point(452,554));
	terrain6->setTag(6);
	addChild(terrain6,5);

	auto terrain13 = Terrain::createTerrain(1);
	terrain13->setPosition(Point(225,510));
	terrain13->setTag(13);
	addChild(terrain13,5);

	auto terrain7 = Terrain::createTerrain(1);
	terrain7->setPosition(Point(471,475));
	terrain7->setTag(7);
	addChild(terrain7,6);
	
	auto terrain3 = Terrain::createTerrain(1);
	terrain3->setPosition(Point(725,456));
	terrain3->setTag(3);
	addChild(terrain3,6);

	auto terrain4 = Terrain::createTerrain(1);
	terrain4->setPosition(Point(950,422));
	terrain4->setTag(4);
	addChild(terrain4,6);

	auto terrain14 = Terrain::createTerrain(1);
	terrain14->setPosition(Point(250,420));
	terrain14->setTag(14);
	addChild(terrain14,6);

	auto terrain8 = Terrain::createTerrain(1);
	terrain8->setPosition(Point(506,405));
	terrain8->setTag(8);
	addChild(terrain8,6);

	auto terrain15 = Terrain::createTerrain(1);
	terrain15->setPosition(Point(295,340));
	terrain15->setTag(15);
	addChild(terrain15,7);

	auto terrain16 = Terrain::createTerrain(1);
	terrain16->setPosition(Point(162,334));
	terrain16->setTag(16);
	addChild(terrain16,7);

	auto terrain9 = Terrain::createTerrain(1);
	terrain9->setPosition(Point(556,330));
	terrain9->setTag(9);
	addChild(terrain9,7);

	auto terrain10 = Terrain::createTerrain(1);
	terrain10->setPosition(Point(830,295));
	terrain10->setTag(10);
	addChild(terrain10,8);

	auto terrain11 = Terrain::createTerrain(1);
	terrain11->setPosition(Point(615,265));
	terrain11->setTag(11);
	addChild(terrain11,8);

	auto terrain12 = Terrain::createTerrain(1);
	terrain12->setPosition(Point(550,210));
	terrain12->setTag(12);
	addChild(terrain12,8);


}