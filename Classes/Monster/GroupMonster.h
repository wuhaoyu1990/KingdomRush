#ifndef _GROUP_MONSTER_H_
#define _GROUP_MONSTER_H_

#include "cocos2d.h"

USING_NS_CC;

class GroupMonster: public Node
{
public:     
   // virtual bool init();
    static GroupMonster* initGroupEnemy(int type, int road, int path);
    CREATE_FUNC(GroupMonster);  
	//保存怪物类型
	CC_SYNTHESIZE(int, type, Type);
	//不同出口
	CC_SYNTHESIZE(int, road, Road);
	//不同路线
	CC_SYNTHESIZE(int, path, Path);
};

#endif