#ifndef _STORE_SCENE_H_
#define _STORE_SCENE_H_

#include "cocos2d.h"
#include "ShopIcon.h"

USING_NS_CC;

class ShopScene : public Layer
{
public:
    static Scene* createScene();

    virtual bool init();
	void initPicture();

protected:
	Size size;
	Label *label;
	Label *label2;
	Label *label3;
	Label *gemLabel;
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);


	int count[6];//购买用品的数量

	Vector<Sprite*> backpackIcons;
	Vector<ShopIcon*> shopIcons;
	Vector<Label*> countLabels;
	void setBorad(int type);
	void initBackpackIcon();
	void setBackpackIcon(int type);
	std::string str_introduction[6];
	std::string str_name[6];
	int str_gem[6];
	Sprite* borad;
	int gem;//宝石的数量
	void buySth(int i);
    CREATE_FUNC(ShopScene);
};

#endif