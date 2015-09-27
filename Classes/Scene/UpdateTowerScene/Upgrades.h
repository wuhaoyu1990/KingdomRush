#ifndef __UPGRADES_H__
#define __UPGRADES_H__

#include "cocos2d.h"
#include "Icons.h"

USING_NS_CC;

class Upgrades :public Layer
{
public:
	
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Upgrades);
	/*初始化状态*/
	void initalState();

	//定义原始状态
	void initalOriginalSta();

	/*生成升级矩阵*/
protected:
	/*储存现有状态*/
	Icons::IconsStatus iconSta[5][6];
	/*储存原始状态*/
	Icons::IconsStatus iconInitSta[5][6];
	/*储存动态可升级图标的精灵矩阵*/
	Icons* icons[5][6];
	/*上一次点击的图标*/
	Icons* lastSelectedIcon;
	Icons* selectedIcon;


	/*所有星星*/
	int startAll;
	/*剩余星星*/
	int startLeft;
	Label* lastStartLabel;
	
	/*升级所需星星*/
	Label* upNeedStartLabel;
	

	//显示选中icon名称
	Label* iconNameLabel;
	//显示icon介绍信息
	Label* iconIntroductionLabel;

	/*显示点击的图标*/
	Sprite* iconDisplay;

	/*显示购买按钮*/
	Sprite* buyButten;
	void showStart();
	void showTips();
	void showBuyBut(Icons* iconSelect);
	void done();

	bool onIconTouchBegan(Touch* , Event* );
	void onTouchEnded(Touch* , Event* );

	bool onBuyButTouchBegan(Touch* , Event* );
	void onBuyButTouchEnded(Touch* , Event* );

	//重置为原始未升级状态
	bool resetSta(Touch* touch , Event* event);
	void resetStaEnded(Touch* , Event* );
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);

	bool onConfirmTouchBegan(Touch* touch,Event* event);
	void onConfirmTouchEnded(Touch* touch,Event* event);
};

#endif