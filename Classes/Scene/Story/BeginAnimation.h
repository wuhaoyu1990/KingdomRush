#ifndef _BEGIN_ANIMATION_H_
#define _BEGIN_ANIMATION_H_

#include "cocos2d.h"
#include "Level0.h"
USING_NS_CC;
class BeginAnimation : public Layer
{
public:
    static Scene* createScene();
	CREATE_FUNC(BeginAnimation);
	

    virtual bool init();
	void startAnimation1();
	void startAnimation2(); 
	void backToGame();
	Level0* game;
protected:

	Sprite* continue_btn;

    Sprite* sp1,*sp2,*sp3;

};

#endif