#include "ChooseDifficulty.h"
#include "GameScene.h"
#include "TransitionGame.h"
#include "GameManager.h"
#include "SoundManager.h"

USING_NS_CC;


Scene* ChooseDifficulty::createSceneWithLevel(int level)
{
    //创建一个自释放的场景对象
    auto scene = Scene::create();
    auto layer = ChooseDifficulty::create();
	layer->initWithLevel(level);
    scene->addChild(layer);
    return scene;
}

// // 场景初始化方法
bool ChooseDifficulty::init()
{

    if ( !Layer::init() )
    {
        return false;
    }
	visibleSize = Director::getInstance()->getVisibleSize();
	difficulty = 0;
	 //获取整个手机可视屏幕尺寸
    

	/***********************************************************************************************/
	for(int i = 0;i<4;i++){
		for(int j =0;j<5;j++){
			auto sprite = Sprite::createWithSpriteFrameName("encyclopedia_bgTile.png");
			sprite->setPosition(Point(i*320,j*160));
			sprite->setAnchorPoint(Point(0,0));
			addChild(sprite);
		}
	}
	/***********************************************************************************************/
	//第二层背景图片 地图

	auto bgSprite2 = Sprite::createWithSpriteFrameName("LevelSelect_Bg.png");
	bgSprite2->setPosition(Point(visibleSize.width*0.5,visibleSize.height*0.5));//点是整个屏幕的中间位置
	//bgSprite2->setScaleX(scaleX);
	this->addChild(bgSprite2,1);

	/***********************************************************************************************/
	//第三层背景图片 
	//放大镜
	auto loupeSprite = Sprite::createWithSpriteFrameName("LevelSelect_loupe.png");
	loupeSprite->setPosition(Point(visibleSize.width*0.21,390));
	//loupeSprite->setScale(scaleX);
	this->addChild(loupeSprite,2);

	//关闭按钮
	auto closeSprite =MenuItemSprite::create(Sprite::createWithSpriteFrameName("LevelSelect_Back_0001.png"),
	Sprite::createWithSpriteFrameName("LevelSelect_Back_0002.png"),CC_CALLBACK_1(ChooseDifficulty::menuCallback,this));  
    Menu *closeMenu = Menu::create(closeSprite,NULL);  //实现三者之间的顺序切换  
    closeSprite->setPosition(Point(visibleSize.width*0.87,580));  
	closeMenu->setPosition(Vec2::ZERO);
    this->addChild(closeMenu,2);  

	//进入战斗的按钮
	auto startModeSprite =MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_startMode_0001.png"),
	Sprite::createWithSpriteFrameName("levelSelect_startMode_0002.png"),CC_CALLBACK_1(ChooseDifficulty::menuCallnext,this));  
    Menu *startModeMenu = Menu::create(startModeSprite,NULL);  //实现三者之间的顺序切换  
    startModeSprite->setPosition(Point(visibleSize.width*0.8,100));  
	startModeMenu->setPosition(Vec2::ZERO);
    this->addChild(startModeMenu,2); 

 
 //=======================放大镜上小星星等的设置======================================================================================//
	//第一个小星星
	 star1 = Sprite::createWithSpriteFrameName("levelSelect_badges_0002.png");
	 star1->setPosition(Point(210,580));
	 //star1->setScale(scaleX);
	 star1->setRotation(-30.0f);
	 addChild(star1,9);

//--------------------------//第二个小星星-----------------------------------------------------------------------------------------------------------//

	 star2 = Sprite::createWithSpriteFrameName("levelSelect_badges_0002.png");
	 star2->setPosition(Point(260,600));
	 //star2->setScale(scaleX);
	 star2->setRotation(-15.0f);
	 addChild(star2,9);

//-------------------------------//第三个小星星------------------------------------------------------------------------------------------------------//

	 star3 = Sprite::createWithSpriteFrameName("levelSelect_badges_0002.png");
	 star3->setPosition(Point(310,605));
	// star3->setScale(scaleX);
	 addChild(star3,9);
//-------------------------------//盾牌------------------------------------------------------------------------------------------------------//
	 star4 = Sprite::createWithSpriteFrameName("levelSelect_badges_0004.png");
	 star4->setPosition(Point(360,600));
	// star4->setScale(scaleX);
	 star4->setRotation(15.0f);
	 addChild(star4,9);

//-------------------------------//拳头------------------------------------------------------------------------------------------------------//

	star5 = Sprite::createWithSpriteFrameName("levelSelect_badges_0006.png");
	star5->setPosition(Point(410,580));
	//star5->setScale(scaleX);
	star5->setRotation(30.0f);
	addChild(star5,9);

   /**********************************************************************************************************/

	/*****************************
	**进入关卡前介绍-开始
	**黑色字体（位于蓝色字体之下）
	******************************/
	
	//读取xml文档,放入ValueVector中
	

	/*****************************
	**进入关卡前介绍-结束
	*****************************/

	/**********************************沙漠绿洲（字体的设置*******************************************************************/

	

////////////---------------------------按钮1--------------------------------------------------------------------------------
	auto imgNormal1 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_butModes_0005.png"),Sprite::createWithSpriteFrameName("levelSelect_butModes_0001.png"));  
    auto imgSelect1 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_butModes_0001.png"),Sprite::createWithSpriteFrameName("levelSelect_butModes_0005.png"));  


	toggleItem1 = MenuItemToggle::createWithCallback(
		                                                 CC_CALLBACK_1(ChooseDifficulty::starMenuCallback1,this), 
		                                                 imgNormal1,
														 imgSelect1,NULL); 
	
	toggleItem1->setTag(1); 
    toggleItem1->setPosition(Point(visibleSize.width*0.12,20)); 
    toggleItem1->setSelectedIndex(0);   // 我们刚进入的时候武器标签是被选中的  
    toggleItem1->setEnabled(false); // 选中的标签不能再点击  
   //////////////////////////----------------------------按钮2------------------------------------------------
    auto imgNormal2 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_butModes_0006.png"),Sprite::createWithSpriteFrameName("levelSelect_butModes_0006.png"));  
    auto imgSelect2 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_butModes_0002.png"),Sprite::createWithSpriteFrameName("levelSelect_butModes_0002.png")); 
	auto imgDisable2 =MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_butModes_0004.png"),Sprite::createWithSpriteFrameName("levelSelect_butModes_0004.png"));


	toggleItem2 = MenuItemToggle::createWithCallback(
		                                                 CC_CALLBACK_1(ChooseDifficulty::starMenuCallback2,this), 
		                                                 imgNormal2,
														 imgSelect2,
														 imgDisable2,NULL);    //	CCMenuItemFont::create("ccc")
	toggleItem2->setSelectedIndex(2);
	toggleItem2->setEnabled(false);
	toggleItem2->setPosition(Point(visibleSize.width*0.24,20)); 
 
	 //////////////----------------------按钮3--------------------------------------------------------------------------
	auto imgNormal3 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_butModes_0007.png"),Sprite::createWithSpriteFrameName("levelSelect_butModes_0007.png"));  
	auto imgSelect3 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_butModes_0003.png"),Sprite::createWithSpriteFrameName("levelSelect_butModes_0003.png"));  
	auto imgDisable3 =MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_butModes_0004.png"),Sprite::createWithSpriteFrameName("levelSelect_butModes_0004.png"));

	toggleItem3=MenuItemToggle::createWithCallback(
		                                                 CC_CALLBACK_1(ChooseDifficulty::starMenuCallback3,this), 
		                                                 imgNormal3,
														 imgSelect3,
														 imgDisable3,NULL);    //	CCMenuItemFont::create("ccc")

	toggleItem3->setSelectedIndex(2);
	toggleItem3->setEnabled(false);
    toggleItem3->setPosition(Point(visibleSize.width*0.36,20));
     
    auto toggleMenu = Menu::create(toggleItem1,toggleItem2,toggleItem3, NULL);  
    toggleMenu->setPosition(Point(0,0));  
    this->addChild(toggleMenu, 2);  
	auto listenerkeyPad = EventListenerKeyboard::create();  
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(ChooseDifficulty::onKeyReleased, this);  
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this); 

	return true;
}

void ChooseDifficulty::initWithLevel(int level)
{
	ValueVector txt_description = 
		FileUtils::getInstance()->getValueVectorFromFile(String::createWithFormat("level%d_description.xml",level)->getCString());
	int i = 0;
	for( auto& e : txt_description){
		auto txt_map = txt_description.at(i).asValueMap();//将键值转化成Map格式，放入txt_map中
		int id_int = txt_map.at("id").asInt();//获取id
		if(id_int == i){
			blueStrTop = txt_map.at("blueStrTop").asString();
			blackStr[0] = txt_map.at("blackStr1").asString();
			blackStr[1] = txt_map.at("blackStr2").asString();
			blackStr[2] = txt_map.at("blackStr3").asString();
			blueStr[0] = txt_map.at("blueStr1").asString();
			blueStr[1] = txt_map.at("blueStr2").asString();
			blueStr[2] = txt_map.at("blueStr3").asString();
		}
		i++;//next description
	}
	auto label1 = Label::createWithTTF(blueStrTop, "Marker Felt.ttf", 40);
    label1->setPosition(Point(visibleSize.width*0.5, 620));
	label1->setColor(Color3B(0,0,0));
	label1->setRotation(3.0f);
	label1->setAnchorPoint(Point(0,1));
    this->addChild(label1, 1);

	/**********************************蓝色字体:挑战、英雄模式、钢铁模式********************************************************/

	blueLabel = Label::createWithTTF(blueStr[0], "Marker Felt.ttf", 30);
	blueLabel->setPosition(Point(visibleSize.width*0.5, 570));
	blueLabel->setRotation(3.0f);
	blueLabel->setColor(Color3B(65,94,241));
	blueLabel->setAnchorPoint(Point(0,1));
    this->addChild(blueLabel, 1);




	blackLabel = Label::createWithTTF(blackStr[0], "Marker Felt.ttf", 21);
	blackLabel->setPosition(Point(visibleSize.width*0.50, 525));
	blackLabel->setRotation(3.0f);
	blackLabel->setColor(Color3B(0,0,0));
	blackLabel->setAnchorPoint(Point(0,1));

    this->addChild(blackLabel, 1);
	this->level = level;
	int star = UserDefault::getInstance()->getIntegerForKey(String::createWithFormat(GameManager::getInstance()->LEVELX_STARNUM,level)->getCString(),0);
	toggleItem1->setPosition(toggleItem1->getPosition()+Point(0,20));

	setBadges(star);
	auto thumb = Sprite::createWithSpriteFrameName(String::createWithFormat("thumb_stage%d.png",level+1)->getCString());
	thumb->setPosition(Point(260,400));
	addChild(thumb,1);
}

void ChooseDifficulty::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
    switch (keycode)
    {
	case EventKeyboard::KeyCode::KEY_BACK:   //返回键听
		Director::getInstance()->popScene();
        break;
    case EventKeyboard::KeyCode::KEY_MENU:      //菜单监听
        break;
    case::EventKeyboard::KeyCode::KEY_HOME:
        break;
    default:
        break;
    }
}

void ChooseDifficulty::setBadges(int star)
{
	switch(star)
	{
	case(0):
		toggleItem1->setSelectedIndex(0);       
		toggleItem2->setSelectedIndex(2);      
		toggleItem3->setSelectedIndex(2);  
		toggleItem1->setPosition(toggleItem1->getPosition()+Point(0,20));

		toggleItem1->setEnabled(false);
		break;
	case 1:
		toggleItem1->setSelectedIndex(0);       
		toggleItem2->setSelectedIndex(2);      
		toggleItem3->setSelectedIndex(2);      
		star1->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0001.png"));

		toggleItem1->setEnabled(false);
		break;
	case 2:
		toggleItem1->setSelectedIndex(0);       
		toggleItem2->setSelectedIndex(2);      
		toggleItem3->setSelectedIndex(2);  
		toggleItem1->setEnabled(false);
		star1->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0001.png"));
		star2->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0001.png"));
		break;
	case 3:
		toggleItem1->setSelectedIndex(0);     
		toggleItem2->setSelectedIndex(1);      
		toggleItem3->setSelectedIndex(1);  
		toggleItem1->setEnabled(false);
		toggleItem2->setEnabled(true);
		toggleItem3->setEnabled(true);
		star1->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0001.png"));
		star2->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0001.png"));
		star3->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0001.png"));
		break;
	case 4:
		toggleItem1->setSelectedIndex(0);     
		toggleItem2->setSelectedIndex(1);      
		toggleItem3->setSelectedIndex(1);  
		toggleItem1->setEnabled(false);
		toggleItem2->setEnabled(true);
		toggleItem3->setEnabled(true);
		star1->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0001.png"));
		star2->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0001.png"));
		star3->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0001.png"));
		star4->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0003.png"));
		break;
	case 5:
		toggleItem1->setSelectedIndex(0);     
		toggleItem2->setSelectedIndex(1);      
		toggleItem3->setSelectedIndex(1);  
		toggleItem1->setEnabled(false);
		toggleItem2->setEnabled(true);
		toggleItem3->setEnabled(true);
		star1->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0001.png"));
		star2->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0001.png"));
		star3->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0001.png"));
		star4->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0003.png"));
		star5->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0005.png"));
		break;
	default:
		break;
	}

}


//关闭按钮返回上一场景
void ChooseDifficulty::menuCallback(Ref* pSpender){

	SoundManager::playClickEffect();
	Director::getInstance()->popScene();
}

//开始战斗按钮进入下一场景
void ChooseDifficulty::menuCallnext(Ref* pSpender)
{     
	SoundManager::playClickEffect();
	Director::getInstance()->replaceScene(TransitionGame::create(2.0f, GameScene::playGame(level,difficulty)));      
}

//升级1
void ChooseDifficulty::starMenuCallback1(Ref* pSpender)
{
	SoundManager::playClickEffect();
	difficulty = 0;
	toggleItem1->runAction(MoveBy::create(0.1f,Point(0,20)));
	if(toggleItem2->getSelectedIndex() == 0)
		toggleItem2->runAction(MoveBy::create(0.1f,Point(0,-20)));
	if(toggleItem3->getSelectedIndex() == 0)
		toggleItem3->runAction(MoveBy::create(0.1f,Point(0,-20)));

	toggleItem1->setEnabled(false); 
	toggleItem1->setSelectedIndex(0); 
	toggleItem2->setSelectedIndex(1);       
	toggleItem2->setEnabled(true);
	toggleItem3->setSelectedIndex(1);       
	toggleItem3->setEnabled(true);  

	blueLabel->setString(blueStr[0]);
	blackLabel->setString(blackStr[0]);
}

void ChooseDifficulty::starMenuCallback2(Ref* pSpender)
{
	SoundManager::playClickEffect();
	difficulty = 1;
	toggleItem2->runAction(MoveBy::create(0.1f,Point(0,20)));
	if(toggleItem1->getSelectedIndex() == 0)
		toggleItem1->runAction(MoveBy::create(0.1f,Point(0,-20)));
	if(toggleItem3->getSelectedIndex() == 0)
		toggleItem3->runAction(MoveBy::create(0.1f,Point(0,-20)));
	toggleItem2->setSelectedIndex(0);       
	toggleItem2->setEnabled(false);
	toggleItem1->setSelectedIndex(1);       
	toggleItem1->setEnabled(true);
	toggleItem3->setSelectedIndex(1);       
	toggleItem3->setEnabled(true); 



	blueLabel->setString(blueStr[1]);
	blackLabel->setString(blackStr[1]); 
}

void ChooseDifficulty::starMenuCallback3(Ref* pSpender)//////////
{
	SoundManager::playClickEffect();
	difficulty = 2;
	toggleItem3->runAction(MoveBy::create(0.1f,Point(0,20)));
	if(toggleItem2->getSelectedIndex() == 0)
		toggleItem2->runAction(MoveBy::create(0.1f,Point(0,-20)));
	if(toggleItem1->getSelectedIndex() == 0)
		toggleItem1->runAction(MoveBy::create(0.1f,Point(0,-20)));
	toggleItem3->setSelectedIndex(0);       
	toggleItem3->setEnabled(false); 
	toggleItem1->setSelectedIndex(1);       
	toggleItem1->setEnabled(true);
	toggleItem2->setSelectedIndex(1);       
	toggleItem2->setEnabled(true);  

	blueLabel->setString(blueStr[2]);
	blackLabel->setString(blackStr[2]); 
}