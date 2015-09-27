#ifndef __Encyclopedia_SCENE_H__
#define __Encyclopedia_SCENE_H__
#include "cocos2d.h"

class EncyclopediaScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

	void menuNextCallback1(Ref *pSender );//点击百科提示按钮，场景切换
	void menuNextCallback2(Ref *pSender );//点击百科防御塔按钮，场景切换
	void menuNextCallback3(Ref *pSender );//点击百科敌人按钮，场景切换
	void menuNextCallback4(Ref *pSender );//点击百科关闭按钮，场景切换

    CREATE_FUNC(EncyclopediaScene);
 
};
#endif // __EncyclopediaScene_SCENE_H__