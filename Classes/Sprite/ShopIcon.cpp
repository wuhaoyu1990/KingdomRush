#include "ShopIcon.h"

bool ShopIcon::initIcon(int type)
{
	if (!Sprite::init())
	{
		return false;
	}
	this->type = type;
	icon = Sprite::createWithSpriteFrameName(String::createWithFormat("inaps_Icons_000%d.png",type)->getCString());
	addChild(icon);
	glow = Sprite::createWithSpriteFrameName(String::createWithFormat("inaps_IconsGlow_000%d.png",type)->getCString());
	glow->setScale(2.0f);
	addChild(glow);
	setNotGlowing();
	
	return true;
}

void ShopIcon::setGlowing()
{
	glow->setVisible(true);
}

void ShopIcon::setNotGlowing()
{
	glow->setVisible(false);
}

ShopIcon* ShopIcon::createIcon(int type)
{
	auto shopIcon = new ShopIcon();
 
    if (shopIcon && shopIcon->initIcon(type))
    {
        shopIcon->autorelease();
        return shopIcon;
    }
    CC_SAFE_DELETE(shopIcon);
    return NULL;
}