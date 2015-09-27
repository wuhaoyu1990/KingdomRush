#ifndef _SLOT_MENU_H_
#define _SLOT_MENU_H_
#include "cocos2d.h"
USING_NS_CC;

class SlotMenu : public Sprite
{
public:
	SlotMenu();
	~SlotMenu();
    virtual bool initWithNum(int num);
    CREATE_FUNC(SlotMenu);
	void button_Savelot_Delete_callback(Ref* pSender);
	void conform_delete(Ref* pSender);
	void cancel_delete(Ref* pSender);
	void createNewGame();
	static SlotMenu* createMenu(int num);
	void deleteRecord(int num);
protected:
	Label* label_hint;
	MenuItemSprite* button_Savelot_Delete;
	Sprite* savelot;
	CC_SYNTHESIZE(int, num, Num);
};

#endif

