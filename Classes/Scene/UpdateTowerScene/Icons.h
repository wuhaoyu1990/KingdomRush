#ifndef __ICONS_H__
#define __ICONS_H__

#include "cocos2d.h"

USING_NS_CC;
class Icons: public Sprite
{
public :
	//设置三种状态：不可升级，可升级，已升级
	enum IconsStatus{eIconOff,eIconOn,eIconOK};
	//初始化方法
    virtual bool initNewIcons(std::string picture,std::string off_picture,std::string iconName,
		std::string iconIntroduction,int startNum,Icons::IconsStatus iconSta,int row,int column);


	//创建自定义精灵的方法
	static Icons* createNewIcons(std::string picture,std::string off_picture,std::string iconName,
		std::string iconIntroduction,int startNum,Icons::IconsStatus iconSta,int row,int column);
    CREATE_FUNC(Icons);


	//根据iconSta修改精灵状态
	void showIcon(Icons::IconsStatus iconSta);
	//该精灵升级所需要星星数
	int priceTag;
	//内层显示的图标；
	Sprite* icon;
	//最外层框图
	Sprite* iconSelected;
	//判断是否被选中
	void iconIsSelect(bool select);
	
	//控件名称
	std::string iconName;
	//控件介绍
	std::string iconIntroduction;
	//储存行列位置
	int iconRow;
	int	iconColumn;


	IconsStatus getIconState();
	void setMayUpedate();
	void setUpdated();
protected:
	IconsStatus iconSta;
	Sprite* iconOKBack;
	
	std::string picture;
	std::string off_picture;

};

#endif