#include "SlotMenu.h"
#include "GameView.h"
#include "TransitionGame.h"
#include "SimpleAudioEngine.h" 

using namespace CocosDenshion;

int SAVELOT = 101;
int NEWGAME = 301;
int LABEL_HINT = 201;

SlotMenu::~SlotMenu(){}

SlotMenu::SlotMenu(){}

bool SlotMenu::initWithNum(int num)
{
	if (!Sprite::init())
	{
		return false;
	}
	setNum(num);
	//Ìí¼Ó±³¾°Í¼Æ¬
	savelot = Sprite::createWithSpriteFrameName("mainmenu_saveslot_0001.png");
	addChild(savelot);
	button_Savelot_Delete = MenuItemSprite::create(Sprite::createWithSpriteFrameName("mainmenu_saveslot_delete_0001.png"),
			Sprite::createWithSpriteFrameName("mainmenu_saveslot_delete_0002.png"),
			CC_CALLBACK_1(SlotMenu::button_Savelot_Delete_callback, this));
	button_Savelot_Delete->setPosition(Point(savelot->getContentSize().width/2 - 20,savelot->getContentSize().height/2 - 20));
	auto menu = Menu::create(button_Savelot_Delete,NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu);

	label_hint = Label::createWithTTF("DELETE SLOT?","Comic_Book.ttf",32,Size::ZERO,TextHAlignment::LEFT,TextVAlignment::TOP);
	label_hint->setColor(Color3B(219,205,139));
	label_hint->setPosition(Point(savelot->getContentSize().width/2,savelot->getContentSize().height/3*2));
	auto confirm_Delete = MenuItemSprite::create(Sprite::createWithSpriteFrameName("mainmenu_saveslot_confirmdelete_0001.png"),
		Sprite::createWithSpriteFrameName("mainmenu_saveslot_confirmdelete_0001.png"),
		CC_CALLBACK_1(SlotMenu::conform_delete, this));
	confirm_Delete->setPosition(Point(savelot->getContentSize().width/4,savelot->getContentSize().height/3));

	auto cancel_Delete_1 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("mainmenu_saveslot_confirmdelete_0002.png"),
		Sprite::createWithSpriteFrameName("mainmenu_saveslot_confirmdelete_0002.png"),
		CC_CALLBACK_1(SlotMenu::cancel_delete, this));
	cancel_Delete_1->setPosition(Point(savelot->getContentSize().width/4*3,savelot->getContentSize().height/3));
	auto delete1_menu = Menu::create(confirm_Delete,cancel_Delete_1,NULL);
	delete1_menu->setPosition(Vec2::ZERO);
	auto confirm = Node::create();
	confirm->addChild(label_hint);
	confirm->addChild(delete1_menu);
	confirm->setTag(LABEL_HINT);
	confirm->setVisible(false);
	savelot->addChild(confirm);

	if(UserDefault::getInstance()->getIntegerForKey(String::createWithFormat("Slot%d",getNum())->getCString(),0)==0)
	{
		createNewGame();
		button_Savelot_Delete->setVisible(false);
	}else
	{
		auto node = Sprite::create();

		auto label_slot = Label::createWithTTF(String::createWithFormat("SLOT %d",num)->getCString(),"Comic_Book.ttf",32,Size::ZERO,TextHAlignment::LEFT,TextVAlignment::TOP);
		label_slot->setColor(Color3B(219,205,139));
		label_slot->setPosition(Point(savelot->getContentSize().width/2,savelot->getContentSize().height/3*2));
		node->addChild(label_slot);
		auto star = Sprite::createWithSpriteFrameName("mainmenu_saveslot_icons_0001.png");
		star->setPosition(Point(savelot->getContentSize().width/4,savelot->getContentSize().height/3));
		node->addChild(star);

		int starCountInt = UserDefault::getInstance()->getIntegerForKey(String::createWithFormat("Slot%d_Star",getNum())->getCString(),0);

		auto slot = Label::createWithTTF(String::createWithFormat("%d/65",starCountInt)->getCString(),"Comic_Book.ttf",32,Size::ZERO,TextHAlignment::LEFT,TextVAlignment::TOP);
		slot->setColor(Color3B(219,205,139));
		slot->setPosition(Point(savelot->getContentSize().width/4*2.5,savelot->getContentSize().height/3));
		node->addChild(slot);
		node->setTag(NEWGAME);
		savelot->addChild(node);
	}

	auto savelot_Listener = EventListenerTouchOneByOne::create();
	savelot_Listener->onTouchBegan = [&](Touch* touch, Event* event){
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Point locationInNode = target->convertTouchToNodeSpace(touch);

		Size size = target->getContentSize();
		Rect rect = Rect(0, 0, size.width, size.height);

		if (rect.containsPoint(locationInNode)&&!savelot->getChildByTag(LABEL_HINT)->isVisible())
		{  
			target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mainmenu_saveslot_0002.png"));			
			return true;  
		}  
		return false;  
	};
	savelot_Listener->onTouchEnded = [&](Touch* touch, Event* event){
		auto instance = GameManager::getInstance();
		instance->setInstance(getNum());
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		UserDefault::getInstance()->setIntegerForKey(instance->SLOTX_ISEXIT,1);
		Director::getInstance()->replaceScene(TransitionGame::create(2.0f, GameView::createScene()));
	};
	savelot_Listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(savelot_Listener,savelot);
	return true;
}

void SlotMenu::button_Savelot_Delete_callback(Ref* pSender)
{
	savelot->getChildByTag(NEWGAME)->setVisible(false);
	button_Savelot_Delete->setVisible(false);
	savelot->getChildByTag(LABEL_HINT)->setVisible(true);
}

void SlotMenu::cancel_delete(Ref* pSender)
{
	savelot->getChildByTag(NEWGAME)->setVisible(true);
	button_Savelot_Delete->setVisible(true);
	savelot->getChildByTag(LABEL_HINT)->setVisible(false);
}

void SlotMenu::conform_delete(Ref* pSender)
{
	savelot->getChildByTag(LABEL_HINT)->setVisible(false);
	savelot->removeChildByTag(NEWGAME);
	createNewGame();
	deleteRecord(getNum());
}

void SlotMenu::createNewGame()
{
	auto label = Label::createWithTTF("new game","Comic_Book.ttf",42,Size::ZERO,TextHAlignment::LEFT,TextVAlignment::TOP);
	label->setColor(Color3B(219,205,139));
	label->setPosition(Point(savelot->getContentSize().width/2,savelot->getContentSize().height/2));
	label->setTag(NEWGAME);
	savelot->addChild(label);
}

SlotMenu* SlotMenu::createMenu(int num)
{
    auto slotMenu = new SlotMenu();
 
    if (slotMenu && slotMenu->initWithNum(num))
    {
        slotMenu->autorelease();
        return slotMenu;
    }
    CC_SAFE_DELETE(slotMenu);
    return NULL;
}

void SlotMenu::deleteRecord(int num)
{
	UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("Slot%d",getNum())->getCString(),0);

	for(int i=0;i<13;i++)
	{
		UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("Slot%d_Level_%d",getNum(),i)->getCString(),0);
	}

	for(int i=0;i<13;i++)
	{
		UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("Slot%d_Level_%d_star",getNum(),i)->getCString(),0);
	}

	UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("Slot%d_DownCount",getNum())->getCString(),0);
 
	UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("Slot%d_NewDown",getNum())->getCString(),0);

	UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("Slot%d_StarLeft",getNum())->getCString(),0);

	UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("Slot%d_Star",getNum())->getCString(),0);

	UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("Slot%d_Gem",getNum())->getCString(),0);

	for(int i = 0;i<6;i++){
		UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("Slot%d_Shop_%d",getNum(),i)->getCString(),0);
	}
}