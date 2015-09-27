#include "EncyclopediaScene.h"
#include "EncyclopaediaTips.h"
#include "EnemyScene.h"
#include "TowerScene.h"
#include "SoundManager.h"

USING_NS_CC;


//创建场景
Scene* EncyclopediaScene::createScene()
{
    auto scene = Scene::create();
    auto layer = EncyclopediaScene::create();
    scene->addChild(layer);
    return scene;
}

// // 场景初始化方法
bool EncyclopediaScene::init()
{
    //////////////////////////////
    // 1.首先进行父类初始化
    if ( !Layer::init() )
    {
		 //如果初始化父类失败返回false
        return false;
    }

	 Size visibleSize = Director::getInstance()->getVisibleSize();
		//导入plist


/*****************************************************************************************************************/
	//第一层图片添加 即背景图片
   //// addImage 加载纹理图片  可实现图片的放大
// 支持图片格式: .png, .bmp, .tiff, .jpeg, .pvr
	for(int i = 0;i<4;i++){
		for(int j =0;j<5;j++){
			auto sprite = Sprite::createWithSpriteFrameName("encyclopedia_bgTile.png");
			sprite->setPosition(Point(i*310,j*150));
			sprite->setAnchorPoint(Point(0,0));
			addChild(sprite);
		}
	}

//第二层图片=====即图片的切换=================================================================================================
	//防御塔

    auto sprite11 = Sprite::createWithSpriteFrameName("encyclopedia_button_towers_0001.png");
	sprite11->setScale(0.95f);

	auto sprite1 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("encyclopedia_button_towers_0001.png"),sprite11,
		CC_CALLBACK_1(EncyclopediaScene::menuNextCallback2,this));  
    auto ccmenuu1 = Menu::create(sprite1,NULL);  //实现三者之间的顺序切换  
    sprite1->setPosition(Point(visibleSize.width*0.23,visibleSize.height*0.65));  
	ccmenuu1->setPosition(Vec2::ZERO);
    this->addChild(ccmenuu1,2); 

	//百科 敌人
	//缩图
	auto sprite21 = Sprite::createWithSpriteFrameName("encyclopedia_button_enemies_0001.png");
	sprite21->setScale(0.95f);

	auto sprite2 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("encyclopedia_button_enemies_0001.png"),
	sprite21,CC_CALLBACK_1(EncyclopediaScene::menuNextCallback3,this));  
    auto ccmenuu2 = Menu::create(sprite2,NULL);  //实现切换  
    sprite2->setPosition(Point(visibleSize.width*0.57,visibleSize.height*0.5));  
	ccmenuu2->setPosition(Vec2::ZERO);
    this->addChild(ccmenuu2,2); 

	//百科 提示
	//原图
	auto sprite31 = Sprite::createWithSpriteFrameName("encyclopedia_button_tips_0001.png");
	sprite31->setScale(0.8f);
   //缩图
	auto sprite32 = Sprite::createWithSpriteFrameName("encyclopedia_button_tips_0001.png");
	sprite32->setScale(0.75f);
	
	auto sprite3 =MenuItemSprite::create(sprite31,sprite32,CC_CALLBACK_1(EncyclopediaScene::menuNextCallback1,this));  
    auto ccmenuu3 = Menu::create(sprite3,NULL);  //实现切换  
    sprite3->setPosition(Point(visibleSize.width*0.86,visibleSize.height*0.3));  
	ccmenuu3->setPosition(Vec2::ZERO);
    this->addChild(ccmenuu3,2); 

	
	//百科 战斗攻略
	auto sprite4 =Sprite::createWithSpriteFrameName("encyclopedia_button_strategyGuide_0001.png");
    sprite4->setPosition(Point(visibleSize.width*0.22,visibleSize.height*0.2));  
	sprite4->setScale(0.9f);
    this->addChild(sprite4,1); 

	//百科 关闭按钮
	auto sprite51 = Sprite::createWithSpriteFrameName("encyclopedia_little_button_close_0001.png");
	auto sprite5 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("encyclopedia_button_close_0001.png"),sprite51,
		CC_CALLBACK_1(EncyclopediaScene::menuNextCallback4,this));  

    auto ccmenuu5 = Menu::create(sprite5,NULL);  //实现切换  
    sprite5->setPosition(Point(visibleSize.width*0.87,visibleSize.height*0.83));  
	ccmenuu5->setPosition(Vec2::ZERO);
    this->addChild(ccmenuu5,2); 

	return true;
   
}

//============================================================================================================================//

////点击百科提示按钮，场景切换
void EncyclopediaScene::menuNextCallback1(Ref *pSender ){
	SoundManager::playClickEffect();
    Director::getInstance()->pushScene(EncyclopaediaTips::createScene());
  }

//点击百科防御塔按钮，场景切换
void EncyclopediaScene::menuNextCallback2(Ref *pSender ){
	SoundManager::playClickEffect();
	Director::getInstance()->pushScene(Tower::createScene());
 }

//点击百科敌人按钮，场景切换
void EncyclopediaScene::menuNextCallback3(Ref *pSender ){
	SoundManager::playClickEffect();
	Director::getInstance()->pushScene(Enemy::createScene());
 }

//点击百科关闭按钮，场景切换
void EncyclopediaScene::menuNextCallback4(Ref *pSender ){
	SoundManager::playClickEffect();
	Director::getInstance()->popScene();
 }