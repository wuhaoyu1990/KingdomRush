#include "Upgrades.h"
#include "Icons.h"
#include "GameManager.h"
#include "SoundManager.h"

USING_NS_CC;


Scene* Upgrades::createScene()
{
	auto scene=Scene::create();

	auto layer = Upgrades::create();

	scene->addChild(layer);
	
	return scene;

}

void Upgrades::initalOriginalSta()
{
	for(int j=0;j<6;j++)
		for(int i=4;i>=0;i--)
		{
			iconInitSta[i][j]=Icons::eIconOff;
		}
}

void Upgrades::initalState()
{
	if(!UserDefault::getInstance()->getBoolForKey("upgrades_icon_sta_isExit",false))
	{
		for(int i=0;i<5;i++)
			for(int j=0;j<6;j++)
			{
				UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("upgrades_icon_%d_%d",i,j)->getCString(),(int)iconInitSta[i][j]);
			}
		UserDefault::getInstance()->setBoolForKey("upgrades_icon_sta_isExit",true);
	}	
	for(int j=0;j<6;j++)
		for(int i=0;i<5;i++)
		{			

			if(1==UserDefault::getInstance()->getIntegerForKey(String::createWithFormat("upgrades_icon_%d_%d",i,j)->getCString()))
			{
				icons[i][j]->showIcon(Icons::eIconOK);
			}
			else if(icons[i][j]->priceTag<=startLeft)
			{
				icons[i][j]->showIcon(Icons::eIconOn);
				i++;
				while(i<5)
					icons[i++][j]->showIcon(Icons::eIconOff);
				
			}
			else
			{
				while(i<5)
					icons[i++][j]->showIcon(Icons::eIconOff);
			}
		}
}

bool Upgrades::init()
{
	if ( !Layer::init() )
    {
        return false;
    }

	initalOriginalSta();
	startAll = UserDefault::getInstance()->getIntegerForKey(GameManager::getInstance()->SLOTX_STAR,0);
	//Ê£ÏÂ
	startLeft = UserDefault::getInstance()->getIntegerForKey(GameManager::getInstance()->SLOTX_STARLEFT,startAll);
	//×Ü


	//³õÊ¼»¯5*6µÄ¶þÎ¬¾ØÕó±£´æÍ¼Æ¬×´Ì¬
	

	//»ñÈ¡ÆÁÄ»´óÐ¡
	Size visibleSize = Director::getInstance()->getVisibleSize();

	for(int i = 0;i<4;i++){
		for(int j =0;j<5;j++){
			auto sprite = Sprite::createWithSpriteFrameName("encyclopedia_bgTile.png");
			sprite->setPosition(Point(i*310,j*150));
			sprite->setAnchorPoint(Point(0,0));
			addChild(sprite);
		}
	}

	

	//µ¼Èë×ó²àÑ¡ÔñÀ¸±³¾°
	auto bg2TileRtSprite = Sprite::createWithSpriteFrameName("upgrades_bg2_tileRight.png");//ÓÒ±ß¿ò
	auto bg2TileLtSprite = Sprite::createWithSpriteFrameName("upgrades_bg2_tileRight.png");//×ó±ß¿ò
	bg2TileLtSprite->setFlippedX(true);//×ó±ß¿ò·­×ª
	bg2TileLtSprite->setPosition(Point(visibleSize.width*0.05,visibleSize.height*0.5));
	for(int i = 1;i<14;i++){
		auto by2TileMidSprite = Sprite::createWithSpriteFrameName("upgrades_bg2_tileMid.png");
		by2TileMidSprite->setPosition((Point(Vec2(visibleSize.width*0.05 + i*(by2TileMidSprite->getContentSize().width-5),visibleSize.height*0.5))));
		addChild(by2TileMidSprite,1);
	}
	
	bg2TileRtSprite->setPosition(Point(visibleSize.width*0.61,visibleSize.height*0.5));
	
	
	
	addChild(bg2TileLtSprite,1);
	addChild(bg2TileRtSprite,1);
	



	//µ¼Èë×ó²àÑ¡¼þ °´¾ØÕóÅÅÁÐ
		//0101
	auto bgIcon0101=Sprite::createWithSpriteFrameName("upgrades_bg_icons_0001.png");
	bgIcon0101->setPosition(Point(visibleSize.width*0.08,visibleSize.height*0.1));
	addChild(bgIcon0101,2);
		//0102
	auto bgIcon0102=Sprite::createWithSpriteFrameName("upgrades_bg_icons_0002.png");
	bgIcon0102->setPosition(Point(visibleSize.width*0.18,visibleSize.height*0.1));
	addChild(bgIcon0102,2);
		//0103
	auto bgIcon0103=Sprite::createWithSpriteFrameName("upgrades_bg_icons_0003.png");
	bgIcon0103->setPosition(Point(visibleSize.width*0.28,visibleSize.height*0.1));
	addChild(bgIcon0103,2);
		//0104
	auto bgIcon0104=Sprite::createWithSpriteFrameName("upgrades_bg_icons_0004.png");
	bgIcon0104->setPosition(Point(visibleSize.width*0.38,visibleSize.height*0.1));
	addChild(bgIcon0104,2);
		//0105
	auto bgIcon0105=Sprite::createWithSpriteFrameName("upgrades_bg_icons_0005.png");
	bgIcon0105->setPosition(Point(visibleSize.width*0.48,visibleSize.height*0.1));
	addChild(bgIcon0105,2);
		//0106
	auto bgIcon0106=Sprite::createWithSpriteFrameName("upgrades_bg_icons_0006.png");
	bgIcon0106->setPosition(Point(visibleSize.width*0.58,visibleSize.height*0.1));
	addChild(bgIcon0106,2);



	//ÉèÖÃ×ó²à¾ØÕó¼àÌýÆ÷
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Upgrades::onIconTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Upgrades::onTouchEnded, this);
	//¾ØÕó¶¯Ì¬Í¼Æ¬³õÊ¼»¯
		//0201
	icons[0][0]=Icons::createNewIcons("upgrades_icons_0001.png","upgrades_icons_off_0001.png","IMPROVED AIM","INCREASES MARKSMEN ATTACK DAMAGE.",1,Icons::eIconOff,0,0);
	icons[0][0]->setPosition(Point(visibleSize.width*0.08,visibleSize.height*0.25));
	icons[0][0]->iconIsSelect(true);
	lastSelectedIcon=icons[0][0];
	addChild(icons[0][0],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,icons[0][0]);
		//0301
	icons[1][0]=Icons::createNewIcons("upgrades_icons_0002.png","upgrades_icons_off_0002.png","LUMBERMILL","REDUCES BASEC ARCHER CONSTRUCTION COSTS.",1,Icons::eIconOff,1,0);
	icons[1][0]->setPosition(Point(visibleSize.width*0.08,visibleSize.height*0.40));
	addChild(icons[1][0],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[1][0]);
		//0401
	icons[2][0]=Icons::createNewIcons("upgrades_icons_0003.png","upgrades_icons_off_0003.png","FOCUSED AIM","INCREASES MARKSMAN ATTACK DAMAGE.",2,Icons::eIconOff,2,0);
	icons[2][0]->setPosition(Point(visibleSize.width*0.08,visibleSize.height*0.55));
	addChild(icons[2][0],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[2][0]);
		//0501
	icons[3][0]=Icons::createNewIcons("upgrades_icons_0004.png","upgrades_icons_off_0004.png","ACCU RACY","INCREASES MARKSMAN ATTACK RANGE AND DAMAGE.",2,Icons::eIconOff,3,0);
	icons[3][0]->setPosition(Point(visibleSize.width*0.08,visibleSize.height*0.7));
	addChild(icons[3][0],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[3][0]);
		//0601
	icons[4][0]=Icons::createNewIcons("upgrades_icons_0005.png","upgrades_icons_off_0005.png","TWIN SHOT","MARKSMEN HAVE A CHANCE OF SHOTING TWO PROJECTILES AT THE SAME TIME",3,Icons::eIconOff,4,0);
	icons[4][0]->setPosition(Point(visibleSize.width*0.08,visibleSize.height*0.85));
	addChild(icons[4][0],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[4][0]);
		//0202
	icons[0][1]=Icons::createNewIcons("upgrades_icons_0006.png","upgrades_icons_off_0006.png","DEFENSIVE STANCE","BARRACKS TRAIN SOLDIERS WHITH BETTER ARMOR",1,Icons::eIconOff,0,1);
	icons[0][1]->setPosition(Point(visibleSize.width*0.18,visibleSize.height*0.25));
	addChild(icons[0][1],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[0][1]);
		//0302
	icons[1][1]=Icons::createNewIcons("upgrades_icons_0007.png","upgrades_icons_off_0007.png","BOOT CAMP","BARRACKS TRAIN MORE RESILIENT SOLDIERS",1,Icons::eIconOff,1,1);
	icons[1][1]->setPosition(Point(visibleSize.width*0.18,visibleSize.height*0.40));
	addChild(icons[1][1],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[1][1]);
		//0402
	icons[2][1]=Icons::createNewIcons("upgrades_icons_0008.png","upgrades_icons_off_0008.png","ESPRIT DE CORPS","INCREASES BARRACK RALLY POINT RANGE AND HEALING RATE.",2,Icons::eIconOff,2,1);
	icons[2][1]->setPosition(Point(visibleSize.width*0.18,visibleSize.height*0.55));
	addChild(icons[2][1],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[2][1]);
		//0502
	icons[3][1]=Icons::createNewIcons("upgrades_icons_0009.png","upgrades_icons_off_0009.png","VETERAN SQUAD","SOLDIERS ARE TRAINED FASTER AND WITH IMPROVED ARMOR.",2,Icons::eIconOff,3,1);
	icons[3][1]->setPosition(Point(visibleSize.width*0.18,visibleSize.height*0.7));
	addChild(icons[3][1],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[3][1]);
		//0602
	icons[4][1]=Icons::createNewIcons("upgrades_icons_0010.png","upgrades_icons_off_0010.png","COURAGE","WHILE IN COMBAT,SOLDIERS $ REINFORCEMENTS REGENERATE HEALTH.",3,Icons::eIconOff,4,1);
	icons[4][1]->setPosition(Point(visibleSize.width*0.18,visibleSize.height*0.85));
	addChild(icons[4][1],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[4][1]);
		//0203
	icons[0][2]=Icons::createNewIcons("upgrades_icons_0011.png","upgrades_icons_off_0011.png","RUNE OF POWER","INCREASES MAGES' ATTACK RANGE",1,Icons::eIconOff,0,2);
	icons[0][2]->setPosition(Point(visibleSize.width*0.28,visibleSize.height*0.25));
	addChild(icons[0][2],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[0][2]);
		//0303
	icons[1][2]=Icons::createNewIcons("upgrades_icons_0012.png","upgrades_icons_off_0012.png","SPELL PENETRATION","MAGES' BOLTS HAVE A CHANCE TO IGNORE MAGIC RESISITANCE.",1,Icons::eIconOff,1,2);
	icons[1][2]->setPosition(Point(visibleSize.width*0.28,visibleSize.height*0.40));
	addChild(icons[1][2],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[1][2]);
		//0403
	icons[2][2]=Icons::createNewIcons("upgrades_icons_0013.png","upgrades_icons_off_0013.png","ELDRITCH POWER","INCREASES MAGES' ATTACK DAMAGE.",2,Icons::eIconOff,2,2);
	icons[2][2]->setPosition(Point(visibleSize.width*0.28,visibleSize.height*0.55));
	addChild(icons[2][2],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[2][2]);
		//0503
	icons[3][2]=Icons::createNewIcons("upgrades_icons_0014.png","upgrades_icons_off_0014.png","WIZARD ACADEMY","REDUCES MAGES' SPECIAL ABILITIES COSTS",2,Icons::eIconOff,3,2);
	icons[3][2]->setPosition(Point(visibleSize.width*0.28,visibleSize.height*0.70));
	addChild(icons[3][2],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[3][2]);
		//0603
	icons[4][2]=Icons::createNewIcons("upgrades_icons_0015.png","upgrades_icons_off_0015.png","BRILLIANCE","FOR EVERY OTHER MAGE TOWER BUILT,EACH MAGE TOWER GETS A BONUS TO DAMAGE.",3,Icons::eIconOff,4,2);
	icons[4][2]->setPosition(Point(visibleSize.width*0.28,visibleSize.height*0.85));
	addChild(icons[4][2],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[4][2]);
		//0204
	icons[0][3]=Icons::createNewIcons("upgrades_icons_0016.png","upgrades_icons_off_0016.png","SMOOTHBORE","INCREASES ARTILLERY ATTACK RANGE.",1,Icons::eIconOff,0,3);
	icons[0][3]->setPosition(Point(visibleSize.width*0.38,visibleSize.height*0.25));
	addChild(icons[0][3],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[0][3]);
		//0304
	icons[1][3]=Icons::createNewIcons("upgrades_icons_0017.png","upgrades_icons_off_0017.png","ALCHEMICAL PWDER","ARTILLERIES HAVE A CHANCE OF DEALING MAX DAMAGE WITH NO SPLASH REDUCTION.",1,Icons::eIconOff,1,3);
	icons[1][3]->setPosition(Point(visibleSize.width*0.38,visibleSize.height*0.40));
	addChild(icons[1][3],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[1][3]);
		//0404
	icons[2][3]=Icons::createNewIcons("upgrades_icons_0018.png","upgrades_icons_off_0018.png","IMPROVED ORDNANCE","INCREASES ARTILLERY ATTACK DAMAGE.",2,Icons::eIconOff,2,3);
	icons[2][3]->setPosition(Point(visibleSize.width*0.38,visibleSize.height*0.55));
	addChild(icons[2][3],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[2][3]);
		//0504
	icons[3][3]=Icons::createNewIcons("upgrades_icons_0019.png","upgrades_icons_off_0019.png","GNOMISH TINKERING","REDUCES ARTILLERIES' SPECIAL ABILITIES RELOAD TIMES.",3,Icons::eIconOff,3,3);
	icons[3][3]->setPosition(Point(visibleSize.width*0.38,visibleSize.height*0.7));
	addChild(icons[3][3],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[3][3]);
		//0604
	icons[4][3]=Icons::createNewIcons("upgrades_icons_0020.png","upgrades_icons_off_0020.png","SHOCK AND AWE","ARTILLERY TOWERS HAVE A CHANCE OF STUNNING THEIR TARGETS ON EVERY ATTACK.",3,Icons::eIconOff,4,3);
	icons[4][3]->setPosition(Point(visibleSize.width*0.38,visibleSize.height*0.85));
	addChild(icons[4][3],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[4][3]);
		//0205
	icons[0][4]=Icons::createNewIcons("upgrades_icons_0021.png","upgrades_icons_off_0021.png","BURNING SKIES","INCREASES METEOR DAMAGE AND REDUCES COOLDOWN BY 5 SECONDS.",2,Icons::eIconOff,0,4);
	icons[0][4]->setPosition(Point(visibleSize.width*0.48,visibleSize.height*0.25));
	addChild(icons[0][4],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[0][4]);
		//0305
	icons[1][4]=Icons::createNewIcons("upgrades_icons_0022.png","upgrades_icons_off_0022.png","SCORCHED EARTH","METEORS SET THE GROUND ON FIRE FOR 5 SECONDS, BURNING ENEMIES WALKING OVER IT.",2,Icons::eIconOff,1,4);
	icons[1][4]->setPosition(Point(visibleSize.width*0.48,visibleSize.height*0.40));
	addChild(icons[1][4],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[1][4]);
		//0405
	icons[2][4]=Icons::createNewIcons("upgrades_icons_0023.png","upgrades_icons_off_0023.png","HELLFIRE","ADDS 2 ADDITIONAL METEORS AND REDUCES COOLDOWN BY5 SECONDS",3,Icons::eIconOff,2,4);
	icons[2][4]->setPosition(Point(visibleSize.width*0.48,visibleSize.height*0.55));
	addChild(icons[2][4],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[2][4]);
		//0505
	icons[3][4]=Icons::createNewIcons("upgrades_icons_0024.png","upgrades_icons_off_0024.png","CONFLAG RATION","INCREASES METEOR DAMAGE AND EXPLOSION RADIUS WHILE DOUBLING SCOREHED EARTH EFFECTS.",3,Icons::eIconOff,3,4);
	icons[3][4]->setPosition(Point(visibleSize.width*0.48,visibleSize.height*0.7));
	addChild(icons[3][4],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[3][4]);
		//0605
	icons[4][4]=Icons::createNewIcons("upgrades_icons_0025.png","upgrades_icons_off_0025.png","CATACLYSM","INCREASES METEOR DAMAGE AND RAINS ADDITIONAL METEORS AT RANDOM LOCATIONS ALL OVER THE BATTLEFIELD.",3,Icons::eIconOff,4,4);
	icons[4][4]->setPosition(Point(visibleSize.width*0.48,visibleSize.height*0.85));
	addChild(icons[4][4],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[4][4]);
		//0206
	icons[0][5]=Icons::createNewIcons("upgrades_icons_0026.png","upgrades_icons_off_0026.png","TRAINED VOLUNTEERS","TRAINED VOLUNTEERS HAVE ADDITIONAL HEALTH AND DEAL A LITTLE MORE DAMAGE.",2,Icons::eIconOff,0,5);
	icons[0][5]->setPosition(Point(visibleSize.width*0.58,visibleSize.height*0.25));
	addChild(icons[0][5],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[0][5]);
		//0306
	icons[1][5]=Icons::createNewIcons("upgrades_icons_0027.png","upgrades_icons_off_0027.png","MEN AT ARMS","MEN AT ARMS HAVE MORE HEALTH AND WEAR GOOD ARMOR.",3,Icons::eIconOff,1,5);
	icons[1][5]->setPosition(Point(visibleSize.width*0.58,visibleSize.height*0.40));
	addChild(icons[1][5],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[1][5]);
		//0406
	icons[2][5]=Icons::createNewIcons("upgrades_icons_0028.png","upgrades_icons_off_0028.png","CHAMPION","CHAMPIONS HAVE EVEN MORE HEALTH AND WIELD GREAT WEAPONS.",3,Icons::eIconOff,2,5);
	icons[2][5]->setPosition(Point(visibleSize.width*0.58,visibleSize.height*0.55));
	addChild(icons[2][5],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[2][5]);
		//0506
	icons[3][5]=Icons::createNewIcons("upgrades_icons_0029.png","upgrades_icons_off_0029.png","SWORN BLADES","SWORN BLADES HAVE THE MOST HEALTH AND WIELD DUAL WEAPONS.",3,Icons::eIconOff,3,5);
	icons[3][5]->setPosition(Point(visibleSize.width*0.58,visibleSize.height*0.7));
	addChild(icons[3][5],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[3][5]);
		//0606
	icons[4][5]=Icons::createNewIcons("upgrades_icons_0030.png","upgrades_icons_off_0030.png","RECURVE BOW","GIVES REINFORCEMENTS A RANGED WEAPON THAT CAN TARGET GROUND AND FLYING ENEMIES.",4,Icons::eIconOff,4,5);
	icons[4][5]->setPosition(Point(visibleSize.width*0.58,visibleSize.height*0.85));
	addChild(icons[4][5],2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),icons[4][5]);

	initalState();


	//µ¼ÈëÓÒ²àÑ¡¿ò
	auto rtSysShow=Sprite::createWithSpriteFrameName("upgrades_info.png");
	rtSysShow->setPosition(Point(visibleSize.width*0.82,visibleSize.height*0.66));
	addChild(rtSysShow,1);

	//¹ºÂò°´Å¥
	auto buyButlistener = EventListenerTouchOneByOne::create();
	buyButlistener->onTouchBegan = CC_CALLBACK_2(Upgrades::onBuyButTouchBegan, this);
	buyButlistener->onTouchEnded = CC_CALLBACK_2(Upgrades::onBuyButTouchEnded, this);
	buyButten=Sprite::createWithSpriteFrameName("upgrades_buyBut_0001.png");
	buyButten->setPosition(Point(visibleSize.width*0.82,visibleSize.height*0.23));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(buyButlistener,buyButten);
	addChild(buyButten,1);
	showBuyBut(lastSelectedIcon);

	//ÖØÖÃ°´Å¥
	auto resetListener= EventListenerTouchOneByOne::create();
	resetListener->onTouchBegan = CC_CALLBACK_2(Upgrades::resetSta, this);
	resetListener->onTouchEnded = CC_CALLBACK_2(Upgrades::resetStaEnded, this);
	//buyButlistener->onTouchEnded = CC_CALLBACK_2(upgrades::onBuyButTouchEnded, this);
	auto reset=Sprite::createWithSpriteFrameName("upgrades_buttons_0001.png");
	reset->setPosition(Point(visibleSize.width*0.73,visibleSize.height*0.07));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(resetListener,reset);
	addChild(reset,01);
	
	auto sure=Sprite::createWithSpriteFrameName("upgrades_buttons_0003.png");
	sure->setPosition(Point(visibleSize.width*0.91,visibleSize.height*0.07));
	auto sureListener= EventListenerTouchOneByOne::create();
	sureListener->onTouchBegan = CC_CALLBACK_2(Upgrades::onConfirmTouchBegan, this);
	sureListener->onTouchEnded = CC_CALLBACK_2(Upgrades::onConfirmTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(sureListener,sure);
	addChild(sure,01);

	//Ê£ÓàµÄÐÇÐÇÏÔÊ¾(±êÇ©)
	lastStartLabel = Label::createWithSystemFont(String::createWithFormat("%d",startLeft)->getCString(),"Arial",50);
	//labelLastStart->setColor(ccc3(20,50,50));
    lastStartLabel->setPosition(Point(visibleSize.width*0.85, visibleSize.height*0.91));
    addChild(lastStartLabel, 2);
	
	//ÏÔÊ¾Éý¼¶ËùÐèÒªµÄÐÇÐÇ(±êÇ©)


	
	upNeedStartLabel = Label::createWithSystemFont(String::createWithFormat("%d",lastSelectedIcon->priceTag)->getCString(),"Arial",28);
	upNeedStartLabel->setColor(Color3B(0,0,0));
	upNeedStartLabel->setPosition(Point(visibleSize.width*0.92, visibleSize.height*0.75));
	addChild(upNeedStartLabel,2);

	//Í¼Æ¬Õ¹Ê¾
	iconDisplay=Sprite::create();
	iconDisplay->setSpriteFrame(lastSelectedIcon->icon->getSpriteFrame());
	iconDisplay->setPosition(Point(visibleSize.width*0.82, visibleSize.height*0.70));
	addChild(iconDisplay,2);



	//ÏÔÊ¾½éÉÜÎÄ×Ö(±êÇ©)
	iconNameLabel=Label::createWithSystemFont(lastSelectedIcon->iconName,"Arial",25);
	iconNameLabel->setColor(Color3B(150,0,0));
	iconNameLabel->setPosition(Point(visibleSize.width*0.82, visibleSize.height*0.60));
	addChild(iconNameLabel,2);

	iconIntroductionLabel=Label::createWithSystemFont(lastSelectedIcon->iconIntroduction,"Arial",20);
	iconIntroductionLabel->setColor(Color3B(0,0,0));
	iconIntroductionLabel->setPosition(Point(visibleSize.width*0.82, visibleSize.height*0.38));
	iconIntroductionLabel->setWidth(visibleSize.width*0.3);
	iconIntroductionLabel->setHeight(visibleSize.height*0.4);
	iconIntroductionLabel->setLineBreakWithoutSpace(true);
	iconIntroductionLabel->setAlignment(cocos2d::TextHAlignment::CENTER);
	addChild(iconIntroductionLabel,2);

	auto listenerkeyPad = EventListenerKeyboard::create();  
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(Upgrades::onKeyReleased, this);  
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this); 

    return true;
}

bool Upgrades::onIconTouchBegan(Touch* touch, Event* event)
{
	auto target = static_cast<Icons*>(event->getCurrentTarget());
	
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());

	Size size = target->iconSelected->getContentSize();
	Rect rect = Rect(0-size.width/2, 0-size.height/2, size.width, size.height);
	if (rect.containsPoint(locationInNode))
	{  	
		SoundManager::playClickEffect();

		lastSelectedIcon->iconIsSelect(false);
		target->iconIsSelect(true);


		upNeedStartLabel->setString(String::createWithFormat("%d",lastSelectedIcon->priceTag)->getCString());
		iconNameLabel->setString(target->iconName);
		iconIntroductionLabel->setString(target->iconIntroduction);
		iconDisplay->setSpriteFrame(target->icon->getSpriteFrame());

		showBuyBut(target);
		
		lastSelectedIcon=target;

		return true; 
	}  
	return false;  
}
void Upgrades::onTouchEnded(Touch* touch,Event* event)
{
	
}

void Upgrades::resetStaEnded(Touch* touch , Event* event)
{
	startLeft = startAll;
	for(int i=0;i<5;i++)
	for(int j=0;j<6;j++)
	{
		icons[i][j]->showIcon(Icons::eIconOff);
		UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("upgrades_icon_%d_%d",i,j)->getCString(),0);
	}
	initalState();
	UserDefault::getInstance()->setIntegerForKey(GameManager::getInstance()->SLOTX_STARLEFT,startLeft);
	lastStartLabel->setString(String::createWithFormat("%d",startLeft)->getCString());
	static_cast<Sprite*>(event->getCurrentTarget())->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("upgrades_buttons_0001.png"));
}

bool Upgrades::resetSta(Touch* touch , Event* event)
{
	if(event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation()))
	{
		static_cast<Sprite*>(event->getCurrentTarget())->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("upgrades_buttons_0002.png"));
		return true;
	}
	return false;
}

void Upgrades::showBuyBut(Icons* iconSelect)
{
	if(iconSelect->getIconState()==Icons::eIconOn)
		buyButten->setVisible(true);
	else
		buyButten->setVisible(false);
}

bool Upgrades::onBuyButTouchBegan(Touch* touch , Event* event)
{
	if(event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())&&buyButten->isVisible())
	{
		SoundManager::playClickEffect();
		buyButten->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("upgrades_buyBut_0002.png"));
		return true;
	}
	return false;
}
void Upgrades::onBuyButTouchEnded(Touch* touch,Event* event)
{
	buyButten->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("upgrades_buyBut_0001.png"));
	lastSelectedIcon->showIcon(Icons::eIconOK);

	UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("upgrades_icon_%d_%d",lastSelectedIcon->iconRow,lastSelectedIcon->iconColumn)->getCString(),1);	
	startLeft-=lastSelectedIcon->priceTag;
	UserDefault::getInstance()->setIntegerForKey(GameManager::getInstance()->SLOTX_STARLEFT,startLeft);
	lastStartLabel->setString(String::createWithFormat("%d",startLeft)->getCString());
	buyButten->setVisible(false);
	initalState();
}

void Upgrades::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
    switch (keycode)
    {
	case EventKeyboard::KeyCode::KEY_BACK:   //·µ»Ø¼üÌý
		Director::getInstance()->popScene();
        break;
    case EventKeyboard::KeyCode::KEY_MENU:      //²Ëµ¥¼àÌý
        break;
    case::EventKeyboard::KeyCode::KEY_HOME:
        break;
    default:
        break;
    }
}

bool Upgrades::onConfirmTouchBegan(Touch* touch,Event* event)
{
	if(event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation()))
	{
		SoundManager::playClickEffect();
		static_cast<Sprite*>(event->getCurrentTarget())->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("upgrades_buttons_0004.png"));
		return true;
	}
	return false;
}

void Upgrades::onConfirmTouchEnded(Touch* touch,Event* event)
{
	Director::getInstance()->popScene();
}