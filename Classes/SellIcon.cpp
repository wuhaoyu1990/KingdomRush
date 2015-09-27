#include "SellIcon.h"

bool SellIcon::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	isSelected = false;
	isAble = true;
	baseIcon = Sprite::createWithSpriteFrameName("ico_sell_0001.png");
	addChild(baseIcon);

	okIcon = Sprite::createWithSpriteFrameName("ico_sell_0002.png");
	okIcon->setPosition(Point(baseIcon->getContentSize().width/2,baseIcon->getContentSize().height/2));
	baseIcon->addChild(okIcon);
	okIcon->setVisible(false);

	return true;
}

void SellIcon::setSelected()
{
	isSelected = true;
	okIcon->setVisible(true);
}

void SellIcon::setNotSelected()
{
	isSelected = false;
	okIcon->setVisible(false);
}