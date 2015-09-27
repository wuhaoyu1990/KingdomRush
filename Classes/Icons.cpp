#include "Icons.h"
USING_NS_CC;


bool Icons::initNewIcons(std::string onPicture,std::string offPicture,std::string iconName,
						 std::string iconIntroduction,int startNum,Icons::IconsStatus iconSta,int row,int column)
{
	if ( !Sprite::init() )
    {
        return false;
    }

	picture=onPicture;
	off_picture=offPicture;
	switch(iconSta)
	{
		case Icons::eIconOff:
			icon=Sprite::createWithSpriteFrameName(offPicture);
		break;
		case Icons::eIconOn:
			icon=Sprite::createWithSpriteFrameName(onPicture);
		break;
		default:
			icon=Sprite::createWithSpriteFrameName(onPicture);
		break;
	}
	//初始化三种类型的状态
	
	iconOKBack=Sprite::createWithSpriteFrameName("upgrades_icons_0032.png");
	iconSelected=Sprite::createWithSpriteFrameName("upgrades_icons_0031.png");
	

	addChild(iconSelected);
	addChild(icon);
	addChild(iconOKBack,1);

	iconSelected->setVisible(false);
	iconOKBack->setVisible(false);
	this->iconName=iconName;
	this->iconIntroduction=iconIntroduction;
	this->iconSta=iconSta;
	this->priceTag=startNum;
	this->iconRow=row;
	this->iconColumn=column;
	return true;
}
void Icons::setMayUpedate()
{
	icon->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(picture));
	this->iconSta=Icons::eIconOn;

}
void Icons::setUpdated()
{
	iconOKBack->setVisible(true);
	this->iconSta=Icons::eIconOK;
}
void Icons::iconIsSelect(bool select)
{
	iconSelected->setVisible(select);
}

Icons* Icons::createNewIcons(std::string picture,std::string off_picture,std::string iconName,
							 std::string iconIntroduction,int startNum,Icons::IconsStatus iconSta,int row,int column)
{
    auto icon = new Icons();
 
    if (icon && icon->initNewIcons(picture,off_picture,iconName,iconIntroduction,startNum,iconSta,row,column))
    {
        icon->autorelease();
        return icon;
    }
    CC_SAFE_DELETE(icon);
    return NULL;
}


void Icons::showIcon(Icons::IconsStatus iconSta)
{
	switch (iconSta)
	{
	case Icons::eIconOff:
		icon->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(off_picture));
		this->iconOKBack->setVisible(false);
		break;
	case Icons::eIconOn:
		icon->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(picture));
		this->iconOKBack->setVisible(false);
		break;
	case Icons::eIconOK:
		icon->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(picture));
		this->iconOKBack->setVisible(true);
		break;
	default:
		icon->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(picture));
		break;
	}
	this->iconSta=iconSta;
}
Icons::IconsStatus Icons::getIconState()
{
	return this->iconSta;
}

