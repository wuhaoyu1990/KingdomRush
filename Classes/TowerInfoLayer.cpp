#include "TowerInfoLayer.h"

TowerInfoLayer* TowerInfoLayer::createTowerInfoLayer(TowerType towerType)
{
	auto towerInfoLayer = new TowerInfoLayer();
	if(towerInfoLayer && towerInfoLayer->init(towerType)){
		towerInfoLayer->autorelease();
		return towerInfoLayer;
	}
	CC_SAFE_DELETE(towerInfoLayer);
	return NULL;
}

bool TowerInfoLayer::init(TowerType towerType)
{
	if(!Sprite::init()){
		return false;
	}
	info_bg = Sprite::createWithSpriteFrameName("menu_bottom_bg.png");

	setTowerInfo(towerType);
	addChild(info_bg);
	return true;
}

void TowerInfoLayer::setTowerInfo(TowerType towerType)
{
	auto protraits = Sprite::createWithSpriteFrameName("portraits_sc.png");
	protraits->setPosition(Point(20,25));
	info_bg->addChild(protraits);

	auto towerName = Label::createWithTTF("","Comic_Book.ttf",20);
	towerName->setPosition((Point(60,25)));
	towerName->setAnchorPoint(Point(0,0.5));
	info_bg->addChild(towerName);

	auto forceSprite = Sprite::createWithSpriteFrameName("icon_0007.png");
	forceSprite->setPosition(Point(300,25));
	info_bg->addChild(forceSprite);

	auto forceLabel = Label::createWithTTF("","Comic_Book.ttf",18);
	forceLabel->setAnchorPoint(Point(0,0.5));
	forceLabel->setPosition(Point(325,25));

	info_bg->addChild(forceLabel);
	//ÏÔÊ¾¹¥»÷ËÙ¶È

	auto speedSprite = Sprite::createWithSpriteFrameName("icon_0008.png");
	speedSprite->setPosition(Point(400,25));
	info_bg->addChild(speedSprite);

	auto speedLabel = Label::createWithTTF("","Comic_Book.ttf",18);
	speedLabel->setAnchorPoint(Point(0,0.5));
	speedLabel->setPosition(Point(435,25));
	info_bg->addChild(speedLabel);

	//ÏÔÊ¾¹¥»÷·¶Î§
	auto scopeSprite = Sprite::createWithSpriteFrameName("icon_0009.png");
	scopeSprite->setPosition(Point(570,25));
	info_bg->addChild(scopeSprite);

	auto scopeLabel = Label::createWithTTF("","Comic_Book.ttf",18);
	scopeLabel->setAnchorPoint(Point(0,0.5));
	scopeLabel->setPosition(Point(605,25));
	info_bg->addChild(scopeLabel);
	Sprite* portraits_sc;

	switch(towerType){

	case(ARCHER_1):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_towers_0001.png");
		towerName->setString("ARCHER TOWER");
		forceLabel->setString("8");
		speedLabel->setString("AVERAGE");
		scopeLabel->setString("SHORT");
		break;
	case(ARCHER_2):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_towers_0001.png");
		towerName->setString("MARKSMEN");
		forceLabel->setString("12");
		speedLabel->setString("FAST");
		scopeLabel->setString("AVERAGE");
		break;
	case(ARCHER_3):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_towers_0001.png");
		towerName->setString("SHARPSHOOTER");
		forceLabel->setString("16");
		speedLabel->setString("FAST");
		scopeLabel->setString("LONG");
		break;
	case(COSSBOW):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_towers_0009.png");
		towerName->setString("CROSSBOW");
		forceLabel->setString("24");
		speedLabel->setString("FAST");
		scopeLabel->setString("GREAT");
		break;
	case(TOTEMTOWER):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_towers_0010.png");
		towerName->setString("TOTEM TOWER");
		forceLabel->setString("24");
		speedLabel->setString("FAST");
		scopeLabel->setString("GREAT");
		break;
	case(EARTHQUAKE):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_towers_0011.png");
		towerName->setString("DWAARP");
		forceLabel->setString("60");
		speedLabel->setString("VERY SLOW");
		scopeLabel->setString("GREAT");
		break;
	case(MECHS):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_towers_0012.png");
		towerName->setString("MECH");
		forceLabel->setString("30");
		speedLabel->setString("FAST");
		scopeLabel->setString("GREAT");
		break;
	case(ARTILLERY_1):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_towers_0004.png");
		towerName->setString("BOMBARD");
		forceLabel->setString("20");
		speedLabel->setString("VERY SLOW");
		scopeLabel->setString("SHOT");
		break;
	case(ARTILLERY_2):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_towers_0004.png");
		towerName->setString("ARTILLERY");
		forceLabel->setString("30");
		speedLabel->setString("VERY SLOW");
		scopeLabel->setString("AVERAGE");
		break;
	case(ARTILLERY_3):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_towers_0004.png");
		towerName->setString("HOWITZER");
		forceLabel->setString("40");
		speedLabel->setString("VERY SLOW");
		scopeLabel->setString("LONG");
		break;
	case(BARAACKS_1):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_towers_0002.png");
		towerName->setString("MILITIA");
		forceLabel->setString("3");
		speedLabel->setString("NONE");
		scopeLabel->setString("NONE");
		break;
	case(BARAACKS_2):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_towers_0002.png");
		towerName->setString("FOOTMEN");
		forceLabel->setString("6");
		speedLabel->setString("NONE");
		scopeLabel->setString("NONE");
		break;
	case(BARAACKS_3):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_towers_0002.png");
		towerName->setString("KNIGHTS");
		forceLabel->setString("9");
		speedLabel->setString("NONE");
		scopeLabel->setString("NONE");
		break;
	case(ARCHMAGE):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_towers_0006.png");
		towerName->setString("ARCHMAGE");
		forceLabel->setString("80");
		speedLabel->setString("SLOW");
		scopeLabel->setString("GREAT");
		break;
	case(NEC):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_towers_0005.png");
		towerName->setString("NECROMANCER");
		forceLabel->setString("80");
		speedLabel->setString("SLOW");
		scopeLabel->setString("GREAT");
		break;
	case(MAGE_1):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_towers_0003.png");
		towerName->setString("MAGE");
		forceLabel->setString("15");
		speedLabel->setString("SLOW");
		scopeLabel->setString("SHOT");
		break;
	case(MAGE_2):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_towers_0003.png");
		towerName->setString("ADEPTE");
		forceLabel->setString("30");
		speedLabel->setString("SLOW");
		scopeLabel->setString("AVERAGE");
		break;
	case(MAGE_3):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_towers_0003.png");
		towerName->setString("WIZARD");
		forceLabel->setString("60");
		speedLabel->setString("SLOW");
		scopeLabel->setString("LONG");
		break;
	case(ASSASSIN):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_towers_0008.png");
		towerName->setString("ASSASSIN");
		forceLabel->setString("14");
		speedLabel->setString("NONE");
		scopeLabel->setString("NONE");
		break;
	case(TEMPLAR):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_towers_0007.png");
		towerName->setString("TEMPLAR");
		forceLabel->setString("20");
		speedLabel->setString("NONE");
		scopeLabel->setString("NONE");
		break;
	default:
		break;
	}
	portraits_sc->setPosition(Point(protraits->getContentSize().width/2,protraits->getContentSize().height/2));
	protraits->addChild(portraits_sc);
}