#include "GroupMonster.h"

USING_NS_CC;

GroupMonster* GroupMonster::initGroupEnemy(int type, int road, int path)
{
	auto monster = new GroupMonster();
	if (monster && monster->init())
	{
		monster->setType(type);
		monster->setRoad(road);
		monster->setPath(path);
		return monster;
	}
	CC_SAFE_RELEASE(monster);

	return NULL;
}