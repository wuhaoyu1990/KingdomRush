#ifndef _NECRBOLT_H_
#define _NECRBOLT_H_

#include "cocos2d.h"
#include "Bullet.h"

class NecrBolt : public Bullet
{
public :
	bool init();
	CREATE_FUNC(NecrBolt);
	void shoot();
	void removeBullet();
};

#endif