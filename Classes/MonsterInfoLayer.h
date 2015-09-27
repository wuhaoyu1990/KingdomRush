#ifndef _MONSTER_INFO_LAYER_H_
#define _MONSTER_INFO_LAYER_H_

#include "cocos2d.h"
#include "BaseMonster.h"

USING_NS_CC;

class MonsterInfoLayer : public Sprite
{
public:
	static MonsterInfoLayer* createMonsterInfoLayer(BaseMonster* monster);
	virtual bool init(BaseMonster* monster);
	void setMonsterInfo();
	BaseMonster* mBaseMonster;
	Sprite* info_bg;
	int maxHp;
	void updateMonsterHp(float dt);
	Label* hpLabel;
};

#endif