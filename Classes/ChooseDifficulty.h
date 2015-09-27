#ifndef _CHOOSE_DIFFICULTY_H_
#define _CHOOSE_DIFFICULTY_H_
#include "cocos2d.h"

USING_NS_CC;

class ChooseDifficulty : public Layer
{
public:
    static Scene* createSceneWithLevel(int level);
    virtual bool init();
	void menuCallback(Ref* pSpender);  //关闭按钮返回上一场景
	void menuCallnext(Ref* pSpender);  //开始战斗按钮进入下一场景
	void starMenuCallback1(Ref* pSpender);
	void starMenuCallback2(Ref* pSpender);
	void starMenuCallback3(Ref* pSpender);
	int level;
	int difficulty;
	void initWithLevel(int level);
	void setBadges(int star);

protected:
	 void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	 MenuItemToggle *toggleItem1; //挑战按钮
	 MenuItemToggle *toggleItem2; //英雄模式按钮
	 MenuItemToggle *toggleItem3; //钢铁模式按钮
	 std::string blueStrTop;
	 Sprite* star1;
	 Sprite* star2;
	 Sprite* star3;
	 Sprite* star4;
	 Sprite* star5;

	 Label *blueLabel; //蓝色字体标签
	 Label *blackLabel;//黑色字体标签

	 std::string blueStr[3]; //将蓝色字体设置为一个数组
	 std::string blackStr[3]; //将蓝色字体设置为一个数组

	 MenuItemToggle *imgItem1;

	  Size visibleSize;
	  Sprite *modeRulesSprite1;
	  Sprite *modeRulesSprite2;
	  Sprite *modeRulesSprite3;
	  Sprite *modeRulesSprite4;

      CREATE_FUNC(ChooseDifficulty);


};

#endif