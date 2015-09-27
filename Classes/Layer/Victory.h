#ifndef __VICTORY_H__
#define __VICTORY_H__

#include "cocos2d.h"

USING_NS_CC;

class Victory : public Layer
{
public:

    virtual bool initVictory(int star,int gem);
	static Victory* createVictory(int star,int gem);
	void OnRestartTouch(Ref* pSpender);
	void OnContinueTouch(Ref* pSpender);

	void VSpriteAnimation();
	void CItemAnimation();
	void RItemAnimation();
	
    CREATE_FUNC(Victory);
	int level;
	int difficult;
	
private:
	Sprite* win_Gnome;
	Point position;
	Sprite* VictorySprite;
	MenuItemSprite* ContinueMenuItem;
	MenuItemSprite* RestartMenuItem;
	void showStar(int star);
	void showGems();
};

#endif // __HELLOWORLD_SCENE_H__
