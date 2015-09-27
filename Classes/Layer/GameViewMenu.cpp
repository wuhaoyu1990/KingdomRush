#include "GameViewMenu.h"
#include "GameManager.h"
#include "Upgrades.h"
#include "ShopScene.h"
#include "SoundManager.h"
#include "EncyclopediaScene.h"

bool GameViewMenu::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	isFirst = true;
	auto winSize = Director::getInstance()->getWinSize();
	shop = MenuItemSprite::create(Sprite::createWithSpriteFrameName("butShop_0001.png"),
		Sprite::createWithSpriteFrameName("butShop_0002.png"));
	update = MenuItemSprite::create(Sprite::createWithSpriteFrameName("butUpgrades_0001.png"),
		Sprite::createWithSpriteFrameName("butUpgrades_0002.png"));
	book = MenuItemSprite::create(Sprite::createWithSpriteFrameName("butEncyclopedia_0001.png"),
		Sprite::createWithSpriteFrameName("butEncyclopedia_0002.png"));


	update->setCallback([&](Ref *pSender){
		SoundManager::playClickEffect();
		Director::getInstance()->getInstance()->pushScene(Upgrades::createScene());
	});

	shop->setCallback([&](Ref *pSender){
		SoundManager::playClickEffect();
		Director::getInstance()->getInstance()->pushScene(ShopScene::createScene());
	});

	book->setCallback([&](Ref *pSender){
		SoundManager::playClickEffect();
		Director::getInstance()->getInstance()->pushScene(EncyclopediaScene::createScene());
	});

	book->setPosition(Point(winSize.width-book->getContentSize().width/2,book->getContentSize().height/2 -130));
	update->setPosition(Point(book->getPosition().x - 160,update->getContentSize().height/2 -130));
	shop->setPosition(Point(update->getPosition().x - 160,shop->getContentSize().height/2 -130));

	auto menu =Menu::create(shop,update,book,NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu);

	mapStarsContainer = Sprite::createWithSpriteFrameName("mapStarsContainer.png");
	mapStarsContainer->setPosition(Point(winSize.width - mapStarsContainer->getContentSize().width/2 -10 ,winSize.height - mapStarsContainer->getContentSize().height/2 +60));
	addChild(mapStarsContainer);


	starLabel = Label::createWithTTF("0","SohoGothicProMedium.ttf",26);
	starLabel->setPosition(Point(mapStarsContainer->getContentSize().width/4*3+20,mapStarsContainer->getContentSize().height/2));
	mapStarsContainer->addChild(starLabel);

	diamondsLabel = Label::createWithTTF("0","SohoGothicProMedium.ttf",26);
	diamondsLabel->setPosition(Point(mapStarsContainer->getContentSize().width/4,mapStarsContainer->getContentSize().height/2));
	mapStarsContainer->addChild(diamondsLabel);

	return true;
}

void GameViewMenu::onEnterTransitionDidFinish()
{
	auto instance = GameManager::getInstance();
	starLabel->setString(String::createWithFormat("%d/65", UserDefault::getInstance()->getIntegerForKey(instance->SLOTX_STAR,0))->getCString());
	diamondsLabel->setString(String::createWithFormat("%d", UserDefault::getInstance()->getIntegerForKey(instance->SLOTX_GEM,0))->getCString());
	if(isFirst){
		book->runAction(MoveBy::create(0.3f,Point(0,130)));
		update->runAction(MoveBy::create(0.3f,Point(0,130)));
		shop->runAction(MoveBy::create(0.3f,Point(0,130)));
		mapStarsContainer->runAction(MoveBy::create(0.3f,Point(0,-70)));
		isFirst = false;
	}
}
