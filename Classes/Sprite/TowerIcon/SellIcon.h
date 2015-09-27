#ifndef _SELL_ICON_H_
#define _SELL_ICON_H_

#include "BaseBuildIcon.h"
#include "cocos2d.h"
USING_NS_CC;

class SellIcon : public BaseBuildIcon
{
public:
	virtual bool init();
    CREATE_FUNC(SellIcon);
	void setSelected();
	void setNotSelected();
};

#endif