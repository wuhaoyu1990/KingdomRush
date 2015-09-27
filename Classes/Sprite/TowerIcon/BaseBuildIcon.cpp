#include "BaseBuildIcon.h"
#include "GameManager.h"

bool BaseBuildIcon::initIcon(int type,int money)
{
	if (!Sprite::init())
	{
		return false;
	}
	isSelected = false;
	auto test = String::createWithFormat("main_icons_00%02d.png",type)->getCString();
	baseIcon = Sprite::createWithSpriteFrameName(String::createWithFormat("main_icons_00%02d.png",type)->getCString());
	addChild(baseIcon);
	priceIcon = Sprite::createWithSpriteFrameName("price_tag.png");
	priceIcon->setPosition(Point(0,-baseIcon->getContentSize().height/2));
	addChild(priceIcon);
	priceLabel = Label::createWithTTF(String::createWithFormat("%d",money)->getCString(),"arial.ttf",20);
	priceLabel->setColor(Color3B(255,153,0));
	priceLabel->setPosition(Point(priceIcon->getContentSize().width/2,priceIcon->getContentSize().height/2-2));
	priceIcon->addChild(priceLabel);

	okIcon = Sprite::createWithSpriteFrameName("main_icons_0019.png");
	okIcon->setPosition(Point(baseIcon->getContentSize().width/2,baseIcon->getContentSize().height/2));
	baseIcon->addChild(okIcon);
	okIcon->setVisible(false);

	setMoney(money);
	setType(type);
	this->scheduleUpdate();


	return true;
}

void BaseBuildIcon::setUpdateMoney(int money)
{
	setMoney(money);
	priceLabel->setString(String::createWithFormat("%d",money)->getCString());
}

BaseBuildIcon* BaseBuildIcon::createIcon(int type,int money)
{
    auto baseBuildIcon = new BaseBuildIcon();
 
    if (baseBuildIcon && baseBuildIcon->initIcon(type,money))
    {
        baseBuildIcon->autorelease();
        return baseBuildIcon;
    }
    CC_SAFE_DELETE(baseBuildIcon);
    return NULL;
}

void BaseBuildIcon::setNotEnoughMoney()
{
	isAble = false;
	priceLabel->setColor(Color3B(102,102,102));
	baseIcon->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("main_icons_disabled_00%02d.png",type)->getCString()));
	priceIcon->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("price_tag_disabled.png"));
	okIcon->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("main_icons_disabled_0019.png"));
}

void BaseBuildIcon::setEnoughMoney()
{
	isAble = true;
	priceLabel->setColor(Color3B(255,153,0));
	okIcon->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("main_icons_0019.png"));
	baseIcon->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("main_icons_00%02d.png",type)->getCString()));
	priceIcon->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("price_tag.png"));
}

void BaseBuildIcon::setSelected()
{
	isSelected = true;
	okIcon->setVisible(true);
}

void BaseBuildIcon::setNotSelected()
{
	isSelected = false;
	okIcon->setVisible(false);
}

void BaseBuildIcon::update(float dt)
{
	if(getMoney()<=GameManager::getInstance()->MONEY){
		setEnoughMoney();
	}else{
		setNotEnoughMoney();
	}
}