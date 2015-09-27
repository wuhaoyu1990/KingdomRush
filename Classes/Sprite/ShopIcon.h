#ifndef _SHOP_ICON_H_
#define _SHOP_ICON_H_

#include "cocos2d.h"

USING_NS_CC;

class ShopIcon : public Sprite
{
public:
	virtual bool initIcon(int tpye);
    CREATE_FUNC(ShopIcon);
	static ShopIcon* createIcon(int type);
	void setGlowing();
	void setNotGlowing();
	int type;
	Sprite* icon;
	Sprite* glow;
};

#endif