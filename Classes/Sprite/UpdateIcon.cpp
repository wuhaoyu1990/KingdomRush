#include "UpdateIcon.h"

USING_NS_CC;

bool UpdateIcon::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	baseIcon = Sprite::createWithSpriteFrameName("main_icons_0005.png");
	baseIcon->setName("0005.png");
	addChild(baseIcon);
	priceIcon = Sprite::createWithSpriteFrameName("price_tag.png");
	priceIcon->setPosition(Point(0,-baseIcon->getContentSize().height/2));
	addChild(priceIcon);
	
	priceLabel = Label::create("70","Arial",20);
	priceLabel->setColor(Color3B(255,153,0));
	priceLabel->setPosition(Point(priceIcon->getContentSize().width/2,priceIcon->getContentSize().height/2-2));
	priceIcon->addChild(priceLabel);

	okIcon = Sprite::createWithSpriteFrameName("main_icons_0019.png");
	okIcon->setPosition(Point(baseIcon->getContentSize().width/2,baseIcon->getContentSize().height/2));
	baseIcon->addChild(okIcon);
	okIcon->setVisible(false);

	isSelected = false;
	this->scheduleUpdate();
	return true;
}