#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public Scene
{
public:	
 	virtual bool initGame(int Level,int Difficulty);
 	static Scene* playGame(int Level,int Difficulty); 
};

#endif