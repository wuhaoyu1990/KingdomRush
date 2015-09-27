#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class WelcomeScene : public Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(WelcomeScene);
	//生成背景图
	void initBackGround();
	//生成Logo图
	void initLogo();
	//生成start按钮
	void initButton_start();
	//生成&播放Logo动画
	void initLogoAnimation();
	//生成&播放start按键动画
	void initButton_startAnimation();
	//生成记录栏menu
	void initMenu_save();
	//菜单关闭按键监听
	void savemenuCloseCallback(cocos2d::Ref* pSender);
	//save_menu动画
	void setSaveMenuInVisible();
	void setSaveMenuVisible();
	//生成3个记录存档
	//成员按键
	void init_creditBtn();
	void initSoundButton();
	void init_creditBtn_startAnimation();
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
private:
	Size visibleSize;
	//游戏logo图位置
	Point point_Logo;
	//logo
	Sprite *sprite_Logo;
	//用sprite自定义start按键
	Sprite *button_Start;
	//credit
	Sprite *button_credit;
	//记录menu
	Sprite *menu_Save;
	//menu_Save起始位置
	Point point_Menu_Save;
	//menu的关闭按键
	MenuItemSprite *button_Menu_Save_Close;
	//menu的关闭按键位置
	Point point_Button_Menu_Save_Close;
	void onEnterTransitionDidFinish();
};

#endif