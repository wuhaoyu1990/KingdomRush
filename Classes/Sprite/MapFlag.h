#ifndef _MAP_FLAG_H_
#define _MAP_FLAG_H_

#include "cocos2d.h"
#include "GameManager.h"

USING_NS_CC;

class MapFlag : public Sprite
{
public:
	MapFlag();
	~MapFlag();
    virtual bool initWithLevel(int Level);
    CREATE_FUNC(MapFlag);

	static MapFlag* createWithLevel(int Level);


	void changeType(int type);
private:
	Sprite* wings;
	CC_SYNTHESIZE(int, type, Type);
	CC_SYNTHESIZE(int, level, Level);
	Sprite* flag;
	Sprite* star_0;
	Sprite* star_1;
	Sprite* star_2;
	void startGame();
	void initStar();
	void addStar();
	void startSuccessAnimation();
	void startDropdownAnimation();
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void starAnimation();
	void setStarShine(int num);
	Vector<Sprite*> starVector;
	GameManager *instance;
	void setStarClose();
};

#endif