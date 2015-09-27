#include "ShopScene.h"
#include "GameManager.h"
#
USING_NS_CC;

Scene* ShopScene::createScene()
{
    auto scene = Scene::create();   
    auto layer = ShopScene::create();
    scene->addChild(layer);
    return scene;
}

//初始化场景
bool ShopScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	//获取屏幕尺寸
	size = Director::getInstance()->getVisibleSize(); //获取屏幕大小 
  
    str_introduction[0] = "THE BIG BAD BOY OF\n BOMBS! YOU ONLY NEED\n ONE OF THESE TO CLEAR THE\n BATTLEFIELD AND CLAIM THE\n SPOILS OF WAR! JUST TELL\n US WHERE TO DROP IT!";
	str_introduction[1] = "FREEZE THE WORLE!\n\n THE MAGIC IN THIS ROD WILL\n FREZE ALL BADDIES AND\n PREVENT NEW ONES FROM\n APPROACHING ";
	str_introduction[2] = "BLAST YOUR ENEMIES TO\n PLECES WITH THESE\n SPECIALLY DESIGNED\n GNOME EXPLOSIVES.\n\n DESTRUCTION GUARANTEED.";
	str_introduction[3] = "THIS SPECIAL CONCOCTION\n WILL FREEZE YOUR ENEMIES\n HELPLESS IN PLACE FOR A\n WHILE";
	str_introduction[4] = "MAGICAL HEARTS TRAPPED\n IN A BOX.\n\n BREAK GLASS IN AN\n EMERGENCY TO GAIN 5\n EXTRA LIVES.";
	str_introduction[5] = "LEAVE NOTHING TO CHANCE.\n BRING EXTRA GOLD TO THE\n BATTLEFIELD!\n\n EACH BIG WORTH 500\n GOLD PIECES.";

	str_name[0] = "BOY";
	str_name[1] = "ICE";
	str_name[2] = "BOMB";
	str_name[3] = "WATER";
	str_name[4] = "HEARTBOX";
	str_name[5] = "MONEY";

	str_gem[0] = 999;
	str_gem[1] = 250;
	str_gem[2] = 50;
	str_gem[3] = 50;
	str_gem[4] = 50;
	str_gem[5] = 500;
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//黑板上的内容
	//大标题
	label = Label::createWithTTF("", "SohoGothicProMedium.ttf", 24);
    label->setPosition(Point(680, 560));
    addChild(label,1);
	//数字 
	label2 = Label::createWithTTF(" ", "SohoGothicProMedium.ttf", 24);
	label2->setPosition(Point(900, 545));
	addChild(label2,1);
	//简介	  
	label3 = Label::createWithTTF("", "SohoGothicProMedium.ttf", 12);
    label3->setPosition(Point(900, 440));
    addChild(label3,1);

	//宝石的数量===============================================
	gem = UserDefault::getInstance()->getIntegerForKey(GameManager::getInstance()->SLOTX_GEM,0);
	//初始化购买物品的数量************************************
	for(int i=0;i<6;i++)
	{
		count[i]=UserDefault::getInstance()->getIntegerForKey(String::createWithFormat(GameManager::getInstance()->SLOTX_SHOP,i)->getCString());		
	}
	//==========================================================//购买的物品


	initBackpackIcon();
	

	//=====================================================//宝石总数


	gemLabel = Label::createWithTTF(String::createWithFormat("%d",gem)->getCString(), "SohoGothicProMedium.ttf", 30);
	gemLabel->setColor(Color3B::WHITE);
	gemLabel->setPosition(Point(size.width*0.35, size.height*0.92));
    addChild(gemLabel,1);


	initPicture();
	auto listenerkeyPad = EventListenerKeyboard::create();  
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(ShopScene::onKeyReleased, this);  
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this); 
	return true;
}

void ShopScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
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

void ShopScene::initBackpackIcon()
{
	float a[6] = {0.0f,0.13f,0.236f,0.346f,0.46f,0.56f};
	for(int i=0;i<6;i++){
		auto backPackIcon = Sprite::createWithSpriteFrameName(String::createWithFormat("inaps_backPackIcons_000%d.png",i+1)->getCString());
		backPackIcon->setPosition(156,size.height*(0.72f-a[i]));
		addChild(backPackIcon,3);
		if(count[i] == 0)
			backPackIcon->setVisible(false);
		auto countLabel =  Label::createWithTTF(String::createWithFormat("%d",count[i])->getCString(), "SohoGothicProMedium.ttf", 24); //小男孩的数量
		countLabel->setPosition(Point(137, size.height*(0.70f-a[i])));
		addChild(countLabel,3);
		backpackIcons.pushBack(backPackIcon);
		countLabels.pushBack(countLabel);
	}
}

//初始化界面
void ShopScene::initPicture()
{
	auto size = Director::getInstance()->getVisibleSize(); //获取屏幕大小 
	/*************************************************************************/
	//背景图片
    auto bgSprite = Sprite::createWithSpriteFrameName("inaps_BG.png");
    bgSprite->setPosition(Point(size.width*0.5,size.height*0.5));
    addChild(bgSprite,0);
	borad = Sprite::create();
	borad->setPosition(Point(655,440));
	addChild(borad);

	auto shopIcon2 = ShopIcon::createIcon(2);//冰杖
	shopIcon2->setPosition(Point(830,250));
	addChild(shopIcon2);

	auto shopIcon5 = ShopIcon::createIcon(5);//生命
	shopIcon5->setPosition(Point(280,155));
	addChild(shopIcon5);

	auto shopIcon1 = ShopIcon::createIcon(1);//原子弹
	shopIcon1->setPosition(Point(640,170));
	addChild(shopIcon1);

	auto shopIcon4 = ShopIcon::createIcon(4);//药瓶
	shopIcon4->setPosition(Point(385,145));
	addChild(shopIcon4);

	auto shopIcon6 = ShopIcon::createIcon(6);//金币
	shopIcon6->setPosition(Point(800,170));
	addChild(shopIcon6);

	auto shopIcon3 = ShopIcon::createIcon(3);//炸弹
	shopIcon3->setPosition(Point(485,130));
	addChild(shopIcon3);

	shopIcons.pushBack(shopIcon1);
	shopIcons.pushBack(shopIcon2);
	shopIcons.pushBack(shopIcon3);
	shopIcons.pushBack(shopIcon4);
	shopIcons.pushBack(shopIcon5);
	shopIcons.pushBack(shopIcon6);

	shopIcon3->setGlowing();
	setBorad(3);

	auto buttonListener = EventListenerTouchOneByOne::create();
	buttonListener->onTouchBegan = [&](Touch* touch, Event* event){
		
		auto target = static_cast<ShopIcon*>(event->getCurrentTarget());
		
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());

		Size size = target->icon->getContentSize();
		Rect rect;
		if(target->type == 1)
			rect = Rect(0-size.width/4, 0-size.height/2, size.width/2, size.height);
		else
			rect = Rect(0-size.width/4, 0-size.height/2, size.width/2, size.height/2);
		if (rect.containsPoint(locationInNode))
		{  
			setBorad(target->type);
			target->setScale(0.9f);
			return true;  
		}  
		return false;  
	};
	buttonListener->onTouchEnded = [&](Touch* touch, Event* event){
		auto target = static_cast<ShopIcon*>(event->getCurrentTarget());
		target->setScale(1.0f);
		for(int i = 0;i<6;i++){
			shopIcons.at(i)->setNotGlowing();
		}
		target->setGlowing();
	};
	buttonListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(buttonListener,shopIcon1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(buttonListener->clone(),shopIcon3);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(buttonListener->clone(),shopIcon4);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(buttonListener->clone(),shopIcon5);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(buttonListener->clone(),shopIcon6);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(buttonListener->clone(),shopIcon2);
//---------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------//
	 //确定
	  auto confirmButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("upgrades_buttons_0003.png"),
		  Sprite::createWithSpriteFrameName("upgrades_buttons_0004.png")); 
	  confirmButton->setPosition(Point(size.width*0.90,size.height*0.10));
	  confirmButton->setCallback([&](Ref *pSender){
		UserDefault::getInstance()->setIntegerForKey(GameManager::getInstance()->SLOTX_GEM,gem);
		for(int i=0;i<6;i++)
		{
			UserDefault::getInstance()->setIntegerForKey(String::createWithFormat(GameManager::getInstance()->SLOTX_SHOP,i)->getCString(),count[i]);		
		}
		Director::getInstance()->popScene();
	  });
	  auto buyButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("inaps_buyButton_0001.png"),
		  Sprite::createWithSpriteFrameName("inaps_buyButton_0002.png")); 
	  buyButton->setPosition(Point(780,320));
	  buyButton->setCallback([&](Ref *pSender){
		  for(int i=0;i<6;i++){
			  if(shopIcons.at(i)->glow->isVisible()){
				  buySth(i);
				  break;
			  }
		  }
		
	  });
      auto menu = Menu::create(confirmButton,buyButton,NULL);  //实现切换  
	  menu->setPosition(Vec2::ZERO);
      addChild(menu,1);
	
 }

 void ShopScene::buySth(int i)
 {
	 if(gem < str_gem[i]){//宝石不够
		auto bubbleNeedMore = Sprite::createWithSpriteFrameName("inaps_bubble_needMore.png");
		bubbleNeedMore->setVisible(true);
		bubbleNeedMore->setPosition(650,430);
		addChild(bubbleNeedMore,5);
		bubbleNeedMore->runAction(Sequence::create(
			FadeOut::create(3.0f),
			CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, bubbleNeedMore)),NULL));
	 }else{
		gem = gem - str_gem[i];
		setBackpackIcon(i);
		gemLabel->setString(String::createWithFormat("%d",gem)->getCString());
		auto bubbleSprite = Sprite::createWithSpriteFrameName("inaps_bubble.png");
		bubbleSprite->setPosition(650,430);
		addChild(bubbleSprite,5); 
		bubbleSprite->runAction(Sequence::create(
			FadeOut::create(3.0f),
			CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, bubbleSprite)),NULL));
	 }
 }

 void ShopScene::setBackpackIcon(int i)
 {
	 count[i] ++;
	 countLabels.at(i)->setString(String::createWithFormat("%d",count[i])->getCString());
	 if(count[i]>0)
		 backpackIcons.at(i)->setVisible(true);
 }

 void ShopScene::setBorad(int type)
 {
	 borad->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(
		 String::createWithFormat("inaps_boardDrawings_000%d.png",type)->getCString()));
	 label3->setString(str_introduction[type-1]);
	 label2->setString(String::createWithFormat("%d",str_gem[type-1])->getCString());
	 label->setString(str_name[type-1]);
 }